#include "Engine.h"
#include "TextureManager.h"
#include "Vector2D.h"
#include "Transform.h"
#include "Pacman.h"
#include "Map.h"

const int MAZE_ROWS = 11;
const int MAZE_COLS = 20;
// Vị trí bắt đầu của pacman
const int start_col = 4;
const int start_row = 2;

// Tâm Pacman sẽ nằm giữa tile
int m_x = start_col * TILE_SIZE + TILE_SIZE / 2;
int m_y = start_row * TILE_SIZE + TILE_SIZE / 2;


Engine* Engine::s_Instance = nullptr;
Pacman pacman(m_x , m_y, "pacman");

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
    pacman.Update( maze );
}

void Engine::Render(){
    SDL_SetRenderDrawColor( m_Renderer, 0 , 0 , 0 , 0 );
    SDL_RenderClear(m_Renderer);

    gameMap->Draw(m_Renderer);

    pacman.Render(m_Renderer);

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
