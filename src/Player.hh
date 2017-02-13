#ifndef __PLAYER_HH__
#define __PLAYER_HH__

#include <iostream>
#include <fstream>

#include "Entity.hh"
#include "../lib/jsoncpp/json/json.h"

enum
{
    canMove,
    isWalkingLeft,
    isWalkingRight,
    isWalkingUp,
    isWalkingDown,
    isRunning
};

class Player : public Entity
{
    public:
        int speed;

        Player(int, int, std::string);
        void update();
};

#endif
