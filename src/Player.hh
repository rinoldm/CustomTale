#ifndef __PLAYER_HH__
#define __PLAYER_HH__

#include <iostream>
#include <fstream>

//#include "Graphics.hh"
#include "../lib/jsoncpp/json/json.h"

enum
{
    canMove
};

enum
{
    DIR_DOWN,
    DIR_UP,
    DIR_LEFT,
    DIR_RIGHT
};

class Player
{
    public:
        int posX;
        int posY;
        int speed;
        std::vector<unsigned int> sprites;
        unsigned int currentSprite;
        std::vector<int> states;

        Player(int, int);
        void initSprites();
        void animate(unsigned int);
        void move();
};

#endif
