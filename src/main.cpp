#include <iostream>

#include "Game.hh"
#include "Graphics.hh"

Game        game;
Json::Value data;
Graphics    graphics(640, 480, "CustomTale");

void debugDisplaySprites()
{
    for (auto i = graphics.sprites.begin(); i != graphics.sprites.end(); ++i)
    {
        std::cout << "  " << i->first;
        if (i->second.isAnimated)
            std::cout << " (animated)";
        std::cout << std::endl;
        for (unsigned int j = 0; j < i->second.frames.size(); ++j)
            std::cout << "    " << j << " " <<i->second.frames[j].name << std::endl;
    }
}

int main(int ac, char **av)
{
    atexit([]{graphics.quit();});

    std::ifstream dataFile("project.json", std::ifstream::binary);
    dataFile >> data;

    graphics.initBackground();
    //graphics.initMap();
    game.player.initSprites();
    //debugDisplaySprites();

    while (!game.states[isQuitting])
    {
        graphics.getInput();
        game.move();
        graphics.render();
        SDL_Delay(1000 / graphics.fps);
    }

    return (0);
}
