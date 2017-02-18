#include "Entity.hh"
#include "Graphics.hh"


extern Game         game;
extern Json::Value  data;
extern Graphics     graphics;

Entity::Entity(std::string name, int posX, int posY, std::string initialSprite, double scaleFactor)
{
    this->name = name;
    this->posX = posX;
    this->posY = posY;
    this->currentSprite = initialSprite;
    this->scaleFactor = scaleFactor;
}

void Entity::loadSprites()
{
    Json::Value sprites = data[this->name]["sprites"];
    std::vector<std::string> spriteNames = sprites.getMemberNames();

    for (unsigned int i = 0; i < spriteNames.size(); ++i)
        this->sprites[spriteNames[i]] = graphics.loadSprite(game.jsonToStrings(sprites[spriteNames[i]]), this->posX, this->posY, this->scaleFactor, false);
    this->getCurrentSprite().isVisible = true;
}

Sprite &Entity::getCurrentSprite()
{
    return (graphics.sprites[this->sprites[this->currentSprite]]);
}

void Entity::changeSpriteTo(const std::string &sprite)
{
    if (this->currentSprite != sprite)
    {
        this->getCurrentSprite().reset();
        this->getCurrentSprite().isVisible = false;
        this->currentSprite = sprite;
        this->getCurrentSprite().isVisible = true;
    }
    this->getCurrentSprite().start();
}
