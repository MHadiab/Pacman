#ifndef MENU_H
#define MENU_H
#include "raylib.h"
extern int score;
extern bool end;
extern int screen;
extern Font customFont;
extern const char *options[4];
extern int selected;
extern char player[100];
void InitMenu();
void show_menu();
void handle_menu();
#endif // MENU_H
