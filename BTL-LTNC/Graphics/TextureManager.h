#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <string>
#include "SDL.h"

class TextureManager
{
    public:
        TextureManager();
        static TextureManager* GetInstance() { return s_Instance = ( s_Instance != nullptr )? s_Instance : new TextureManager(); }

    protected:

    private:
        static TextureManager* s_Instance;
};

#endif // TEXTUREMANAGER_H
