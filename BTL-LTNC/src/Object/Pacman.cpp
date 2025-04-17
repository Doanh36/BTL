#include "Pacman.h"
#include "TextureManager.h"
#include "Engine.h"
#include "Map.h"

Pacman::Pacman(Properties* props, Map* map)
    : GameObject(props), m_Map(map), m_Velocity(0, 0) {}

void Pacman::Update(float dt) {
    if (SDL_GetTicks() - m_lastFrameTime > m_animDelay) {
        m_frame = (m_frame + 1) % 2;
        m_lastFrameTime = SDL_GetTicks();
    }

    int col = m_Transform->X / TILE_SIZE;
    int row = m_Transform->Y / TILE_SIZE;

    if (dotMap[row][col] == 1) {
        dotMap[row][col] = 0;
    }

    bool isAlignedX = (int(m_Transform->X) % TILE_SIZE == TILE_SIZE / 2);
    bool isAlignedY = (int(m_Transform->Y) % TILE_SIZE == TILE_SIZE / 2);

    if (isAlignedX && isAlignedY && nextDir != currentDir) {
        Vector2D testVel;
        switch (nextDir) {
            case UP:    testVel = Vector2D(0, -1); break;
            case DOWN:  testVel = Vector2D(0, 1); break;
            case LEFT:  testVel = Vector2D(-1, 0); break;
            case RIGHT: testVel = Vector2D(1, 0); break;
            default:    testVel = Vector2D(0, 0); break;
        }

        float testX = m_Transform->X + testVel.X * m_speed;
        float testY = m_Transform->Y + testVel.Y * m_speed;

        if (m_Map->CanMove(testX, testY)) {
            currentDir = nextDir;
        }
    }

    switch (currentDir) {
        case UP:    m_Velocity = Vector2D(0, -1); break;
        case DOWN:  m_Velocity = Vector2D(0, 1); break;
        case LEFT:  m_Velocity = Vector2D(-1, 0); break;
        case RIGHT: m_Velocity = Vector2D(1, 0); break;
        default:    m_Velocity = Vector2D(0, 0); break;
    }

    float newX = m_Transform->X + m_Velocity.X * m_speed;
    float newY = m_Transform->Y + m_Velocity.Y * m_speed;

    if (m_Map->CanMove(newX, newY)) {
        m_Transform->X = newX;
        m_Transform->Y = newY;
    }
}

void Pacman::Draw() {
    int offset_X = (SCREEN_WIDTH - MAP_WIDTH * TILE_SIZE) / 2;
    int offset_Y = (SCREEN_HEIGHT - MAP_HEIGHT * TILE_SIZE) / 2;
    int drawX = m_Transform->X - TILE_SIZE / 2 + 146;
    int drawY = m_Transform->Y - TILE_SIZE / 2 + 14;

    int row = 0;
    switch (currentDir) {
        case RIGHT: row = 0; break;
        case LEFT:  row = 1; break;
        case UP:    row = 2; break;
        case DOWN:  row = 3; break;
    }

    TextureManager::GetInstance()->DrawFrame(m_TextureID,drawX, drawY,m_Width, m_Height,row, m_frame,m_Flip);
}

void Pacman::HandleInput(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
            case SDLK_UP:    nextDir = UP; break;
            case SDLK_DOWN:  nextDir = DOWN; break;
            case SDLK_LEFT:  nextDir = LEFT; break;
            case SDLK_RIGHT: nextDir = RIGHT; break;
        }
    }
}

void Pacman::Clean() {
    delete m_Transform;
}
