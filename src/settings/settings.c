#include "settings.h"
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "../gui/keyBinds.h"
#include "configParserActionStructure.h"

static void applySettingFromFile( char *settingName, char *settingValue );
static void loadSettingsFromFile();

const char *SETTINGS_FILE_PATH = "settings.cfg";
char *bootRomPath;
char *lastRomPath;
bool runBootRom;
bool debugFlag;
bool runLastRomOnBoot;


static void loadSettingsFromFile();
/** \brief setup the settings module
 * gathers info on the saved settings of GameGent, and sets up default keybinds
 * @todo load setting from a saved file
 */
void Settings_init( bool loadFromFile ){
	//set defaults on init
	debugFlag = false;
	runBootRom = false;
	runLastRomOnBoot = false;
	lastRomPath = NULL;
	bootRomPath = NULL;
    //check for local settings file
    //load file, overwriting defaults
	KeyBinds_init(); //possibly pass settings config file info for saved binds?
    if( loadFromFile ){
        loadSettingsFromFile();
        printf("Finished loading settings from file.\n");
    }
}
void Settings_shutdown(){
    free( lastRomPath );
    free( bootRomPath );
}
bool  Settings_getRunLastRomOnBoot(){ return runLastRomOnBoot; }
char *Settings_getLastRomPath(){ return lastRomPath; }
bool  Settings_getDebugFlag(){ return debugFlag; }
bool  Settings_getRunBootRom(){	return runBootRom; }
char *Settings_getBootRomPath(){ return bootRomPath; }
void Settings_setRunLastRomOnBoot( bool value ){ runLastRomOnBoot = value; }
void Settings_setDebugFlag( bool value ){ debugFlag = value; }
void Settings_setRunBootRom( bool value ){ runBootRom = value; }

void Settings_setLastRomPath( char* path ){
    free( lastRomPath );
    char *temp = malloc( strlen( path ) );
    if( !temp ){
        printf("allocation of memory failed in setBootRomPath!\n");
        return;
    }
    strcpy( temp, path );
    lastRomPath = temp;
}
void Settings_setBootRomPath( char *path){
    free( bootRomPath );
    char *temp = malloc( strlen( path ) );
    if( !temp ){
        printf("allocation of memory failed in setBootRomPath!\n");
        return;
    }
    strcpy( temp, path );
    bootRomPath = temp;
}

/** \brief unimplemented! save the current settings to disc
 * @todo save the current settings to disc
 */
void Settings_save(){
}

/** \brief unimplemented! load the current settings from disc
 * @todo load the current settings to disc
 */
void Settings_load(){
}

/** \brief get the list of recent roms
 * return a list of recently played roms. Each recentRom item
 * in the list should have a full absolute path, and a short
 * (18 char truncate) name.
 * @todo actually load the list from the settings / config file, and not just use predefined test values
 *
 * \return a list of recentRom pairs
 *
 */
recentRomList Settings_get_recentRoms(){
	recentRomList list;
	list.number = 2;
	recentRom test = { "LoZ-LinksAwakening", "C:\\dev\\c\\GameGent\\tests\\LoZ-LinksAwakening-DE.gb" };
	list.items[0] = test;
	recentRom test2 = { "Tetris (World) (Re", "C:\\dev\\c\\GameGent\\tests\\Tetris (World) (Rev A).gb" };
	list.items[1] = test2;
	return list;
};


static void loadSettingsFromFile(){
	FILE* settingsFile = fopen( SETTINGS_FILE_PATH, "r" );
	if( settingsFile == NULL ){
        printf( "settings file not found, relying on defaults." );
        return;
	}
	char line[1024];
	while( fgets( line, 1024, settingsFile ) ){
        if( strlen( line ) == 1 || line[0] == '\n' || line[0] == '#' ){
            continue;
        }
        char *key = strtok( line, " " );
        char *value = strtok( NULL, "\n" );
        if( value && strlen( value ) && value[0] == ' '){
            value = value + 1;
        }
        applySettingFromFile( key, value );
	}
}


static void applySettingFromFile( char *settingName, char *settingValue ){
#define ACTION_COUNT 14
    configParserAction actions[ACTION_COUNT] = {
        { "DEBUG_MODE", BOOLEAN, &Settings_setDebugFlag, NULL },
        { "RUN_BOOT_ROM", BOOLEAN, &Settings_setRunBootRom, NULL },
        { "RUN_LAST_ROM_ON_START", BOOLEAN, &Settings_setRunLastRomOnBoot, NULL },
        { "BOOT_ROM_PATH", STRING, NULL, &Settings_setBootRomPath },
        { "LAST_ROM_PATH", STRING, NULL, &Settings_setLastRomPath },
        { "A", SDL_KEY, NULL, NULL },
        { "B", SDL_KEY, NULL, NULL },
        { "UP", SDL_KEY, NULL, NULL },
        { "DOWN", SDL_KEY, NULL, NULL },
        { "LEFT", SDL_KEY, NULL, NULL },
        { "RIGHT", SDL_KEY, NULL, NULL },
        { "SELECT", SDL_KEY, NULL, NULL },
        { "START", SDL_KEY, NULL, NULL },
        { "MENU", SDL_KEY, NULL, NULL }
    };
    for( int i = 0; i < ACTION_COUNT; i++ ){
        if( !strcmp( settingName, actions[i].settingName ) ){
            if( actions[i].argType == STRING ){
                actions[i].actionChar( settingValue );
            } else if ( actions[i].argType == BOOLEAN ) {
                actions[i].actionBool( (bool)strcmp( settingValue, "false" ) );
            } else if ( actions[i].argType == SDL_KEY ) {
                KeyBinds_addKeyBindFromStrings( settingName, settingValue );
            }
        }
    }
}
