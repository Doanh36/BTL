#include "Pacman.h"
#include "TextureManager.h"


Pacman::Pacman(int x, int y, std::string textureID)
    : m_x(x), m_y(y), m_textureID(textureID), m_speed(2),
      m_frame(0), m_lastFrameTime(SDL_GetTicks()) {}

bool Pacman::CanMove( int newX, int newY, const int maze[MAP_HEIGHT][MAP_WIDTH] ) {
    int left   = (newX - TILE_SIZE / 2) / TILE_SIZE;
    int right  = (newX + TILE_SIZE / 2 - 1) / TILE_SIZE;
    int top    = (newY - TILE_SIZE / 2) / TILE_SIZE;
    int bottom = (newY + TILE_SIZE / 2 - 1) / TILE_SIZE;

    if (left < 0 || right >= MAP_WIDTH || top < 0 || bottom >= MAP_HEIGHT)
        return false;

    return (maze[top][left] == 0 &&
            maze[top][right] == 0 &&
            maze[bottom][left] == 0 &&
            maze[bottom][right] == 0);
}



void Pacman::Update(const int maze[MAP_HEIGHT][MAP_WIDTH]) {

    if (SDL_GetTicks() - m_lastFrameTime > m_animDelay) {
        m_frame = (m_frame + 1) % 2;
        m_lastFrameTime = SDL_GetTicks();
    }

    int col = m_x / TILE_SIZE;
    int row = m_y / TILE_SIZE;

    if (dotMap[row][col] == 1) {
        dotMap[row][col] = 0; 
    }

    bool isAlignedX = (m_x % TILE_SIZE == TILE_SIZE / 2);
    bool isAlignedY = (m_y % TILE_SIZE == TILE_SIZE / 2);

    if (isAlignedX && isAlignedY && nextDir != currentDir) {
        int testX = m_x, testY = m_y;

        switch (nextDir) {
            case UP:    testY -= m_speed; break;
            case DOWN:  testY += m_speed; break;
            case LEFT:  testX -= m_speed; break;
            case RIGHT: testX += m_speed; break;
            default: break;
        }

        if (CanMove(testX, testY, maze)) {
            currentDir = nextDir;
        }
    }


    int newX = m_x, newY = m_y;

    switch (currentDir) {
        case UP:    newY -= m_speed; break;
        case DOWN:  newY += m_speed; break;
        case LEFT:  newX -= m_speed; break;
        case RIGHT: newX += m_speed; break;
        default: break;
    }

    if (CanMove(newX, newY, maze)) {
        m_x = newX;
        m_y = newY;
    }
}


void Pacman::Render(SDL_Renderer* renderer) {
    int drawX = m_x - TILE_SIZE / 2;
    int drawY = m_y - TILE_SIZE / 2;

    int row = 0;

    switch (currentDir) {
        case RIGHT:
            row = 0;
            break;
        case LEFT:
            row = 1;
            break;
        case UP:
            row = 2;
            break;
        case DOWN:
            row = 3;
            break;
    }

    TextureManager::GetInstance()->DrawFrame(
    m_textureID,
    drawX, drawY,
    32, 32,
    row, m_frame,
    SDL_FLIP_NONE
);
}

void Pacman::HandleInput(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
            case SDLK_UP:
                nextDir = UP;
                break;
            case SDLK_DOWN:
                nextDir = DOWN;
                break;
            case SDLK_LEFT:
                nextDir = LEFT;
                break;
            case SDLK_RIGHT:
                nextDir = RIGHT;
                break;
        }
    }
}

