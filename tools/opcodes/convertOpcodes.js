"use strict";

const fs = require('fs');
const request  = require("request");
const REMOTE_OPCODE_JSON_SOURCE = "https://raw.githubusercontent.com/lmmendes/game-boy-opcodes/master/opcodes.json"
const OPCODE_OUTPUT_FILE = "codeTables.h";
const CODETABLE_DECLARATION = "static instruction codeTable[ 0x100 ] = {\n";
const PREFIXTABLE_DECLARATION = "static instruction prefixCodeTable[ 0x100 ] = {\n";
const FILE_HEADER = `#pragma once
/** GENERATED OPCODE FILE
* Created by convertOpcodes.js from data scraped from
* https://github.com/gb-archive/game-boy-opcodes
**/

`;

request(REMOTE_OPCODE_JSON_SOURCE, function (error, response, body) {
  if (error){
    throw error;
  }
  console.log("scraping github, status: ", response && response.statusCode);
  console.log("writing to file");
  var code = convertJSONtoCodeTable(body);
  fs.writeFile(OPCODE_OUTPUT_FILE, FILE_HEADER + code, (err)=>{
    if(err){ throw err; }
  });
});

function convertJSONtoCodeTable(body){
  const codes = JSON.parse(body);
  const codeTable = tableizeCode(codes.unprefixed);
  const prefixCodeTable = tableizeCode(codes.cbprefixed);
  codeTable.forEach(reshapeTable);
  prefixCodeTable.forEach(reshapeTable);
  const codeTableString = codeTable.map(cStructStringify).join(",\n");
  const prefixTableString = prefixCodeTable.map(cStructStringify).join(",\n");
  return CODETABLE_DECLARATION + codeTableString + "\n};\n\n" + PREFIXTABLE_DECLARATION + prefixTableString + "\n};";
}

function tableizeCode(codeObj){
  var returnTable = [];
  for (let i = 0; i < 0x100; i++){
    let index = "0x"+i.toString(16);
    if(codeObj[index]){
      returnTable.push(codeObj[index]);
    } else {
      returnTable.push({
        mnemonic: "CRIMES",
        length: 1,
        cycles: [0],//confirm?
        flags:["-","-","-","-"],
        addr: index
      });
    }
  }
  return returnTable;
}


function fixFlags(flag){
  if(flag=="-"){ return "E_UNAFFECTED"; }
  else if(flag=="0"){ return "E_CLEARED"; }
  else if(flag=="1"){ return "E_RAISED"; }
  else if(flag=="Z" || flag=="H" || flag=="N" || flag=="C"){ return "E_APPLIED"; }
}


function reshapeTable(e, i){
  e.flags = e.flags.map(fixFlags);
  if( e.flags.reduce((acc, curr)=> acc && curr == "E_UNAFFECTED", true) ){
    e.flags = ["NO_FLAGS"];
  }
  if(!e.operand1){ e.operand1 = ""; }
  if(!e.operand2){ e.operand2 = ""; }
  if(e.cycles[1]){
    e.cyclesAbort = e.cycles[1];
    //abort? ...abstain? abjure? abscond?
    //why am I stuck on "a" words? this must be Hussie's fault.
  } else {
    e.cyclesAbort = e.cycles[0];
  }
  e.cycles = e.cycles[0];
}


function cStructStringify(e){
  return `\t{ ${e.addr}, ${e.length}, ${e.cycles}, ${e.cyclesAbort}, {${e.flags.join(", ")}}, "${e.mnemonic}", "${e.operand1}", "${e.operand2}" }`;
}
