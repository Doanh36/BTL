#include "MenuManager.h"

MenuManager::MenuManager(SDL_Renderer* renderer, TTF_Font* font)
    : renderer(renderer), font(font), selected(NEW_GAME) {
    white = {255, 255, 255, 255};
    yellow = {255, 255, 0, 255};
}

MenuManager::~MenuManager() {}

void MenuManager::handleEvent(SDL_Event& e, bool& quit, bool& startGame) {
    if (e.type == SDL_QUIT) {
        quit = true;
    } else if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
            case SDLK_UP:
            case SDLK_w:
                selected = (selected == NEW_GAME) ? EXIT : NEW_GAME;
                break;
            case SDLK_DOWN:
            case SDLK_s:
                selected = (selected == NEW_GAME) ? EXIT : NEW_GAME;
                break;
            case SDLK_RETURN:
            case SDLK_KP_ENTER:
                if (selected == NEW_GAME) startGame = true;
                else quit = true;
                break;
        }
    }
}

void MenuManager::render() {
    const char* options[] = {"New Game", "Exit"};

    for (int i = 0; i < 2; ++i) {
        SDL_Color color = (i == selected) ? yellow : white;
        int textW, textH;
        SDL_Texture* textTex = createTextTexture(options[i], color, textW, textH);

        SDL_Rect dstRect = {screenWidth / 2 - textW / 2,screenHeight / 2 + i * 60 - 30,textW,textH};

        SDL_RenderCopy(renderer, textTex, nullptr, &dstRect);
        SDL_DestroyTexture(textTex);
    }
}

void MenuManager::RenderWIN()
{
    int WIN_W, WIN_H;

    SDL_Texture* WIN_Tex = createTextTexture("YOU WIN", yellow, WIN_W, WIN_H);
    SDL_Rect WIN_Rect = {screenWidth / 2 - WIN_W / 2,100,WIN_W,WIN_H};

    SDL_RenderCopy(renderer, WIN_Tex, nullptr, &WIN_Rect);
    SDL_DestroyTexture(WIN_Tex);
}

void MenuManager::RenderLOSE()
{
    int LOSE_W, LOSE_H;

    SDL_Texture* LOSE_Tex = createTextTexture("YOU LOSE", yellow, LOSE_W, LOSE_H);
    SDL_Rect LOSE_Rect = {screenWidth / 2 - LOSE_W / 2,100,LOSE_W,LOSE_H};

    SDL_RenderCopy(renderer, LOSE_Tex, nullptr, &LOSE_Rect);
    SDL_DestroyTexture(LOSE_Tex);
}

void MenuManager::RenderTitle()
{
    int titleW, titleH;
    SDL_Texture* titleTex = createTextTexture("PAC-MAN", yellow, titleW, titleH);
    SDL_Rect titleRect = {screenWidth / 2 - titleW / 2,100,titleW,titleH};
    SDL_RenderCopy(renderer, titleTex, nullptr, &titleRect);
    SDL_DestroyTexture(titleTex);
}

SDL_Texture* MenuManager::createTextTexture(const std::string& text, SDL_Color color, int& w, int& h) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    w = surface->w;
    h = surface->h;
    SDL_FreeSurface(surface);
    return texture;
}
