#ifndef GHOST_H
#define GHOST_H

#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"
#include "Pacman.h"
#include <cmath>
#include <iostream>

enum Direction {
    LEFT = 0,
    RIGHT = 1,
    UP = 2,
    DOWN = 3,
    NONE = -1
};

enum GhostType {
    BLINKY,
    PINKY,
    INKY,
    CLYDE,
};

class Ghost : public GameObject {
public:
    Ghost(Properties* props, Map* map, Pacman* pacman, GhostType type, Ghost* blinky = nullptr);

    virtual void Update(float dt) override;
    virtual void Draw() override;
    virtual void Clean() override;

    int ManhattanDistance(int x1, int y1, int x2, int y2) const;

    int GetTileX() const { return m_GridX; }
    int GetTileY() const { return m_GridY; }

private:
    Pacman* m_Pacman;
    Map* m_Map;
    GhostType m_Type;
    Ghost* m_Blinky = nullptr; 
    Direction m_LastDirection;

    int m_GridX;
    int m_GridY;

    float m_VelocityX = 0;
    float m_VelocityY = 0;

    const int m_Speed = 130; 
};

#endif
