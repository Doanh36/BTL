#include "Map.h"
#include "Engine.h"

int dotMap[MAP_HEIGHT][MAP_WIDTH];

Map::Map() {
    totalDots = 149;
    dotsEaten = 0;

    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            if (maze[y][x] == 0 && !(x >= 5 && x <= 13 && y >= 6 && y <= 12) && !(y == 9)) {
                dotMap[y][x] = 1;
            } else {
                dotMap[y][x] = 0;
            }
        }
    }

    dotMap[2][1] = 2;
    dotMap[2][MAP_WIDTH - 2] = 2;
    dotMap[MAP_HEIGHT - 6][1] = 2;
    dotMap[MAP_HEIGHT - 6][MAP_WIDTH - 2] = 2;
}

Map::~Map() {}

void Map::Draw(SDL_Renderer* renderer) {
    int offsetX = (SCREEN_WIDTH - MAP_WIDTH * TILE_SIZE) / 2;
    int offsetY = (SCREEN_HEIGHT - MAP_HEIGHT * TILE_SIZE) / 2;

    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {

            if (maze[y][x] == 1) {
                SDL_Rect wallRect = {
                    offsetX + x * TILE_SIZE,
                    offsetY + y * TILE_SIZE,
                    TILE_SIZE,
                    TILE_SIZE
                };
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Màu xanh dương
                SDL_RenderFillRect(renderer, &wallRect);
            }

            if (dotMap[y][x] == 1) {
                SDL_Rect dotRect = {
                    offsetX + x * TILE_SIZE + TILE_SIZE / 2 - 2,
                    offsetY + y * TILE_SIZE + TILE_SIZE / 2 - 2,
                    4,
                    4
                };
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderFillRect(renderer, &dotRect);
            }

            if (dotMap[y][x] == 2) {
                SDL_Rect powerDotRect = {
                    offsetX + x * TILE_SIZE + TILE_SIZE / 2 - 4,
                    offsetY + y * TILE_SIZE + TILE_SIZE / 2 - 4,
                    8,
                    8
                };
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderFillRect(renderer, &powerDotRect);
            }
        }
    }
}

bool Map::CanMove(float newX, float newY) {
    int left   = (newX - TILE_SIZE / 2) / TILE_SIZE;
    int right  = (newX + TILE_SIZE / 2 - 1) / TILE_SIZE;
    int top    = (newY - TILE_SIZE / 2) / TILE_SIZE;
    int bottom = (newY + TILE_SIZE / 2 - 1) / TILE_SIZE;

    if (left < 0 || right >= MAP_WIDTH || top < 0 || bottom >= MAP_HEIGHT)
        return false;

    return (maze[top][left] == 0 &&
            maze[top][right] == 0 &&
            maze[bottom][left] == 0 &&
            maze[bottom][right] == 0);
}

int Map::EatDot(int x, int y) {
    if (dotMap[y][x] == 1) {
        dotMap[y][x] = 0;
        dotsEaten++;
        return 1;
    } else if (dotMap[y][x] == 2) {
        dotMap[y][x] = 0;
        dotsEaten++;
        return 2;
    }
    return 0;
}

bool Map::HasWon() {
    if (dotsEaten >= totalDots) {
        return true;
    }
    return false;
}
