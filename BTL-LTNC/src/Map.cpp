#include "Map.h"

Map::Map() {}

Map::~Map() {}

void Map::Draw(SDL_Renderer* renderer) {

    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (maze[y][x] == 1) {
                SDL_Rect wallRect = { x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE };
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Màu xanh dương
                SDL_RenderFillRect(renderer, &wallRect);
            }
        }
    }
}

