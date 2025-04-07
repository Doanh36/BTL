#ifndef MAP_H
#define MAP_H

#include <SDL.h>

const int MAP_WIDTH = 20;
const int MAP_HEIGHT = 11;
extern int maze[MAP_HEIGHT][MAP_WIDTH];

class Map {
public:
    Map();
    ~Map();
    void Draw(SDL_Renderer* renderer);
};

#endif
