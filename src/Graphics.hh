#ifndef __GRAPHICS_HH__
#define __GRAPHICS_HH__

#include <string>
#include <vector>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Graphics
{
    public:
    typedef struct
    {
        SDL_Surface *image;
        SDL_Texture *texture;
        std::string name;
        int posX;
        int posY;
        int sizeX;
        int sizeY;
        bool isVisible;
    } Sprite;

    public:
        SDL_Window *window;
        int windowX;
        int windowY;
        std::string windowTitle;
        SDL_Event event;
        int fps;
        SDL_Renderer *renderer;
        std::map<unsigned int, Sprite> sprites;
        unsigned int lastSpriteID;

    Graphics(int, int, const std::string &);
    void    error(const std::string &);
    void    init();
    void    getInput();
    unsigned int loadSprite(const std::string &, int, int, double, bool);
    unsigned int loadSprite(const std::string &, int, int, double);
    void    renderSprite(unsigned int);
    void    render();
    void    quit();
};

#endif
