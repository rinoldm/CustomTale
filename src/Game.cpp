#include "Game.hh"

extern Graphics graphics;

Game::Game() : player(60, 60)
{
    this->states.resize(1, 0);
    this->states[isQuitting] = false;
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
