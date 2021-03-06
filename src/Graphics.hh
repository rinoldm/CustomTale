#ifndef __GRAPHICS_HH__
#define __GRAPHICS_HH__

#include <iostream>
#include <vector>
#include <map>


#include "Sprite.hh"
#include "Game.hh"
#include "Player.hh"
#include "../lib/jsoncpp/json/json.h"

enum
{
    layer_background,
    layer_backtiles,
    layer_backtiles2,
    layer_backsprites,
    layer_entities,
    layer_fronttiles,
    layer_fronttiles2,
    layer_frontsprites,
    layer_foreground
};

class Graphics
{
public:
    SDL_Window      *window;
    int             windowX;
    int             windowY;
    std::string     windowTitle;
    unsigned int    tileSizeX;
    unsigned int    tileSizeY;
    double          globalScaling;
    SDL_Event       event;
    std::map<SDL_Keycode, bool> keydown;
    int             fps;
    SDL_Renderer    *renderer;
    std::vector<std::map<unsigned int, Sprite>> sprites;
    unsigned int    lastSpriteID;

    Graphics(int, int, const std::string &);

    void            error(const std::string &);
    void            initWindow();
    void            getInput();
    unsigned int    loadSprite(std::vector<std::string>, unsigned int, double, double, bool, double);
    void            initBackground();
    void            render();
    void            quit();
};

#endif
