#include "Player.hh"
#include "Graphics.hh"

extern Graphics graphics;
extern Json::Value project;

Player::Player(int posX, int posY) : posX(posX), posY(posY)
{
    this->states.resize(5, 0);
    this->states[canMove]       = true;
    this->states[isGoingLeft]   = false;
    this->states[isGoingRight]  = false;
    this->states[isGoingUp]     = false;
    this->states[isGoingDown]   = false;
}

std::vector<std::string> jsonToStrings(Json::Value json)
{
    std::vector<std::string> strings;
    for (unsigned int i = 0; i < json.size(); ++i)
        strings.push_back(json[i].asString());
    return (strings);
}

void Player::initSprites()
{
    Json::Value sprites = project["Player"]["sprites"];

    this->sprites.resize(4, -1);
    this->sprites[DIR_DOWN]  = graphics.loadSprite(jsonToStrings(sprites["walkingDown"]),  this->posX, this->posY, 2);
    this->sprites[DIR_UP]    = graphics.loadSprite(jsonToStrings(sprites["walkingUp"]),    this->posX, this->posY, 2, false);
    this->sprites[DIR_LEFT]  = graphics.loadSprite(jsonToStrings(sprites["walkingLeft"]),  this->posX, this->posY, 2, false);
    this->sprites[DIR_RIGHT] = graphics.loadSprite(jsonToStrings(sprites["walkingRight"]), this->posX, this->posY, 2, false);

    //graphics.sprites[this->sprites[DIR_DOWN][0]].isVisible = true;
}

void Player::animate(unsigned int spriteID)
{
    if (this->currentSprite == spriteID) // Already walking in that direction
    {
        // Advance one frame and reset if last frame
        if (++this->currentFrame == graphics.sprites[this->sprites[currentSprite]].size())
            this->currentFrame = 0;
    }
    else // Just changed direction
    {
        // Set animation to first frame of correct direction
        this->currentSprite = spriteID;
        this->currentFrame = 0;
    }
}

void Player::move()
{
    if (this->states[canMove])
    {
        if (this->states[isGoingLeft])  std::cout << "L"; else std::cout << " ";
        if (this->states[isGoingRight]) std::cout << "R"; else std::cout << " ";
        if (this->states[isGoingUp])    std::cout << "U"; else std::cout << " ";
        if (this->states[isGoingDown])  std::cout << "D"; else std::cout << " ";
        std::cout << std::endl;

        // Erase last frame of walking animation
        graphics.sprites[this->sprites[this->currentSprite]][this->currentFrame].isVisible = false;

        // Reset walking animation if not moving
        if (this->states[isGoingLeft] == this->states[isGoingRight] &&
            this->states[isGoingUp]   == this->states[isGoingDown])
            this->currentFrame = 0;

        // Left animation if walking left but not up/left or down/left
        if (this->states[isGoingLeft])
        {
            this->posX -= 5;
            if (!this->states[isGoingRight] && (this->states[isGoingUp] == this->states[isGoingDown]))
                this->animate(DIR_LEFT);
        }

        // Right animation if walking right but not up/right or down/right
        if (this->states[isGoingRight])
        {
            this->posX += 5;
            if (!this->states[isGoingLeft] && (this->states[isGoingUp] == this->states[isGoingDown]))
                this->animate(DIR_RIGHT);
        }

        // Up animation if walking up, up/left or up/right
        if (this->states[isGoingUp])
        {
            this->posY -= 5;
            if (!this->states[isGoingDown])
                this->animate(DIR_UP);
        }

        // Down animation if walking down, down/left or down/right
        if (this->states[isGoingDown])
        {
            this->posY += 5;
            if (!this->states[isGoingUp])
                this->animate(DIR_DOWN);
        }

        // Update position of current frame of animation
        graphics.sprites[this->sprites[this->currentSprite]][this->currentFrame].posX = this->posX;
        graphics.sprites[this->sprites[this->currentSprite]][this->currentFrame].posY = this->posY;
        graphics.sprites[this->sprites[this->currentSprite]][this->currentFrame].isVisible = true;
    }
}
