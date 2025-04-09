#ifndef PACMAN_H
#define PACMAN_H

#include <SDL.h>
#include <string>
#include "Map.h"


class Pacman {
public:
    Pacman(int x, int y, std::string textureID);

    void Update(const int maze[MAP_HEIGHT][MAP_WIDTH]);
    void Render(SDL_Renderer* renderer);
    void HandleInput(SDL_Event& e);
    bool CanMove(int newX, int newY, const int maze[MAP_HEIGHT][MAP_WIDTH]);

private:
    enum Direction { NONE, UP, DOWN, LEFT, RIGHT };
    Direction m_direction = NONE;
    int m_x, m_y;
    int m_speed;

    int m_frame;
    Uint32 m_lastFrameTime;
    const int m_animDelay = 80;

    std::string m_textureID;
};

#endif
