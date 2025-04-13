#include "Engine.h"
#include "TextureManager.h"
#include "Vector2D.h"
#include "Transform.h"
#include "Pacman.h"

const int MAZE_ROWS = 11;
const int MAZE_COLS = 20;

Engine* Engine::s_Instance = nullptr;
Pacman pacman(32 , 32, "pacman"); // "pacman" là id của texture đã load

bool Engine::Init(){
    if ( SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init( IMG_INIT_JPG | IMG_INIT_PNG ) ) {
        SDL_Log( "Failed to initialize SDL: %s" , SDL_GetError() ) ;
        return false;
    }

    m_Window = SDL_CreateWindow( " Pac-man " , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , SCREEN_WIDTH , SCREEN_HEIGHT ,0);
    if ( m_Window == nullptr ) {
        SDL_Log( "Failed to create Window: %s" , SDL_GetError() ) ;
        return false;
    }

    m_Renderer = SDL_CreateRenderer( m_Window , -1 , SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if ( m_Renderer == nullptr ) {
        SDL_Log( "Failed to create Renderer: %s" , SDL_GetError() ) ;
        return false;
    }

    TextureManager::GetInstance()->Load( "pacman" , "assets/pacman.png");

    Transform tf;
    tf.Log();

    gameMap = new Map();

    return m_IsRunning = true;
}

void Engine::Update(){
    pacman.Update();
}

void Engine::Render(){
    SDL_SetRenderDrawColor( m_Renderer, 0 , 0 , 0 , 0 );
    SDL_RenderClear(m_Renderer);

    SDL_SetRenderDrawColor(m_Renderer, 100, 100, 100, 255); // Màu xám

// Vẽ các dòng ngang
for (int i = 0; i <= MAZE_ROWS; i++) {
    SDL_RenderDrawLine(
        m_Renderer,
        0, i * TILE_SIZE,
        MAZE_COLS * TILE_SIZE, i * TILE_SIZE
    );
}

// Vẽ các dòng dọc
for (int j = 0; j <= MAZE_COLS; j++) {
    SDL_RenderDrawLine(
        m_Renderer,
        j * TILE_SIZE, 0,
        j * TILE_SIZE, MAZE_ROWS * TILE_SIZE
    );
}


    gameMap->Draw(m_Renderer);

    pacman.Render(m_Renderer);

    //TextureManager::GetInstance()->Draw( "pacman", 32, 29, 32, 32 );
    SDL_RenderPresent(m_Renderer);
}

void Engine::Events(){
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                Quit();
                break;

            case SDL_KEYDOWN:
            case SDL_KEYUP:
                pacman.HandleInput(event); // 👈 gọi hàm xử lý input của Pacman
                break;
        }
    }
}

bool Engine::Clean(){
    TextureManager::GetInstance()->Clean();
    delete gameMap;
    SDL_DestroyRenderer ( m_Renderer );
    SDL_DestroyWindow ( m_Window );
    IMG_Quit();
    SDL_Quit();

}

void Engine::Quit(){
    m_IsRunning = false;
}
