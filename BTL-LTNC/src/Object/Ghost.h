#ifndef GHOST_H
#define GHOST_H

#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"
#include "Pacman.h"
#include <cmath>
#include <iostream>

enum GhostState {
    CHASE,
    SCATTER,
    FRIGHTENED,
};

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
    void UpdateState(float dt);
    void SetFrightened();
    void GhostCollision();
    void Reset();

    const int BLINKY_START_X = 304;
    const int BLINKY_START_Y = 240;

    const int PINKY_START_X = 304;
    const int PINKY_START_Y = 272;

    const int INKY_START_X = 304;
    const int INKY_START_Y = 304;

    const int CLYDE_START_X = 336;
    const int CLYDE_START_Y = 304;

private:
    Pacman* m_Pacman;
    Map* m_Map;
    GhostType m_Type;
    Ghost* m_Blinky = nullptr;
    Direction m_LastDirection;
    GhostState m_State;

    bool m_IsFrightened = false;
    Uint32 m_FrightenedStartTime = 0;
    Uint32 m_FrightenedDuration = 6000; // 6 seconds
    int m_NormalSpeed = 130;
    int m_FrightenedSpeed = 65;

    int m_GridX;
    int m_GridY;

    int m_TargetX = 0, m_TargetY = 0;

    const int houseExitX = 9;
    const int houseExitY = 7;

    float m_VelocityX = 0;
    float m_VelocityY = 0;

    const int m_Speed = 130;

    float m_ModeTimer = 0.0f;
    int m_ModePhase = 0;

    const std::vector<float> m_PhaseDurations = {
        7.0f, 20.0f,
        7.0f, 20.0f,
        5.0f, 20.0f,
    };

};

#endif
