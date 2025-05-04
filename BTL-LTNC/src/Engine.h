#ifndef ENGINE_H
#define ENGINE_H

#include "SDL.h"
#include "SDL_image.h"
#include "Map.h"

#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 700

class Engine {

    public:
        static Engine* GetInstance(){
            return s_Instance = (s_Instance != nullptr)? s_Instance : new Engine();
        }

        bool Init();
        bool Clean();
        void Quit();

        void Update();
        void Render();
        void Events();
        void ResetGame();

        inline bool IsRunning(){return m_IsRunning;}
        inline SDL_Renderer* GetRenderer() { return m_Renderer; }
        bool m_IsPaused = false;

    private:
        Map* gameMap;
        Engine(){}
        SDL_Window* m_Window;
        SDL_Renderer* m_Renderer;
        bool m_IsRunning;
        static Engine* s_Instance;
};

#endif
