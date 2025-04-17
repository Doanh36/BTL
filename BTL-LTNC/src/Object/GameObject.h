#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL.h>
#include "Transform.h"
#include <vector>

struct Properties {
    std::string TextureID;
    int Width, Height;
    float X, Y;
    SDL_RendererFlip Flip;

    Properties(std::string textureID, int x, int y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE)
        : TextureID(textureID), X(x), Y(y), Width(width), Height(height), Flip(flip) {}
};


class GameObject
{
    public:
        GameObject(Properties* props)
    : m_TextureID(props->TextureID),
      m_Width(props->Width),
      m_Height(props->Height),
      m_Flip(props->Flip)
{
    m_Transform = new Transform(props->X, props->Y);
}

        virtual ~GameObject() {}

        virtual void Draw() = 0;
        virtual void Update( float dt ) = 0;
        virtual void Clean() = 0;

    protected:
        Transform* m_Transform;
        int m_Width ,m_Height;
        std::string m_TextureID;
        SDL_RendererFlip m_Flip;

    private:
};

#endif // GAMEOBJECT_H
