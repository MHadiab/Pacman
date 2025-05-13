#ifndef MOVE_H
#define MOVE_H
#include "raylib.h"
extern int score;
extern Rectangle pacman;
extern int joon;
extern Vector2 pacmanSpeed;
extern Sound Lose;
void InitChatrecters();
void UpdateChatrecters();
void Drawcharecters();
void Unloadcharecters();
void GenerateStars();
#endif