#ifndef PACMAN_H
#define PACMAN_H

#include <SDL.h>
#include <string>


class Pacman {
public:
    Pacman(int x, int y, std::string textureID);

    void Update();
    void Render(SDL_Renderer* renderer);
    void HandleInput(SDL_Event& e);

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
