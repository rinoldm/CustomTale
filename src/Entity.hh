#ifndef __ENTITY_HH__
#define __ENTITY_HH__

#include <vector>
#include <map>

#include "Sprite.hh"

class Entity
{
    public:
        std::string name;
        int posX;
        int posY;

        std::map<std::string, unsigned int> sprites;
        std::string currentSprite;
        double scaleFactor;
        std::vector<int> states;

        Entity(std::string, int, int, std::string, double);
        void loadSprites();
        Sprite &getCurrentSprite();
        void changeSpriteTo(const std::string &);
};

#endif
