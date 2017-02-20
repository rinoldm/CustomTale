#include <iostream>

#include "Game.hh"
#include "Graphics.hh"

Game        game("CustomTale");
Json::Value data;
Graphics    graphics(640, 480, game.name);

void debugDisplaySprites()
{
    for (auto i = graphics.sprites.begin(); i != graphics.sprites.end(); ++i)
    {
        std::cout << "  " << i->first << std::endl;
        for (unsigned int j = 0; j < i->second.frames.size(); ++j)
            std::cout << "    " << j << " " <<i->second.frames[j].name << std::endl;
    }
}

int main(int ac, char **av)
{
    atexit([]{graphics.quit();});

    std::ifstream dataFile("data/" + game.name + "/project.json", std::ifstream::binary);
    dataFile >> data;

    graphics.initBackground();
    //graphics.initMap();
    game.player.loadSprites();
    //debugDisplaySprites();

    while (!game.states[isQuitting])
    {
        graphics.getInput();
        game.handleInput();
        game.update();
        graphics.render();
        SDL_Delay(1000 / graphics.fps);
    }

    return (0);
}
