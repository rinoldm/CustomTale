#ifndef __GAME_HH__
#define __GAME_HH__

#include <vector>

#include "Graphics.hh"
#include "Player.hh"
#include "Map.hh"

enum
{
    isQuitting
};

class Game
{
public:
    std::string     projectName;
    std::string     projectPath;
    std::vector<int> states;
    Player          player;
    Map             map;

    Game(std::string name);

    void            loadJsonFile(std::string, Json::Value &);
    std::vector<std::string> jsonToStrings(Json::Value json);
    void            loadMap(std::string);
    void            handleInput();
    void            update();
};

#endif
