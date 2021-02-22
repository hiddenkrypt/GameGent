#pragma once


typedef enum argumentTypeEnum {
	BOOLEAN,
	STRING,
	SDL_KEY
} argumentType;

typedef struct{
    char *settingName;
    argumentType argType;
	void (*actionBool) (bool);
	void (*actionChar) (char*);
} settingsFileLineAction;
