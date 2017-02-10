#include "Game.hh"

extern Graphics graphics;

Game::Game() : player(220, 20)
{
    this->states.resize(6, 0);
    this->states[isQuitting]        = false;
    this->states[isPressingLeft]    = false;
    this->states[isPressingRight]   = false;
    this->states[isPressingUp]      = false;
    this->states[isPressingDown]    = false;
    this->states[isPressingSpace]   = false;
}

std::vector<std::string> Game::jsonToStrings(Json::Value json)
{
    std::vector<std::string> strings;
    for (unsigned int i = 0; i < json.size(); ++i)
        strings.push_back(json[i].asString());
    return (strings);
}

void Game::move()
{
    this->player.move();
}
