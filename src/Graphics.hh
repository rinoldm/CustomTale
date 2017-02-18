#ifndef __GRAPHICS_HH__
#define __GRAPHICS_HH__

#include <iostream>
#include <vector>
#include <map>


#include "Sprite.hh"
#include "Game.hh"
#include "Player.hh"
#include "../lib/jsoncpp/json/json.h"

class Graphics
{
    public:
        SDL_Window *window;
        int windowX;
        int windowY;
        std::string windowTitle;
        SDL_Event event;
        std::map<SDL_Keycode, bool> keydown;
        int fps;
        SDL_Renderer *renderer;
        std::map<unsigned int, Sprite> sprites;
        unsigned int lastSpriteID;

    Graphics(int, int, const std::string &);
    void    error(const std::string &);
    void    initWindow();
    void    getInput();
    unsigned int loadSprite(std::vector<std::string>, int, int, double, bool);
    unsigned int loadSprite(            std::string , int, int, double, bool);
    void    initBackground();

    void    renderSprite(Sprite);
    void    render();
    void    quit();
};

#endif
