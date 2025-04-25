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

class Ghost : public GameObject {
public:
    Ghost(Properties* props, Map* map, Pacman* pacman);

    virtual void Update(float dt) override;
    virtual void Draw() override;
    virtual void Clean() override;
    int ManhattanDistance(int x1, int y1, int x2, int y2) const;

private:
    Pacman* m_Pacman;
    Map* m_Map;
    Direction m_LastDirection;

    int m_GridX;
    int m_GridY;

    float m_VelocityX = 0;
    float m_VelocityY = 0;

    const int m_Speed = 130; 
};

#endif
