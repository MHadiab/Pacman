#ifndef SMART_H
#define SMART_H
#include "raylib.h"
extern Rectangle pacman;
extern int joon;
extern Sound Lose;
extern int screen;
extern float collisionTime;
extern Sound dead;
void InitSmart();
void UpdateSmart();
void DrawSmart();
void UnloadSmart();
#endif // SMART_H