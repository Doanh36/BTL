#include "Pacman.h"
#include "TextureManager.h"
#include "Map.h"

Pacman::Pacman(int x, int y, std::string textureID)
    : m_x(x), m_y(y), m_textureID(textureID), m_speed(2),
      m_frame(0), m_lastFrameTime(SDL_GetTicks()) {}

void Pacman::Update() {
    // Cập nhật animation mở – đóng miệng
    if (SDL_GetTicks() - m_lastFrameTime >     case DOWN:  m_y += m_speed; break;
    case LEFT:  m_x -= m_speed; break;m_animDelay) {
        m_frame = (m_frame + 1) % 2; // 2 frame
        m_lastFrameTime = SDL_GetTicks();
    }

    switch (m_direction) {
    case UP:    m_y -= m_speed; break;

    case RIGHT: m_x += m_speed; break;
    default: break;
    }
}

void Pacman::Render(SDL_Renderer* renderer) {
    TextureManager::GetInstance()->DrawFrame(
        m_textureID,
        m_x, m_y,
        32, 32,         // kích thước frame
        0, m_frame,     // row, frame
        SDL_FLIP_NONE
    );
}

void Pacman::HandleInput(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN) {
    switch (e.key.keysym.sym) {
        case SDLK_UP:    m_direction = UP; break;
        case SDLK_DOWN:  m_direction = DOWN; break;
        case SDLK_LEFT:  m_direction = LEFT; break;
        case SDLK_RIGHT: m_direction = RIGHT; break;
    }
}
}
