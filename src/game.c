#include "game.h"
#include "map.h"
#include "raylib.h"
#include "math.h"
#include "stdlib.h"
#include "stdio.h"
#include "time.h"
#include "move.h"
Texture2D pacmanOpen;
Texture2D pacmanRight, pacmanLeft, pacmanUp, pacmanDown, currentPacman,pacmancurOpen,pac1,pac2,pac3;
Vector2 pacmanSpeed = {3.5f, 3.5f};
Rectangle pacman;
Texture2D heart;
Texture2D warn;
Texture2D ghost[61];
int currentGhostFrame = 0;
float ghostdeadTime=0;
bool deadStart;
float ghostAnimationTime = 0.0f;
float ghostAnimationSpeed = 0.04f;
float animationTime = 0.0f;
float animationSpeed = 0.2f;
float ghostSpeed;
typedef struct {
    Rectangle soul;
    bool alive;
} souls;
souls ghosts[6];
int waitt;
float collisionTime;
Sound Lose;
Sound dead;
int wich;
static int w3=1;
void InitGame() {
    deadStart= false;
    warn= LoadTexture("../resources/warn.png");
    heart= LoadTexture("../resources/heart1.png");
    ghostSpeed=2.4;
    Lose= LoadSound("../resources/Lose.mp3");
    dead = LoadSound("../resources/dead.mp3");

    for (int i = 1; i <= 61; i++) {
        char Gname[200];
        sprintf(Gname, "../resources/ghost/layer %d.gif", i);
        ghost[i - 1] = LoadTexture(Gname);
    }
    pac1= LoadTexture("../resources/pacman/pacman10.png");
    pac2= LoadTexture("../resources/pacman/pacman11.png");
    pac3= LoadTexture("../resources/pacman/pacman13.png");
    pacmanOpen = LoadTexture("../resources/pacman/pacman1.png");
    pacmanRight = LoadTexture("../resources/pacman/pacman2.png");
    pacmanLeft = LoadTexture("../resources/pacman/pacman5.png");
    pacmanUp = LoadTexture("../resources/pacman/pacman4.png");
    pacmanDown = LoadTexture("../resources/pacman/pacman3.png");
    currentPacman = pacmanRight;
    pacmancurOpen=pacmanOpen;
    pacman = (Rectangle){50, 145, pacmanOpen.width * 0.095f, pacmanOpen.height * 0.095f};
    ghosts[0].soul = (Rectangle){600, 530, ghost[currentGhostFrame].width * 0.12, ghost[currentGhostFrame].height * 0.12};ghosts[0].alive= true;
    ghosts[1].soul = (Rectangle){1100, 150, ghost[currentGhostFrame].width * 0.12, ghost[currentGhostFrame].height * 0.12};ghosts[1].alive= true;
    ghosts[2].soul = (Rectangle){830, 440, ghost[currentGhostFrame].width * 0.12, ghost[currentGhostFrame].height * 0.12};ghosts[2].alive= true;
    ghosts[3].soul = (Rectangle){750, 530, ghost[currentGhostFrame].width * 0.12, ghost[currentGhostFrame].height * 0.12};ghosts[3].alive= true;
    ghosts[4].soul = (Rectangle){400, 650, ghost[currentGhostFrame].width * 0.12, ghost[currentGhostFrame].height * 0.12};ghosts[4].alive= true;
    ghosts[5].soul = (Rectangle){500, 150, ghost[currentGhostFrame].width * 0.12, ghost[currentGhostFrame].height * 0.12};ghosts[5].alive= true;
    waitt=0;
    collisionTime= 0.0f;
    w3=1;
}
    
void move(){
    if(ghosts[5].alive){
        static int w6=2;
        if(ghosts[5].soul.x > 800){
            w6=2;
        }
        if(ghosts[5].soul.y > 800){
            w6=4;
        }
        if (w6 == 1) {
            ghosts[5].soul.x += ghostSpeed;
            if (CheckCollisionWithMap(ghosts[5].soul)) {
                ghosts[5].soul.x -= ghostSpeed;
                srand(time(NULL));
                w6 = rand() % 4 + 1;
            }
        }
        if (w6 == 2) {
            ghosts[5].soul.x -= ghostSpeed;
            if (CheckCollisionWithMap(ghosts[5].soul)) {
                ghosts[5].soul.x += ghostSpeed;
                srand(time(NULL));
                w6 = rand() % 4 + 1;
            }
        }
        if (w6 == 3) {
            ghosts[5].soul.y += ghostSpeed;
            if (CheckCollisionWithMap(ghosts[5].soul)) {
                ghosts[5].soul.y -= ghostSpeed;
                srand(time(NULL));
                w6 = rand() % 4 + 1;
            }
        }
        if (w6 == 4) {
            ghosts[5].soul.y -= ghostSpeed;
            if (CheckCollisionWithMap(ghosts[5].soul)) {
                ghosts[5].soul.y += ghostSpeed;
                srand(time(NULL));
                w6 = rand() % 4 + 1;
            }
        }
    }
    if(ghosts[4].alive){
        static int w5=1;
        if (w5 == 1) {
            ghosts[4].soul.x += ghostSpeed;
            if(ghosts[4].soul.x>1000 && ghosts[4].soul.y>700){
                if(CheckCollisionWithMap(ghosts[4].soul)){
                    w5=4;
                }
            }
            if (CheckCollisionWithMap(ghosts[4].soul)) {
                ghosts[4].soul.x -= ghostSpeed;
                srand(time(NULL));
                w5 = rand() % 4 + 1;
            }
        }
        if (w5 == 2) {
            ghosts[4].soul.x -=ghostSpeed;
            if (CheckCollisionWithMap(ghosts[4].soul)) {
                ghosts[4].soul.x += ghostSpeed;
                srand(time(NULL));
                w5 = rand() % 4 + 1;
            }
        }
        if (w5 == 3) {
            ghosts[4].soul.y +=ghostSpeed;
            if (CheckCollisionWithMap(ghosts[4].soul)) {
                ghosts[4].soul.y -= ghostSpeed;
                srand(time(NULL));
                w5 = rand() % 4 + 1;
            }
        }
        if (w5 == 4) {
            ghosts[4].soul.y -= ghostSpeed;
            if(ghosts[4].soul.x>800){
                if(CheckCollisionWithMap(ghosts[4].soul)){
                    ghosts[4].soul.y += ghostSpeed;
                    w5=2;
                }
            }
            if (CheckCollisionWithMap(ghosts[4].soul)) {
                ghosts[4].soul.y += ghostSpeed;
                srand(time(NULL));
                w5 = rand() % 4 + 1;
            }
        }
    }
    if(ghosts[0].alive){
        static int w1=1;
        if(ghosts[0].soul.y>900){
            w1=4;
        }
        if(ghosts[0].soul.x<500){
            w1=1;
        }
        if (w1 == 1) {
            ghosts[0].soul.x += ghostSpeed;
            if (CheckCollisionWithMap(ghosts[0].soul)) {
                ghosts[0].soul.x -= ghostSpeed;
                srand(time(NULL));
                w1 = rand() % 4 + 1;
            }
        }
        if (w1 == 2) {
            ghosts[0].soul.x -= ghostSpeed;
            if (CheckCollisionWithMap(ghosts[0].soul)) {
                ghosts[0].soul.x += ghostSpeed;
                srand(time(NULL));
                w1 = rand() % 4 + 1;
            }
        }
        if (w1 == 3) {
            ghosts[0].soul.y += ghostSpeed;
            if (CheckCollisionWithMap(ghosts[0].soul)) {
                ghosts[0].soul.y -= ghostSpeed;
                srand(time(NULL));
                w1 = rand() % 4 + 1;
            }
        }
        if (w1 == 4) {
            ghosts[0].soul.y -= ghostSpeed;
            if (CheckCollisionWithMap(ghosts[0].soul)) {
                ghosts[0].soul.y += ghostSpeed;
                srand(time(NULL));
                w1 = rand() % 4 + 1;
            }
        }
    }
    if(ghosts[1].alive){
        static int w2=1;
        if(ghosts[1].soul.x<200){
            w2=1;
        }
        if(ghosts[1].soul.y>700){
            w2=4;
        }
        if (w2 == 1) {
            ghosts[1].soul.x += ghostSpeed;
            if (CheckCollisionWithMap(ghosts[1].soul)) {
                ghosts[1].soul.x -= ghostSpeed;
                srand(time(NULL));
                w2 = rand() % 4 + 1;
            }
        }
        if (w2 == 2) {
            ghosts[1].soul.x -= ghostSpeed;
            if (CheckCollisionWithMap(ghosts[1].soul)) {
                ghosts[1].soul.x += ghostSpeed;
                srand(time(NULL));
                w2 = rand() % 4 + 1;
            }
        }
        if (w2 == 3) {
            ghosts[1].soul.y += ghostSpeed;
            if (CheckCollisionWithMap(ghosts[1].soul)) {
                ghosts[1].soul.y -= ghostSpeed;
                srand(time(NULL));
                w2 = rand() % 4 + 1;
            }
        }
        if (w2 == 4) {
            ghosts[1].soul.y -= ghostSpeed;
            if (CheckCollisionWithMap(ghosts[1].soul)) {
                ghosts[1].soul.y += ghostSpeed;
                srand(time(NULL));
                w2 = rand() % 4 + 1;
            }
        }
    }
    if(ghosts[2].alive){
        //    ghost[2]

        if(w3==1){
            ghosts[2].soul.x += ghostSpeed;
            if(ghosts[2].soul.x >= 1000) {
                w3=2;
            }
        }
        if(w3==2){
            ghosts[2].soul.y-=ghostSpeed;
            if(CheckCollisionWithMap(ghosts[2].soul)){
                ghosts[2].soul.y+=ghostSpeed;
                w3=3;
            }
        }
        if(w3==3){
            ghosts[2].soul.x+=ghostSpeed;
            if(CheckCollisionWithMap(ghosts[2].soul)){
                ghosts[2].soul.x-=ghostSpeed;
                w3=4;
            }
        }
        if(w3==4){
            ghosts[2].soul.x-=ghostSpeed;
            if(ghosts[2].soul.x <= 1000) {
                w3=5;
            }
        }
        if(w3==5){
            ghosts[2].soul.y+=ghostSpeed;
            if(CheckCollisionWithMap(ghosts[2].soul)){
                ghosts[2].soul.y-=ghostSpeed;
                w3=6;
            }
        }
        if(w3==6) {
            ghosts[2].soul.x -= ghostSpeed;
            if (CheckCollisionWithMap(ghosts[2].soul)) {
                ghosts[2].soul.x += ghostSpeed;
                w3 = 1;
            }
        }
    }
    if(ghosts[3].alive){

        static int w4=1;
        if (w4 == 1) {
            ghosts[3].soul.x += ghostSpeed;
            if(CheckCollisionWithMap(ghosts[3].soul)){
                ghosts[3].soul.x -= ghostSpeed;
                w4 = 2;
            }
        }
        if (w4 == 2) {
            ghosts[3].soul.x -= ghostSpeed;
            if(CheckCollisionWithMap(ghosts[3].soul)){
                ghosts[3].soul.x += ghostSpeed;
                w4 = 1;
            }
        }
    }
//-------------------------------------------------------
}
void UpdateGame() {

    if (IsKeyDown(KEY_RIGHT)) {
        currentPacman = pacmanRight;
        pacmancurOpen = pacmanOpen;
        pacman.x += pacmanSpeed.x;
        if (CheckCollisionWithMap(pacman)) {
            pacman.x -= pacmanSpeed.x;
        }
    }
    if (IsKeyDown(KEY_LEFT)) {
        currentPacman = pacmanLeft;
        pacmancurOpen=pac1;
        pacman.x -= pacmanSpeed.x;
        if (CheckCollisionWithMap(pacman)) {
            pacman.x += pacmanSpeed.x;
        }
    }
    if (IsKeyDown(KEY_DOWN)) {
        currentPacman = pacmanDown;
        pacmancurOpen=pac2;
        pacman.y += pacmanSpeed.y;
        if (CheckCollisionWithMap(pacman)) {
            pacman.y -= pacmanSpeed.y;
        }
    }
    if (IsKeyDown(KEY_UP)) {
        currentPacman = pacmanUp;
        pacmancurOpen=pac3;
        pacman.y -= pacmanSpeed.y;
        if (CheckCollisionWithMap(pacman)) {
            pacman.y += pacmanSpeed.y;
        }
    }

    animationTime += GetFrameTime();
    ghostAnimationTime += GetFrameTime();
    if (ghostAnimationTime >= ghostAnimationSpeed) {
        ghostAnimationTime = 0.0f;
        currentGhostFrame = (currentGhostFrame + 1) % 61;
    }
    //joon
    collisionTime += GetFrameTime();
    for(int i = 0; i < 6; i++) {
        if (CheckCollisionRecs(pacman, ghosts[i].soul)) {
            PlaySound(dead);
            if(ghosteat_ability){
                wich=i;
                ghosts[i].soul=(Rectangle){-100,-100,50,50};
                ghosteat_ability= false;
                ghosts[i].alive= false;
                deadStart=true;
                collisionTime=0;
            } else{
                if (collisionTime > 1.2f) {
                    collisionTime = 0;
                    if (joon > 1) {
                        joon--;
                    } else if (joon == 1) {
                        PlaySound(Lose);
                        joon = 0;
                        w3=1;
                        screen = 2;
                    }
                }
            }
        }
    }
    if(deadStart){
        ghostdeadTime+=GetFrameTime();
        if(ghostdeadTime>3 && ghostdeadTime<6){
            switch (wich) {
                case 0:
                    DrawTextureEx(warn, (Vector2){600,530}, 0.0f, 0.18f, WHITE);
                    break;
                case 1:
                    DrawTextureEx(warn, (Vector2){1100,150}, 0.0f, 0.18f, WHITE);
                    break;
                case 2:
                    DrawTextureEx(warn, (Vector2){830,440}, 0.0f, 0.18f, WHITE);
                    break;
                case 3:
                    DrawTextureEx(warn, (Vector2){750,530}, 0.0f, 0.18f, WHITE);
                    break;
                case 4:
                    DrawTextureEx(warn, (Vector2){400,650}, 0.0f, 0.18f, WHITE);
                    break;
                case 5:
                    DrawTextureEx(warn, (Vector2){500,150}, 0.0f, 0.18f, WHITE);
                    break;
            }
        }
        if(ghostdeadTime>6){
                    ghosts[wich].alive= true;
                    switch (wich) {
                            case 0:
                                ghosts[0].soul = (Rectangle){600, 530, ghost[currentGhostFrame].width * 0.12, ghost[currentGhostFrame].height * 0.12};
                                break;
                            case 1:
                                ghosts[1].soul = (Rectangle){1100, 150, ghost[currentGhostFrame].width * 0.12, ghost[currentGhostFrame].height * 0.12};
                                break;
                            case 2:
                                w3=1;
                                ghosts[2].soul = (Rectangle){830, 440, ghost[currentGhostFrame].width * 0.12, ghost[currentGhostFrame].height * 0.12};
                                break;
                            case 3:
                                ghosts[3].soul = (Rectangle){750, 530, ghost[currentGhostFrame].width * 0.12, ghost[currentGhostFrame].height * 0.12};
                                break;
                            case 4:
                                ghosts[4].soul = (Rectangle){400, 650, ghost[currentGhostFrame].width * 0.12, ghost[currentGhostFrame].height * 0.12};
                                break;
                            case 5:
                                ghosts[5].soul = (Rectangle){500, 150, ghost[currentGhostFrame].width * 0.12, ghost[currentGhostFrame].height * 0.12};
                                break;
                    }
                    deadStart=false;
                    ghostdeadTime=0;
                }
            }
}
void DrawGame() {
    ClearBackground(BLACK);
    DrawTextureEx(heart, (Vector2){1345, 35}, 0, 0.035f, WHITE);

    for (int i = 0; i < 6; i++) {
        if(ghosts[i].alive){
            DrawTextureEx(ghost[currentGhostFrame], (Vector2){ghosts[i].soul.x, ghosts[i].soul.y}, 0.0f, 0.12f, WHITE);
        }
    }

    if (fmod(animationTime, animationSpeed * 2) < animationSpeed) {
        DrawTextureEx(pacmancurOpen, (Vector2){pacman.x, pacman.y}, 0.0f, 0.11f, WHITE);
    } else {
        DrawTextureEx(currentPacman, (Vector2){pacman.x, pacman.y}, 0.0f, 0.11f, WHITE);
    }

}

void UnloadGame() {
    for (int i = 0; i < 61; i++) {
        UnloadTexture(ghost[i]);
    }
    UnloadTexture(pacmanOpen);
    UnloadTexture(pacmanRight);
    UnloadTexture(pacmanLeft);
    UnloadTexture(pacmanUp);
    UnloadTexture(pacmanDown);
    UnloadTexture(pac1);
    UnloadTexture(pac2);
    UnloadTexture(pac3);
    UnloadTexture(heart);
    UnloadTexture(warn);
    UnloadSound(Lose);
    UnloadSound(dead);
    CloseAudioDevice();
}

