
#include "menu.h"
#include "raylib.h"
#include "string.h"
#include "game.h"

const char *options[4] = {"START", "SCORES", "RECORD", "EXIT"};

int selected = 0;
Sound menuSound;

void InitMenu() {
    end = false;
    menuSound = LoadSound("../resources/select.mp3");
}

void show_menu() {
    for (int i = 0; i < 4; i++) {
        if (i == selected) DrawTextEx(customFont, TextFormat("%s", options[i]), (Vector2){350, 300 + 100 * i}, 70, 2, WHITE);
        else DrawTextEx(customFont, options[i], (Vector2){350, 300 + 100 * i}, 60, 2, WHITE);
    }
    DrawTextEx(customFont, "Enter your name:", (Vector2){860, 400}, 30, 2, WHITE);
    DrawRectangle(850, 450, 300, 50, LIGHTGRAY);
    DrawText(player, 860, 460, 30, BLACK);

    int key = GetCharPressed();
    while (key > 0) {
        if ((key >= 32) && (key <= 125) && (strlen(player) < 49)) {
            int len = strlen(player);
            player[len] = (char)key;
            player[len + 1] = '\0';
        }
        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE)) {
        int len = strlen(player);
        if (len > 0) {
            player[len - 1] = '\0';
        }
    }
}

void handle_menu() {
    bool optionChanged = false;
    if (IsKeyPressed(KEY_DOWN)) {
        selected++;
        optionChanged = true;
    }
    if (IsKeyPressed(KEY_UP)) {
        selected--;
        optionChanged = true;
    }
    if (optionChanged) {
        PlaySound(menuSound);
    }

    if (selected < 0) selected = 3;
    if (selected > 3) selected = 0;

    if (IsKeyPressed(KEY_ENTER)) {
        if (selected == 3) {
            end = true;
            CloseWindow();
        }
        if (selected == 0) {
            screen = 1;
            SetTargetFPS(60);
        }
        if (selected == 1) {
            screen = 3;
        }
    }
}
