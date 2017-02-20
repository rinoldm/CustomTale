#ifndef __ENTITY_HH__
#define __ENTITY_HH__

#include <vector>
#include <map>

#include "Sprite.hh"

class Entity
{
    public:
        std::string name;
        double posX;
        double posY;

        std::map<std::string, unsigned int> sprites;
        std::string currentSprite;
        double scaling;
        std::vector<int> states;

        Entity(std::string, double, double, std::string, double);
        void loadSprites();
        Sprite &getCurrentSprite();
        void changeSpriteTo(const std::string &);
};

#endif
