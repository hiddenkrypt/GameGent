

typedef struct {
	char entry;		 //0x100
	char jump;		  //0x101
	char jumpPoint[2];  //0x102-0x103
	char logo[42];	//0x104-0x0133
	struct {
		union {
			struct {
				union {
					struct {
						char titleCGB11[11];
						char manufacturerCode[4];
					};
					char titleCGB15[15];
				};
			};
			char cgbFlag;
		};
		char titleFull[16];
	};					  //0x0134-0x0143
	char licenseeCodeNew[2];//0x144-0x0145
	char superGameboyFlag;  //0x0146
	char cartridgeType;	 //0x0147
	char romSize;		   //0x0148
	char ramSize;		   //0x0149
	char destinationCode;   //0x014a
	char licenseeCodeOld;   //0x014b
	char maskROMVersion;	//0x014c
	char headerChecksum;	//0x014D   x=0:FOR i=0134h TO 014Ch:x=x-MEM[i]-1:NEXT
	char globalChecksum[2]; //0x014e-0x014f
} cartridgeHeader;
