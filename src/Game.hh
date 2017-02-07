#ifndef __GAME_HH__
#define __GAME_HH__

#include <vector>

#include "Graphics.hh"
#include "Player.hh"

enum
{
    isQuitting,
};

class Game
{
    public:
        std::vector<int> states;
        Player player;

    Game();
    void move();
};

#endif
