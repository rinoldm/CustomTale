#include <iostream>

#include "Game.hh"
#include "Graphics.hh"

Game        game("CustomTale");
Json::Value data;
Graphics    graphics(640, 480, game.projectName);

void debugDisplaySprites()
{
    for (unsigned int layer = 0; layer < graphics.sprites.size(); ++layer)
    {
        std::cout << "Layer " << layer << ":" << std::endl;
        for (auto i = graphics.sprites[layer].begin(); i != graphics.sprites[layer].end(); ++i)
        {
            std::cout << "  " << i->first << std::endl;
            for (unsigned int j = 0; j < i->second.frames.size(); ++j)
                std::cout << "    " << j << " " <<i->second.frames[j].name << std::endl;
        }
        std::cout << std::endl;
    }
}

int main(int ac, char **av)
{
    atexit([]{graphics.quit();});

    game.loadJsonFile(game.projectPath + "project.json", data);
    graphics.initBackground();
    game.loadMap("map_ruins1");
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
