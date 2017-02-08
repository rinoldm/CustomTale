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
        int fps;
        SDL_Renderer *renderer;
        std::map<unsigned int, std::vector<Sprite>> sprites;
        unsigned int lastSpriteID;

    Graphics(int, int, const std::string &);
    void    error(const std::string &);
    void    init();
    void    getInput();
    unsigned int loadSprite(std::vector<std::string>, int, int, double, bool = true);
    unsigned int loadSprite(std::string, int, int, double, bool = true);
    void    initBackground();

    void    renderSprite(unsigned int);
    void    render();
    void    quit();
};

#endif
