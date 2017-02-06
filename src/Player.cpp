#include "Player.hh"
#include <iostream>
extern Graphics graphics;

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
    // Shut up, I know :c
    this->sprites.resize(4, std::vector<unsigned int>());
    this->sprites[DIR_DOWN].push_back(graphics.loadSprite("spr_maincharad_0.png", this->posX, this->posY, 2));
    this->sprites[DIR_DOWN].push_back(graphics.loadSprite("spr_maincharad_1.png", this->posX, this->posY, 2, false));
    this->sprites[DIR_DOWN].push_back(graphics.loadSprite("spr_maincharad_1.png", this->posX, this->posY, 2, false));
    this->sprites[DIR_DOWN].push_back(graphics.loadSprite("spr_maincharad_1.png", this->posX, this->posY, 2, false));
    this->sprites[DIR_DOWN].push_back(graphics.loadSprite("spr_maincharad_2.png", this->posX, this->posY, 2, false));
    this->sprites[DIR_DOWN].push_back(graphics.loadSprite("spr_maincharad_2.png", this->posX, this->posY, 2, false));
    this->sprites[DIR_DOWN].push_back(graphics.loadSprite("spr_maincharad_2.png", this->posX, this->posY, 2, false));
    this->sprites[DIR_DOWN].push_back(graphics.loadSprite("spr_maincharad_3.png", this->posX, this->posY, 2, false));
    this->sprites[DIR_DOWN].push_back(graphics.loadSprite("spr_maincharad_3.png", this->posX, this->posY, 2, false));
    this->sprites[DIR_DOWN].push_back(graphics.loadSprite("spr_maincharad_3.png", this->posX, this->posY, 2, false));
    this->sprites[DIR_DOWN].push_back(graphics.loadSprite("spr_maincharad_0.png", this->posX, this->posY, 2, false));
    this->sprites[DIR_DOWN].push_back(graphics.loadSprite("spr_maincharad_0.png", this->posX, this->posY, 2, false));
    this->sprites[DIR_UP].push_back(graphics.loadSprite("spr_maincharau_0.png", this->posX, this->posY, 2, false));
    this->sprites[DIR_UP].push_back(graphics.loadSprite("spr_maincharau_1.png", this->posX, this->posY, 2, false));
    this->sprites[DIR_UP].push_back(graphics.loadSprite("spr_maincharau_1.png", this->posX, this->posY, 2, false));
    this->sprites[DIR_UP].push_back(graphics.loadSprite("spr_maincharau_1.png", this->posX, this->posY, 2, false));
    this->sprites[DIR_UP].push_back(graphics.loadSprite("spr_maincharau_2.png", this->posX, this->posY, 2, false));
    this->sprites[DIR_UP].push_back(graphics.loadSprite("spr_maincharau_2.png", this->posX, this->posY, 2, false));
    this->sprites[DIR_UP].push_back(graphics.loadSprite("spr_maincharau_2.png", this->posX, this->posY, 2, false));
    this->sprites[DIR_UP].push_back(graphics.loadSprite("spr_maincharau_3.png", this->posX, this->posY, 2, false));
    this->sprites[DIR_UP].push_back(graphics.loadSprite("spr_maincharau_3.png", this->posX, this->posY, 2, false));
    this->sprites[DIR_UP].push_back(graphics.loadSprite("spr_maincharau_3.png", this->posX, this->posY, 2, false));
    this->sprites[DIR_UP].push_back(graphics.loadSprite("spr_maincharau_0.png", this->posX, this->posY, 2, false));
    this->sprites[DIR_UP].push_back(graphics.loadSprite("spr_maincharau_0.png", this->posX, this->posY, 2, false));
    this->sprites[DIR_LEFT].push_back(graphics.loadSprite("spr_maincharal_0.png", this->posX, this->posY, 2, false));
    this->sprites[DIR_LEFT].push_back(graphics.loadSprite("spr_maincharal_1.png", this->posX, this->posY, 2, false));
    this->sprites[DIR_LEFT].push_back(graphics.loadSprite("spr_maincharal_1.png", this->posX, this->posY, 2, false));
    this->sprites[DIR_LEFT].push_back(graphics.loadSprite("spr_maincharal_1.png", this->posX, this->posY, 2, false));
    this->sprites[DIR_LEFT].push_back(graphics.loadSprite("spr_maincharal_0.png", this->posX, this->posY, 2, false));
    this->sprites[DIR_LEFT].push_back(graphics.loadSprite("spr_maincharal_0.png", this->posX, this->posY, 2, false));
    this->sprites[DIR_RIGHT].push_back(graphics.loadSprite("spr_maincharar_0.png", this->posX, this->posY, 2, false));
    this->sprites[DIR_RIGHT].push_back(graphics.loadSprite("spr_maincharar_1.png", this->posX, this->posY, 2, false));
    this->sprites[DIR_RIGHT].push_back(graphics.loadSprite("spr_maincharar_1.png", this->posX, this->posY, 2, false));
    this->sprites[DIR_RIGHT].push_back(graphics.loadSprite("spr_maincharar_1.png", this->posX, this->posY, 2, false));
    this->sprites[DIR_RIGHT].push_back(graphics.loadSprite("spr_maincharar_0.png", this->posX, this->posY, 2, false));
    this->sprites[DIR_RIGHT].push_back(graphics.loadSprite("spr_maincharar_0.png", this->posX, this->posY, 2, false));

    for (int i = 0; i < this->sprites.size(); ++i)
    {
        for (int j = 0; j < this->sprites[i].size(); ++j)
        {
            std::cout << this->sprites[i][j] << " " << graphics.sprites[this->sprites[i][j]].name << std::endl;
        }
        std::cout << std::endl;
    }
}

void Player::animate(unsigned int spriteID)
{
    if (this->currentSprite == spriteID) // Already walking in that direction
    {
        // Advance one frame and reset if last frame
        if (++this->currentFrame == this->sprites[currentSprite].size())
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
        if (this->states[isGoingLeft]) std::cout << "L"; else std::cout << " ";
        if (this->states[isGoingRight]) std::cout << "R"; else std::cout << " ";
        if (this->states[isGoingUp]) std::cout << "U"; else std::cout << " ";
        if (this->states[isGoingDown]) std::cout << "D"; else std::cout << " ";
        std::cout << std::endl;

        // Erase last frame of walking animation
        graphics.sprites[this->sprites[this->currentSprite][this->currentFrame]].isVisible = false;

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
        graphics.sprites[this->sprites[this->currentSprite][this->currentFrame]].posX = this->posX;
        graphics.sprites[this->sprites[this->currentSprite][this->currentFrame]].posY = this->posY;
        graphics.sprites[this->sprites[this->currentSprite][this->currentFrame]].isVisible = true;
    }
}
