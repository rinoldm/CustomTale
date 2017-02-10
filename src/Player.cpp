#include "Player.hh"
#include "Graphics.hh"

extern Game         game;
extern Json::Value  data;
extern Graphics     graphics;

Player::Player(int posX, int posY) : posX(posX), posY(posY), speed(5)
{
    this->states.resize(1, 0);
    this->states[canMove] = true;
}

void Player::initSprites()
{
    Json::Value sprites = data["Player"]["sprites"];

    this->sprites.resize(4, -1);
    this->sprites[DIR_DOWN]  = graphics.loadSprite(game.jsonToStrings(sprites["charaWalkingDown"]),  this->posX, this->posY, 2);
    this->sprites[DIR_UP]    = graphics.loadSprite(game.jsonToStrings(sprites["charaWalkingUp"]),    this->posX, this->posY, 2, false);
    this->sprites[DIR_LEFT]  = graphics.loadSprite(game.jsonToStrings(sprites["charaWalkingLeft"]),  this->posX, this->posY, 2, false);
    this->sprites[DIR_RIGHT] = graphics.loadSprite(game.jsonToStrings(sprites["charaWalkingRight"]), this->posX, this->posY, 2, false);
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
        if (this->states[isPressingLeft])  std::cout << "L"; else std::cout << " ";
        if (this->states[isPressingRight]) std::cout << "R"; else std::cout << " ";
        if (this->states[isPressingUp])    std::cout << "U"; else std::cout << " ";
        if (this->states[isPressingDown])  std::cout << "D"; else std::cout << " ";
        if (this->states[isPressingSpace]) std::cout << "S"; else std::cout << " ";
        std::cout << std::endl;
        */

        // Erase last frame of walking animation
        graphics.getCurrentFrame(this->sprites[this->currentSprite]).isVisible = false;

        // Gotta go fast
        if (game.states[isPressingSpace])
            this->speed = 10;
        else
            this->speed = 5;

        // Reset walking animation if not moving
        if (game.states[isPressingLeft] == game.states[isPressingRight] &&
            game.states[isPressingUp]   == game.states[isPressingDown])
            graphics.resetSprite(this->sprites[this->currentSprite]);

        // Left animation if walking left but not up/left or down/left
        if (game.states[isPressingLeft])
        {
            this->posX -= this->speed;
            if (!game.states[isPressingRight] && (game.states[isPressingUp] == game.states[isPressingDown]))
                this->animate(DIR_LEFT);
        }

        // Right animation if walking right but not up/right or down/right
        if (game.states[isPressingRight])
        {
            this->posX += this->speed;
            if (!game.states[isPressingLeft] && (game.states[isPressingUp] == game.states[isPressingDown]))
                this->animate(DIR_RIGHT);
        }

        // Up animation if walking up, up/left or up/right
        if (game.states[isPressingUp])
        {
            this->posY -= this->speed;
            if (!game.states[isPressingDown])
                this->animate(DIR_UP);
        }

        // Down animation if walking down, down/left or down/right
        if (game.states[isPressingDown])
        {
            this->posY += this->speed;
            if (!game.states[isPressingUp])
                this->animate(DIR_DOWN);
        }

        // Update position of current frame of animation
        graphics.getCurrentFrame(this->sprites[this->currentSprite]).posX = this->posX;
        graphics.getCurrentFrame(this->sprites[this->currentSprite]).posY = this->posY;
        graphics.getCurrentFrame(this->sprites[this->currentSprite]).isVisible = true;
    }
}
