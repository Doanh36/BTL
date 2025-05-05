#include "Engine.h"
#include "TextureManager.h"
#include "Vector2D.h"
#include "Transform.h"
#include "Pacman.h"
#include "Map.h"
#include "Ghost.h"

Engine* Engine::s_Instance = nullptr;

Properties* pacmanProps = new Properties(std::string("pacman"), m_x, m_y, TILE_SIZE, TILE_SIZE);
Map* m_Map = new Map();
Pacman* pacman = new Pacman(pacmanProps, m_Map);

Ghost* blinky = new Ghost(new Properties("blinky", 304 , 240, TILE_SIZE, TILE_SIZE), m_Map, pacman, BLINKY);
Ghost* pinky = new Ghost(new Properties("pinky", 304, 272, TILE_SIZE, TILE_SIZE), m_Map, pacman, PINKY);
Ghost* inky = new Ghost(new Properties("inky", 304, 304, TILE_SIZE, TILE_SIZE), m_Map, pacman, INKY, blinky);
Ghost* clyde = new Ghost(new Properties("clyde", 336, 304, TILE_SIZE, TILE_SIZE), m_Map, pacman, CLYDE);

std::vector<Ghost*> ghostList = { blinky, pinky, inky, clyde };

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

    TTF_Init();
    m_Font = TTF_OpenFont("assets/consola.ttf", 48);
    if (!m_Font) {
        SDL_Log("Failed to load font: %s", TTF_GetError());
        return false;
    }
    m_Menu = new MenuManager(m_Renderer, m_Font);
    m_CurrentState = STATE_MENU;

    TextureManager::GetInstance()->Load( "pacman" , "assets/pacman.png");
    TextureManager::GetInstance()->Load( "blinky" , "assets/blinky animation.png" );
    TextureManager::GetInstance()->Load( "pinky" , "assets/pinky animation.png" );
    TextureManager::GetInstance()->Load( "inky" , "assets/inky animation.png" );
    TextureManager::GetInstance()->Load( "clyde" , "assets/clyde animation.png" );

    pacman->SetGhosts(ghostList);

    Transform tf;
    tf.Log();
    return m_IsRunning = true;
}

void Engine::Update(){
    if (m_CurrentState == STATE_MENU) return;
    if (m_IsPaused) return;

    pacman->Update(0.016f);
    blinky->Update(0.016f);
    pinky->Update(0.016f);
    inky->Update(0.016f);
    clyde->Update(0.016f);

    CheckGameOver();
}

void Engine::Render(){

    SDL_SetRenderDrawColor( m_Renderer, 0 , 0 , 0 , 0 );
    SDL_RenderClear(m_Renderer);

    switch ( m_CurrentState ) {
        case STATE_MENU:
            m_Menu->render();
            m_Menu->RenderTitle();
            break;
        case STATE_PLAYING:
            m_Map->Draw(m_Renderer);
            pacman->Draw();
            blinky->Draw();
            pinky->Draw();
            inky->Draw();
            clyde->Draw();
            break;
        case STATE_WIN:
            m_Menu->render();
            m_Menu->RenderWIN();
            break;
        case STATE_LOSE:
            m_Menu->render();
            m_Menu->RenderLOSE();
            break;
    }

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
                if (event.key.keysym.sym == SDLK_SPACE) {
                    m_IsPaused = !m_IsPaused;
                }
                if (!m_IsPaused) {
                    pacman->HandleInput(event);
                }
                break;

            case SDL_KEYUP:
                if (!m_IsPaused) {
                    pacman->HandleInput(event);
                }
                break;
        }

        if (m_CurrentState == STATE_MENU || m_CurrentState == STATE_WIN || m_CurrentState == STATE_LOSE) {
            bool quit = false;
            bool startGame = false;
            m_Menu->handleEvent(event, quit, startGame);
            if (quit) Quit();
            if (startGame) {
                ResetGame();
                m_CurrentState = STATE_PLAYING;
            };
        } else if (m_CurrentState == STATE_PLAYING) {}
    }
}

bool Engine::Clean(){
    TextureManager::GetInstance()->Clean();
    delete gameMap;
    delete m_Menu;
    TTF_CloseFont(m_Font);
    TTF_Quit();
    SDL_DestroyRenderer ( m_Renderer );
    SDL_DestroyWindow ( m_Window );
    IMG_Quit();
    SDL_Quit();
}

void Engine::Quit(){
    m_IsRunning = false;
}

void Engine::ResetGame()
{
    pacman->Reset();
    blinky->Reset();
    pinky->Reset();
    inky->Reset();
    clyde->Reset();
    m_Map->Reset();
}

void Engine::CheckGameOver()
{
    if (m_Map->HasWon()) {
        m_CurrentState = STATE_WIN;
    } else if (pacman->GetGameOver()) {
        m_CurrentState = STATE_LOSE;
    }
}
