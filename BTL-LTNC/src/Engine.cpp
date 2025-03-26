#include "Engine.h"
#include "TextureManager.h"

Engine* Engine::s_Instance = nullptr;

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

    //TextureManager::GetInstance()->Load( "yellow" , "assets/Spongebob.png" );

    gameMap = new Map();

    return m_IsRunning = true;
}

void Engine::Update(){
    //SDL_Log("SDL is working");
    //SDL_Delay(100);
}

void Engine::Render(){
    SDL_SetRenderDrawColor( m_Renderer, 0 , 0 , 0 , 0 );
    SDL_RenderClear(m_Renderer);

    gameMap->Draw(m_Renderer);

    TextureManager::GetInstance()->Draw( "yellow", 100, 100, 495 , 350 );
    SDL_RenderPresent(m_Renderer);
}

void Engine::Events(){
    SDL_Event event;
    SDL_PollEvent ( &event );
    switch ( event.type ) {
        case SDL_QUIT:;
        Quit();
        break;
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
