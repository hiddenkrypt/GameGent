#pragma once

typedef struct{
	int (*itemCount) ();
	void (*getLabel) (int, char*);
	void (*activateItem) (int);
} menu;
