#ifndef PACMAN_H
#define PACMAN_H

#include "GameObject.h"
#include "Map.h"

const int start_col = 9; //9
const int start_row = 15; //15
const int m_x = start_col * TILE_SIZE + TILE_SIZE / 2;
const int m_y = start_row * TILE_SIZE + TILE_SIZE / 2;

class Pacman : public GameObject {
public:
    Pacman(Properties* props, Map* map);
    virtual void Draw() override;
    virtual void Update(float dt) override;
    virtual void Clean() override;
    void HandleInput(SDL_Event& e);
    int GetTileX() const;
    int GetTileY() const;
    int GetDirectionX() const;
    int GetDirectionY() const;

private:
    Map* m_Map;
    enum Direction { NONE, UP, DOWN, LEFT, RIGHT };
    Direction currentDir = NONE;
    Direction nextDir = NONE;
    Vector2D m_Velocity;
    int m_speed = 2;
    int m_frame = 0;
    Uint32 m_lastFrameTime = 0;
    const int m_animDelay = 80;
};

#endif
