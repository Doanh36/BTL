#ifndef GHOST_H
#define GHOST_H

#include "GameObject.h"
#include "TextureManager.h"
#include "Map.h"
#include <cstdlib>
#include <ctime>

class Ghost : public GameObject
{
public:
    Ghost(Properties* props, Map* map);

    void Draw() override;

    void Update(float dt) override;

    void Clean() override;

    void RandomMove();

private:
    Map* m_Map;
    Vector2D m_Velocity;
    const float m_Speed = 2.0f;
    int m_MoveDelay = 10;
    int m_MoveCounter = 0;
};

#endif // GHOST_H
