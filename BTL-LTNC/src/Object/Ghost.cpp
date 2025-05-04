#include "Ghost.h"

Ghost::Ghost(Properties* props, Map* map, Pacman* pacman, GhostType type, Ghost* blinky)
    : GameObject(props), m_Map(map), m_Pacman(pacman), m_Type(type), m_Blinky(blinky), m_LastDirection(NONE), m_State(SCATTER) {}

void Ghost::Draw() {
    int drawX = m_Transform->position.X - TILE_SIZE / 2 + 146;
    int drawY = m_Transform->position.Y - TILE_SIZE / 2 + 14;

    TextureManager::GetInstance()->DrawFrame(m_TextureID, drawX, drawY, m_Width, m_Height, 0, 0, m_Flip);
}

void Ghost::Clean() {
    delete m_Transform;
}

void Ghost::Update(float dt) {
    if (m_IsFrightened) {
        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - m_FrightenedStartTime >= m_FrightenedDuration) {
            m_IsFrightened = false;
        }
    }
    int m_Speed = m_IsFrightened ? m_FrightenedSpeed : m_NormalSpeed;

    GhostCollision();
    UpdateState(dt);
    int centerX = (int)(m_Transform->position.X + TILE_SIZE / 2) % TILE_SIZE;
    int centerY = (int)(m_Transform->position.Y + TILE_SIZE / 2) % TILE_SIZE;

    bool onTile = (centerX == 0) && (centerY == 0);

    if (onTile) {
        int gridX = (m_Transform->position.X - TILE_SIZE / 2) / TILE_SIZE;
        int gridY = (m_Transform->position.Y - TILE_SIZE / 2) / TILE_SIZE;

        m_GridX = gridX;
        m_GridY = gridY;

        const int dx[] = { -1, 1, 0, 0 };
        const int dy[] = { 0, 0, -1, 1 };

        int bestDir = -1;
        int minDistance = 1e9;

        int pacX = m_Pacman->GetTileX();
        int pacY = m_Pacman->GetTileY();
        int dirX = m_Pacman->GetDirectionX();
        int dirY = m_Pacman->GetDirectionY();

        m_TargetX = pacX;
        m_TargetY = pacY;

        // Nếu ghost còn trong nhà
        if (gridX >= 9 && gridX <= 10 && gridY >= 7 && gridY <= 10) {
            m_TargetX = houseExitX;
            m_TargetY = houseExitY;
        } else {
            if (m_State == SCATTER) {
                // Scatter mode: mỗi ghost về góc riêng
                switch (m_Type) {
                    case BLINKY:
                        m_TargetX = 19;
                        m_TargetY = 3;
                        break;
                    case PINKY:
                        m_TargetX = 4;
                        m_TargetY = 0;
                        break;
                    case INKY:
                        m_TargetX = 19;
                        m_TargetY = 16;
                        break;
                    case CLYDE:
                        m_TargetX = -1;
                        m_TargetY = 17;
                        break;
                }
            }
            else if (m_State == CHASE) {
                // Chase mode: hành vi đuổi Pacman
                if (m_Type == PINKY) {
                    m_TargetX = pacX + 4 * dirX;
                    m_TargetY = pacY + 4 * dirY;
                }
                else if (m_Type == INKY) {
                    if (m_Blinky) {
                        int aheadX = pacX + 2 * dirX;
                        int aheadY = pacY + 2 * dirY;
                        int blinkyX = m_Blinky->GetTileX();
                        int blinkyY = m_Blinky->GetTileY();

                        m_TargetX = aheadX + (aheadX - blinkyX);
                        m_TargetY = aheadY + (aheadY - blinkyY);
                    }
                }
                else if (m_Type == CLYDE) {
                    int distToPacman = ManhattanDistance(gridX, gridY, pacX, pacY);
                    if (distToPacman > 8) {
                        m_TargetX = pacX;
                        m_TargetY = pacY;
                    } else {
                        m_TargetX = -1;
                        m_TargetY = 17;
                    }
                }
                // Blinky giữ target Pacman
            }
        }

        for (int i = 0; i < 4; ++i) {
            if ((m_LastDirection == LEFT && i == RIGHT) || (m_LastDirection == RIGHT && i == LEFT) ||
                (m_LastDirection == UP && i == DOWN) || (m_LastDirection == DOWN && i == UP)) {
                continue;
            }

            int newX = gridX + dx[i];
            int newY = gridY + dy[i];

            float pixelX = newX * TILE_SIZE + TILE_SIZE / 2.0f;
            float pixelY = newY * TILE_SIZE + TILE_SIZE / 2.0f;

            if (m_Map->CanMove(pixelX, pixelY)) {
                int dist = ManhattanDistance(newX, newY, m_TargetX, m_TargetY);

                if (dist < minDistance) {
                    minDistance = dist;
                    bestDir = i;
                }
            }
        }

        if (bestDir != -1) {
            m_VelocityX = dx[bestDir] * m_Speed;
            m_VelocityY = dy[bestDir] * m_Speed;
            m_LastDirection = static_cast<Direction>(bestDir);
        } else {
            m_VelocityX = 0;
            m_VelocityY = 0;
        }
    }

    float nextX = m_Transform->position.X + m_VelocityX * dt;
    float nextY = m_Transform->position.Y + m_VelocityY * dt;

    if (m_Map->CanMove(nextX, nextY)) {
        m_Transform->position.X = nextX;
        m_Transform->position.Y = nextY;
    } else {
        m_VelocityX = 0;
        m_VelocityY = 0;

        int grid_X = static_cast<int>(m_Transform->position.X / TILE_SIZE);
        int grid_Y = static_cast<int>(m_Transform->position.Y / TILE_SIZE);
        m_Transform->position.X = grid_X * TILE_SIZE + TILE_SIZE / 2;
        m_Transform->position.Y = grid_Y * TILE_SIZE + TILE_SIZE / 2;
    }
}

int Ghost::ManhattanDistance(int x1, int y1, int x2, int y2) const {
    return abs(x1 - x2) + abs(y1 - y2);
}

void Ghost::UpdateState(float dt) {
    m_ModeTimer += dt;

    if (m_ModePhase < m_PhaseDurations.size()) {
        float duration = m_PhaseDurations[m_ModePhase];
        if (m_ModeTimer >= duration) {
            m_State = (m_State == SCATTER) ? CHASE : SCATTER;
            m_ModeTimer = 0.0f;
            m_ModePhase++;
        }
    } else {
        m_State = CHASE;
    }
}

void Ghost::SetFrightened() {
    m_IsFrightened = true;
    m_FrightenedStartTime = SDL_GetTicks();
    m_State = FRIGHTENED;
}

void Ghost::GhostCollision()
{
    int ghostTileX = m_GridX;
    int ghostTileY = m_GridY;
    int pacmanTileX = m_Pacman->GetTileX();
    int pacmanTileY = m_Pacman->GetTileY();

    if (ghostTileX == pacmanTileX && ghostTileY == pacmanTileY && m_State != FRIGHTENED) {
        m_Pacman->SetGameOver(true);
    }
}
