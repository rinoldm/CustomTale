#include "Game.hh"
#include "Graphics.hh"

extern Graphics graphics;

Game::Game() : player(0, 0)
{
    this->states.resize(1, 0);
    this->states[isQuitting] = false;
}

void Game::move()
{
    this->player.move();
}
