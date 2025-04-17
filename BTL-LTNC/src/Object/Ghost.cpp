#include "Ghost.h"

Ghost::Ghost(Properties* props, Map* map) : GameObject(props), m_Map(map), m_Velocity(0,0) {
    srand(time(0)); // dùng cho di chuyển ngẫu nhiên
}

void Ghost::Draw()
{
    int drawX = m_Transform->X - TILE_SIZE / 2 + 146;
    int drawY = m_Transform->Y - TILE_SIZE / 2 + 14;

    TextureManager::GetInstance()->DrawFrame(m_TextureID,drawX, drawY,m_Width, m_Height,0, 0,m_Flip);
}

void Ghost::Update(float dt)
{
    m_MoveCounter++;
    if (m_MoveCounter >= m_MoveDelay) {
        RandomMove();
        m_MoveCounter = 0;
    }

    float newX = m_Transform->X + m_Velocity.X * m_Speed;
    float newY = m_Transform->Y + m_Velocity.Y * m_Speed;

    if (m_Map->CanMove(newX, newY)) {
        m_Transform->X = newX;
        m_Transform->Y = newY;
    }
}

void Ghost::Clean()
{

}

void Ghost::RandomMove()
{
    Vector2D directions[] = {
        Vector2D(-1, 0), Vector2D(1, 0),
        Vector2D(0, -1), Vector2D(0, 1)
    };

    std::vector<Vector2D> validDirs;

    for (auto& dir : directions) {
        float testX = m_Transform->X + dir.X * TILE_SIZE;
        float testY = m_Transform->Y + dir.Y * TILE_SIZE;

        if (m_Map->CanMove(testX, testY)) {
            validDirs.push_back(dir);
        }
    }

    if (!validDirs.empty()) {
        int idx = rand() % validDirs.size();
        m_Velocity = validDirs[idx];
    } else {
        m_Velocity = Vector2D(0, 0); // đứng im nếu bị kẹt
    }
}
