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
}

void Entity::animate(std::string spriteID)
{
    if (this->currentSprite == spriteID) // Already walking in that direction
    {
        // Advance one frame and reset if last frame
        if (++graphics.getSprite(this->sprites[this->currentSprite]).currentFrame == graphics.getSprite(this->sprites[this->currentSprite]).frames.size())
            graphics.resetSprite(this->sprites[this->currentSprite]);
    }
    else // Just changed direction
    {
        // Set animation to first frame of correct direction
        this->currentSprite = spriteID;
        graphics.resetSprite(this->sprites[this->currentSprite]);
    }
}
