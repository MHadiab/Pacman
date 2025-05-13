#include "stdio.h"
#include "raylib.h"
#include "map.h"
#include "smart.h"
Texture2D smart[61];
float smartAnimationTime = 0.0f;
float smartAnimationSpeed = 0.04f;
int currentSmartFrame = 0;
bool salive;
Rectangle Smart_Ghost;
int x;
void InitSmart(){
    Smart_Ghost=(Rectangle){1350,440,40,40};
    salive= true;
    for (int i = 1; i <= 61; i++) {
        char sgname[200];
        sprintf(sgname, "../resources/smart/layer %d.png", i);
        smart[i - 1] = LoadTexture(sgname);
    }
}
void UpdateSmart(){
    smartAnimationTime += GetFrameTime();
    if (smartAnimationTime >= smartAnimationSpeed) {
        smartAnimationTime = 0.0f;
        currentSmartFrame = (currentSmartFrame + 1) % 61;
    }
    if(pacman.x>Smart_Ghost.x){
        Smart_Ghost.x+=2.3f;
        if(CheckCollisionWithMap(Smart_Ghost)){
            Smart_Ghost.x-=2.3f;
        }
    }
    if(pacman.x<Smart_Ghost.x) {
        Smart_Ghost.x -= 2.3f;
        if (CheckCollisionWithMap(Smart_Ghost)) {
            Smart_Ghost.x += 2.3f;
        }
    }
    if(pacman.y>Smart_Ghost.y){
        Smart_Ghost.y+=2.3f;
        if(CheckCollisionWithMap(Smart_Ghost)) {
            Smart_Ghost.y -= 2.3f;
        }
    }
    if(pacman.y<Smart_Ghost.y){
        Smart_Ghost.y-=2.3f;
        if(CheckCollisionWithMap(Smart_Ghost)) {
            Smart_Ghost.y += 2.3f;
        }
    }
    if(x>=2){
        if(Smart_Ghost.x>pacman.x){
            Smart_Ghost.x-=2.3f;
        } else{
            Smart_Ghost.x+=2.3f;
        }
    }

    collisionTime+=GetFrameTime();
    if (CheckCollisionRecs(pacman, Smart_Ghost)) {
        PlaySound(dead);
        if(collisionTime > 2) {
            if (joon > 1) {
                collisionTime=0;
                joon--;
            } else if (joon == 1) {
                PlaySound(Lose);
                joon = 0;
                screen = 2;
            }
        }

    }
}
void DrawSmart(){
    if(salive){
        DrawTextureEx(smart[currentSmartFrame], (Vector2){Smart_Ghost.x, Smart_Ghost.y}, 0.0f, 0.12f, WHITE);
    }
}
void UnloadSmart(){
    for (int i = 0; i < 61; i++) {
        UnloadTexture(smart[i]);
    }
}