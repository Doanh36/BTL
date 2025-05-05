#ifndef ENGINE_H
#define ENGINE_H

#include "SDL.h"
#include "SDL_image.h"
#include "Map.h"
#include "MenuManager.h"
#include "SDL_ttf.h"

#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 700

enum GameState {
    STATE_MENU,
    STATE_PLAYING,
    STATE_WIN,
    STATE_LOSE
};

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
        void ResetToSpawn();

        inline bool IsRunning(){return m_IsRunning;}
        inline SDL_Renderer* GetRenderer() { return m_Renderer; }
        bool m_IsPaused = false;
        void CheckGameOver();

    private:
        MenuManager* m_Menu = nullptr;
        TTF_Font* m_Font = nullptr;
        GameState m_CurrentState = STATE_MENU;

        Map* gameMap;
        Engine(){}
        SDL_Window* m_Window;
        SDL_Renderer* m_Renderer;
        bool m_IsRunning;
        static Engine* s_Instance;
};

#endif
