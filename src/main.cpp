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

    graphics.initBackground();
    //graphics.initMap();
    game.player.initSprites();

    for (auto i = graphics.sprites.begin(); i != graphics.sprites.end(); ++i)
    {
        std::cout << "  " << i->first << std::endl;
        for (unsigned int j = 0; j < i->second.frames.size(); ++j)
        {
            std::cout << "    " << j << " " <<i->second.frames[j].name << std::endl;
        }
    }
    while (!game.states[isQuitting])
    {
        graphics.getInput();
        game.move();
        graphics.render();
        SDL_Delay(1000 / graphics.fps);
    }

    return (0);
}
