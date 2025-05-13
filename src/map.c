#include "raylib.h"
#include "map.h"
Rectangle walls[] = {
        {1, 100, 1499, 40},
        {1, 1010, 1499, 40},
        {1, 140, 40, 870},
        {1460, 140, 40, 870},

        {700, 140, 80, 197},
        {850, 197, 235, 136},
        {1150, 197, 235, 136},
        {100, 197, 235, 136},
        {400, 197, 235, 136},
        {1150, 390, 235, 40},
        {100, 390, 235, 40},
        {400, 390, 40, 250},
        {1050, 390, 40, 250},
        {500, 390, 490, 40},
        {440, 485, 180, 40},
        {870, 485, 180, 40},
        {685, 430, 120, 95},
        {1150, 490, 310, 150},
        {41, 490, 300, 150},
        {500, 580, 185, 40},
        {500, 620, 40, 100},
        {800, 580, 185, 40},
        {944, 620, 40, 100},
        {540, 680, 404, 40},
        {400, 700, 40, 150},
        {1050, 700, 40, 150},
        {500, 774, 484, 40},
        {1150, 700, 310, 150},
        {41, 700, 300, 150},
        {117, 910, 484, 40},
        {900, 910, 484, 40},
        {670, 814, 150, 138}
};

int wallCount = sizeof(walls) / sizeof(walls[0]);

bool CheckCollisionWithMap(Rectangle pacman) {
    for (int i = 0; i < wallCount; i++) {
        if (CheckCollisionRecs(pacman, walls[i])) {
            return true;
        }
    }
    return false;
}


void DrawMap() {
    for (int i = 0; i < wallCount; i++) {
        DrawRectangleRec(walls[i], DARKBLUE);
        DrawRectangleLinesEx(walls[i], 2, YELLOW);
    }
}
