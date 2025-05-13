#ifndef GAME_H
#define GAME_H
#include "raylib.h"
void InitGame();
void UpdateGame();
void DrawGame();
void UnloadGame();
void move();
void ResetGame();
extern int joon;
extern bool ghosteat_ability;
extern int screen;
#endif // GAME_H


