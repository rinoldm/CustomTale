#include "Player.hh"
#include "Graphics.hh"

extern Game         game;
extern Json::Value  data;
extern Graphics     graphics;

Player::Player(int posX, int posY) : posX(posX), posY(posY)
{
    this->states.resize(5, 0);
    this->states[canMove]       = true;
    this->states[isGoingLeft]   = false;
    this->states[isGoingRight]  = false;
    this->states[isGoingUp]     = false;
    this->states[isGoingDown]   = false;
}

void Player::initSprites()
{
    Json::Value sprites = data["Player"]["sprites"];

    this->sprites.resize(4, -1);
    this->sprites[DIR_DOWN]  = graphics.loadSprite(game.jsonToStrings(sprites["walkingDown"]),  this->posX, this->posY, 2);
    this->sprites[DIR_UP]    = graphics.loadSprite(game.jsonToStrings(sprites["walkingUp"]),    this->posX, this->posY, 2, false);
    this->sprites[DIR_LEFT]  = graphics.loadSprite(game.jsonToStrings(sprites["walkingLeft"]),  this->posX, this->posY, 2, false);
    this->sprites[DIR_RIGHT] = graphics.loadSprite(game.jsonToStrings(sprites["walkingRight"]), this->posX, this->posY, 2, false);
}

void Player::animate(unsigned int spriteID)
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

void Player::move()
{
    if (this->states[canMove])
    {
        /*
        if (this->states[isGoingLeft])  std::cout << "L"; else std::cout << " ";
        if (this->states[isGoingRight]) std::cout << "R"; else std::cout << " ";
        if (this->states[isGoingUp])    std::cout << "U"; else std::cout << " ";
        if (this->states[isGoingDown])  std::cout << "D"; else std::cout << " ";
        std::cout << std::endl;
        */

        // Erase last frame of walking animation
        graphics.getCurrentFrame(this->sprites[this->currentSprite]).isVisible = false;

        // Reset walking animation if not moving
        if (this->states[isGoingLeft] == this->states[isGoingRight] &&
            this->states[isGoingUp]   == this->states[isGoingDown])
            graphics.resetSprite(this->sprites[this->currentSprite]);

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

        graphics.getCurrentFrame(this->sprites[this->currentSprite]).posX = this->posX;
        graphics.getCurrentFrame(this->sprites[this->currentSprite]).posY = this->posY;
        graphics.getCurrentFrame(this->sprites[this->currentSprite]).isVisible = true;
    }
}
