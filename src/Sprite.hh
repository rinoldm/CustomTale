#ifndef __SPRITE_HH__
#define __SPRITE_HH__

#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

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
} Frame;

class Sprite
{
    public:
        std::vector<Frame> frames;
        unsigned int currentFrame;
        bool isAnimated;

        Sprite(){};
        Sprite(std::vector<std::string>, int, int, double, bool, bool);
};

#endif
