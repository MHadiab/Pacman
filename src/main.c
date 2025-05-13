#include "raylib.h"
#include "menu.h"
#include "game.h"
#include "map.h"
#include "move.h"
#include "stdio.h"
#include "string.h"
char player[100]="player";
Font customFont;
Texture2D bcm;
Texture2D rank_background;
Texture2D rb;
int screen = 0;
int joon = 5;
int score = 0;
char names[100][50];
int scores[100];
int count = 0;
bool end;
void ReadAndSortScores() {
    FILE *fp = fopen("../records.txt", "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    count = 0;
    while (fscanf(fp, "%s %d", names[count], &scores[count]) != EOF && count < 100) {
        count++;
    }
    fclose(fp);
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - 1 - i; j++) {
            if (scores[j] < scores[j + 1]) {
                int tempScore = scores[j];
                scores[j] = scores[j + 1];
                scores[j + 1] = tempScore;
                char tempName[50];
                strcpy(tempName, names[j]);
                strcpy(names[j], names[j + 1]);
                strcpy(names[j + 1], tempName);
            }
        }
    }
}

int main(void) {
    FILE *fp = fopen("../records.txt", "a+");
    Rectangle Loserec = {50, 350, 1400, 420};
    InitAudioDevice();
    Music music = LoadMusicStream("../resources/Theme.mp3");
    PlayMusicStream(music);
    int screenWidth = 1500;
    int screenHeight = 1050;
    InitWindow(screenWidth, screenHeight, "Raylib Custom Font Example");
    customFont = LoadFont("../resources/font.otf");
    bcm = LoadTexture("../resources/14.jpg");
    rank_background = LoadTexture("../resources/rank1.png");
    rb = LoadTexture("../resources/rb.jpg");
    InitGame();
    InitMenu();
    InitChatrecters();
    while (!WindowShouldClose()) {
        SetTargetFPS(60);
        UpdateMusicStream(music);
        BeginDrawing();
        if (screen == 0) {
            handle_menu();
            ClearBackground(RAYWHITE);
            DrawTexture(bcm, 0, 0, WHITE);
            show_menu();
        } else if (screen == 1) {
            DrawTextEx(customFont," press SPACE to stop , press ENTER to continue , press L to give up",(Vector2){550, 45},13,1,WHITE);
            if(IsKeyPressed(KEY_SPACE)){
                EnableEventWaiting();
            }
            if(IsKeyPressed(KEY_ENTER)){
                DisableEventWaiting();
            }
            if(IsKeyPressed(KEY_L)){
                PlaySound(Lose);
                joon = 0;
                screen = 2;
            }
            DrawTextEx(customFont, TextFormat("%i", joon), (Vector2){1400, 30}, 50, 1, WHITE);
            DrawTextEx(customFont, TextFormat("Score: %d", score), (Vector2){60, 25}, 50, 1, WHITE);
            move();
            UpdateChatrecters();
            UpdateGame();
            ClearBackground((Color){0, 5, 60, 0});
            DrawMap();
            Drawcharecters();
            DrawGame();
        } else if (screen == 2) {
            fseek(fp, 0, SEEK_END);
            DrawRectangle(50, 350, 1400, 420, BLACK);
            DrawRectangleLinesEx(Loserec, 10, RED);
            DrawTextEx(customFont, "You Lost! Press Enter to Restart.", (Vector2){90, 450}, 80, 2, RED);
            DrawTextEx(customFont, TextFormat("%s , Your Score is : ", player), (Vector2){210, 550}, 60, 2, RED);
            DrawTextEx(customFont, TextFormat("%d", score), (Vector2){670, 640}, 60, 2, WHITE);
            if (IsKeyPressed(KEY_ENTER)) {
                fprintf(fp, "%s %d\n", player, score);
                fflush(fp);
                screen = 0;
                joon = 5;
                ResetGame();
            }
        } else if (screen == 3) {
            ClearBackground(RAYWHITE);
            ReadAndSortScores();
            DrawTextureEx(rb, (Vector2){0, 0}, 0, 2.7f, WHITE);
            DrawTextEx(customFont, "High Scores", (Vector2){900, 150}, 40, 5, RED);
            DrawTextEx(customFont, "press space key to menu", (Vector2){170, 750}, 40, 3, RED);
            DrawTextureEx(rank_background, (Vector2){50, 280}, 0, 0.75f, WHITE);
            for (int i = 0; i < 10; i++) {
                DrawTextEx(customFont, TextFormat("%d. %s - %d", i + 1, names[i], scores[i]), (Vector2){900, 220.0f + 60.0f * i}, 30, 2, RED);
            }
            if (IsKeyPressed(KEY_SPACE)) {
                screen = 0;
            }
        }
        EndDrawing();
    }

    if (end) {
        UnloadGame();
        UnloadFont(customFont);
        UnloadTexture(bcm);
        UnloadTexture(rank_background);
        UnloadTexture(rb);
        Unloadcharecters();
        fclose(fp);
        UnloadMusicStream(music);
        CloseAudioDevice();
        CloseWindow();
        return 0;
    }
    CloseWindow();
    return 0;
}
