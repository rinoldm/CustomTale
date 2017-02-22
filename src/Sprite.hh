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
    int sizeX;
    int sizeY;
} Frame;

class Sprite
{
public:
    std::vector<Frame> frames;
    unsigned int    currentFrame;
    unsigned int    totalFrames;
    bool            stopped;
    double          posX;
    double          posY;
    bool            isVisible;

    Sprite(){};
    Sprite(std::vector<std::string>, double, double, bool, double);

    Frame           loadFrame(std::string, double);
    Frame &         getCurrentFrame();
    void            start();
    void            stop();
    void            restart();
    void            reset();
    void            update();
};

#endif
