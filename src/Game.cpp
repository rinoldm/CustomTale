#include "Game.hh"

extern Graphics graphics;

Game::Game() : player(220, 20, "walkingDown")
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

void Game::handleInput()
{
    if (graphics.keydown[SDLK_ESCAPE])
        this->states[isQuitting] = true;

    this->player.states[isWalkingLeft]  = graphics.keydown[SDLK_LEFT];
    this->player.states[isWalkingRight] = graphics.keydown[SDLK_RIGHT];
    this->player.states[isWalkingUp]    = graphics.keydown[SDLK_UP];
    this->player.states[isWalkingDown]  = graphics.keydown[SDLK_DOWN];
    this->player.states[isRunning]      = graphics.keydown[SDLK_SPACE];
}

void Game::update()
{
    this->player.update();
}
