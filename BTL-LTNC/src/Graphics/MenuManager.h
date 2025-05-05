#ifndef MENU_MANAGER_H
#define MENU_MANAGER_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <iostream>

enum MenuOption {
    NEW_GAME,
    EXIT
};

class MenuManager {
public:
    MenuManager(SDL_Renderer* renderer, TTF_Font* font);
    ~MenuManager();

    void handleEvent(SDL_Event& e, bool& quit, bool& startGame);

    void render();
    void RenderWIN();
    void RenderLOSE();
    void RenderTitle();

private:
    int screenWidth = 900, screenHeight = 700;
    SDL_Renderer* renderer;
    TTF_Font* font;
    MenuOption selected;

    SDL_Color white;
    SDL_Color yellow;

    SDL_Texture* createTextTexture(const std::string& text, SDL_Color color, int& w, int& h);
};

#endif
