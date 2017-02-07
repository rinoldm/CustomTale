#include <iostream>

#include "Game.hh"
#include "Graphics.hh"

Game game;
Json::Value project;
Graphics graphics(640, 480, "CustomTale");

int main(int ac, char **av)
{
    atexit([]{graphics.quit();});

    std::ifstream projectFile("project.json", std::ifstream::binary);
    projectFile >> project;

    graphics.loadSprite("spr_undertaletitle_0.png", 0, 0, 2);
    game.player.initSprites();

    while (!game.states[isQuitting])
    {
        graphics.getInput();
        game.move();
        graphics.render();
        SDL_Delay(1000 / graphics.fps);
    }

    return (0);
}
