#include "raylib.h"
#include "stdio.h"
#include "map.h"
#include "time.h"
#include "stdlib.h"
#include "game.h"
#include "smart.h"
#include "move.h"
int currentcherryFrame = 0;
int currentappleFrame = 0;
int currentmushFrame = 0;
int currentpepperFrame = 0;
float fruitAnimationTime = 0.0f;
float fruitAnimationSpeed = 0.05f;
float animationfruitTime = 0.0f;
float FcollisionTime=0.0f;
Texture2D cherry[17];
Texture2D apple[31];
Texture2D mush[30];
Texture2D pepperr[8];
Vector2 cherryPosition;
Rectangle CherryRec;
bool cherryeat;
bool mushroomeat;
bool peppereat;
bool appleeat;
bool ghosteat_ability;
Vector2 applePosition;
Rectangle AppleRec;
Vector2 mushPosition;
Rectangle MushRec;
Vector2 pepperPosition;
Rectangle PepperRec;

Rectangle Fruits[4];
typedef struct {
    Vector2 position;
    Rectangle starrec;
    int currentSFrame;
    bool eaten;
} Star;
int StarCount;
Star stars[10];
Texture2D starFrames[28];
Sound starsound;
Sound goal;
Sound mive;
void GenerateStars(){

    int count = 0;
    while (count < 10) {
        Vector2 pos = {GetRandomValue(100, 1400), GetRandomValue(100, 1020)};
        Rectangle starRec = {pos.x, pos.y, 40, 40};
        bool collision = false;

        if (CheckCollisionWithMap(starRec)) {
            continue;
        }

//        تداخل با ستاره های دیگه
        for (int i = 0; i < count; i++) {
            Rectangle existingStarRec = {stars[i].position.x, stars[i].position.y, 50, 50};
            if (CheckCollisionRecs(starRec, existingStarRec ) || CheckCollisionRecs(starRec, pacman)) {
                collision = true;
                break;
            }
        }

        if (!collision) {
            stars[count].position = pos;
            stars[count].currentSFrame = 0;
            stars[count].starrec=(Rectangle){stars[count].position.x, stars[count].position.y, 50, 50};
            stars[count].eaten= false;
            count++;
        }
    }
    printf("Generated Stars: %d\n", count);
    if (count < 10) { GenerateStars(); }
}


void GenerateFruits() {
    int countFruit = 0;
    while (countFruit < 4) {
        bool colfruit = false;
        Vector2 temp = {GetRandomValue(100, 1400), GetRandomValue(100, 1020)};
        Rectangle fruitrectemp = {temp.x, temp.y, 60, 60};
        if (CheckCollisionWithMap(fruitrectemp)) {
            continue;
        }

        for (int j = 0; j < countFruit; j++) {
            if (CheckCollisionRecs(fruitrectemp, Fruits[j])) {
                colfruit = true;
                break;
            }
        }

        if (!colfruit) {
            if (countFruit == 0) {
                applePosition = temp;
                Fruits[countFruit] = fruitrectemp;
                countFruit++;
            } else if (countFruit == 1) {
                mushPosition = temp;
                Fruits[countFruit] = fruitrectemp;
                countFruit++;
            } else if (countFruit == 2) {
                pepperPosition = temp;
                Fruits[countFruit] = fruitrectemp;
                countFruit++;
            } else if (countFruit == 3) {
                cherryPosition = temp;
                Fruits[countFruit] = fruitrectemp;
                countFruit++;
            }

        }
    }
    printf("Generated Fruits: %d\n", countFruit);
    if (countFruit < 4) {
        GenerateFruits();
    }
}

void InitChatrecters(){
    InitSmart();
    appleeat= false;mushroomeat= false;peppereat= false;cherryeat= false;
    CherryRec=(Rectangle){cherryPosition.x, cherryPosition.y, 50, 50};
    AppleRec=(Rectangle){applePosition.x, applePosition.y, 50, 50};
    PepperRec=(Rectangle){pepperPosition.x, pepperPosition.y, 50, 50};
    MushRec=(Rectangle){mushPosition.x, mushPosition.y, 50, 50};
//    -----------
    goal= LoadSound("../resources/goal.wav");
    starsound= LoadSound("../resources/star.wav");
    mive = LoadSound("../resources/mive1.mp3");
    StarCount=10;
    srand(time(NULL));
    for (int i = 1; i <= 28; i++) {
        char sname[200];
        sprintf(sname, "../resources/star/Layer %d.png", i);
        starFrames[i - 1] = LoadTexture(sname);
    }

    for (int i = 1; i <= 31; i++) {
        char aname[200];
        sprintf(aname, "../resources/apple/Layer %d.png", i);
        apple[i - 1] = LoadTexture(aname);
    }
    for (int i = 1; i <= 30; i++) {
        char mname[200];
        sprintf(mname, "../resources/mush/Layer %d.png", i);
        mush[i - 1] = LoadTexture(mname);
    }
    for (int i = 1; i <= 17; i++) {
        char cname[200];
        sprintf(cname, "../resources/Cherry/Layer %d.png", i);
        cherry[i - 1] = LoadTexture(cname);
    }
    for (int i = 1; i <= 8; i++) {
        char pname[200];
        sprintf(pname, "../resources/pepper/Layer %d.png", i);
        pepperr[i - 1] = LoadTexture(pname);
    }
    GenerateStars();
    GenerateFruits();
    AppleRec = (Rectangle){applePosition.x, applePosition.y, 50, 50};
    CherryRec = (Rectangle){cherryPosition.x, cherryPosition.y, 50, 50};
    MushRec = (Rectangle){mushPosition.x, mushPosition.y, 50, 50};
    PepperRec = (Rectangle){pepperPosition.x, pepperPosition.y, 50, 50};
    ghosteat_ability= false;
}

void UpdateChatrecters() {
    UpdateSmart();
    animationfruitTime += GetFrameTime();
    fruitAnimationTime += GetFrameTime();
    if (fruitAnimationTime >= fruitAnimationSpeed) {
        fruitAnimationTime = 0.0f;
        currentappleFrame = (currentappleFrame + 1) % 31;
        currentmushFrame = (currentmushFrame + 1) % 30;
        currentcherryFrame = (currentcherryFrame + 1) % 17;
        currentpepperFrame = (currentpepperFrame + 1) % 8;

        for (int i = 0; i < 10; i++) {
            stars[i].currentSFrame = (stars[i].currentSFrame + 1) % 28;
        }
    }

//    -scores
    for(int i=0;i<10;i++){
        if(CheckCollisionRecs(stars[i].starrec,pacman)){
            PlaySound(starsound);
            stars[i].eaten=true;
            stars[i].starrec=(Rectangle){-100,-100,50,50};
            score+=10;
            StarCount--;

        }
    }
    if(StarCount==0){
        PlaySound(goal);
        GenerateStars();
        StarCount=10;
    }
//    Fruits conditions
    FcollisionTime += GetFrameTime();
    if(CheckCollisionRecs(AppleRec,pacman)){
        AppleRec=(Rectangle){-100,-100,50,50};
        appleeat=true;
        PlaySound(mive);
        if(FcollisionTime>0.1){
            FcollisionTime=0;
            joon++;
        }
    }
    if(CheckCollisionRecs(PepperRec,pacman)){
        PepperRec=(Rectangle){-100,-100,50,50};
        peppereat=true;
        PlaySound(mive);
        if(FcollisionTime>0.1){
            FcollisionTime=0;
            pacmanSpeed.x+=1;
            pacmanSpeed.y+=1;
        }
    }
    if(CheckCollisionRecs(MushRec,pacman)){
        MushRec=(Rectangle){-100,-100,50,50};
        mushroomeat=true;
        PlaySound(mive);
        if(FcollisionTime>0.1){
            FcollisionTime=0;
            if(joon>1){
                joon--;
            } else{
                PlaySound(Lose);
                joon=0;
                screen=2;
            }
        }
    }
    if(CheckCollisionRecs(CherryRec,pacman)){
        CherryRec=(Rectangle){-100,-100,50,50};
        cherryeat=true;
        PlaySound(mive);
        if(FcollisionTime>0.1){
            FcollisionTime=0;
            ghosteat_ability= true;
        }
    }

}

void Drawcharecters(){
    if(!appleeat){DrawTextureEx(apple[currentappleFrame], applePosition, 0.0f, 0.18f, WHITE);}
    if(!mushroomeat){DrawTextureEx(mush[currentmushFrame], mushPosition, 0.0f, 0.12f, WHITE);}
    if(!peppereat){DrawTextureEx(pepperr[currentpepperFrame], pepperPosition, 0.0f, 0.13f, WHITE);}
    if(!cherryeat){DrawTextureEx(cherry[currentcherryFrame], cherryPosition, 0.0f, 0.155f, WHITE);}

    for (int i = 0; i < 10; i++) {
        if(stars[i].eaten==false){
            DrawTextureEx(starFrames[stars[i].currentSFrame], stars[i].position, 0.0f, 0.14f, WHITE);
        }
    }
    DrawSmart();
}
void Unloadcharecters(){
    for (int i = 0; i < 31; i++) {
        UnloadTexture(apple[i]);
    }
    for (int i = 0; i < 30; i++) {
        UnloadTexture(mush[i]);
    }
    for (int i = 0; i < 8; i++) {
        UnloadTexture(pepperr[i]);
    }
    for (int i = 0; i < 17; i++) {
        UnloadTexture(cherry[i]);
    }
    for (int i = 0; i < 28; i++) {
        UnloadTexture(starFrames[i]);
    }
    UnloadSound(mive);
    UnloadSound(goal);
    UnloadSound(starsound);
    UnloadSmart();
    CloseAudioDevice();
}


void ResetGame() {
    score=0;
    pacmanSpeed = (Vector2){3.5f, 3.5f};
    currentcherryFrame = 0;
    currentappleFrame = 0;
    currentmushFrame = 0;
    currentpepperFrame = 0;
    fruitAnimationTime = 0.0f;
    animationfruitTime = 0.0f;
    DisableEventWaiting();
    InitChatrecters();
    InitGame();
}

