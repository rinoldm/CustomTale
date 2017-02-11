#ifndef __GAME_HH__
#define __GAME_HH__

#include <vector>

#include "Graphics.hh"
#include "Player.hh"

enum
{
    isQuitting,
    isPressingLeft,
    isPressingRight,
    isPressingUp,
    isPressingDown,
    isPressingSpace
};

class Game
{
    public:
        std::vector<int> states;
        Player player;

    Game();

    std::vector<std::string> jsonToStrings(Json::Value json);
    void update();
};

#endif
