#include <iostream>
#include "Game.hh"
#include "Graphics.hh"

Game game;
Graphics graphics(640, 480, "CustomTale");

int main(int ac, char **av)
{
    atexit([]{graphics.quit();});

    while (!game.states[isQuitting])
    {
        graphics.getInput();
        game.move();
        graphics.render();
        SDL_Delay(1000 / graphics.fps);
    }

    return (0);
}
