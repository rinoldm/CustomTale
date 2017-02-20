#include "Player.hh"
#include "Graphics.hh"

extern Game         game;
extern Json::Value  data;
extern Graphics     graphics;

Player::Player(double posX, double posY, std::string initialSprite) : Entity("Player", posX, posY, initialSprite, 1)
{
    this->speed = 2.5;

    this->states.resize(6, 0);
    this->states[canMove]           = true;
    this->states[isWalkingLeft]     = false;
    this->states[isWalkingRight]    = false;
    this->states[isWalkingUp]       = false;
    this->states[isWalkingDown]     = false;
    this->states[isRunning]         = false;
}

void Player::update()
{
    if (this->states[canMove])
    {
        /*
        if (this->states[isWalkingLeft])  std::cout << "L"; else std::cout << " ";
        if (this->states[isWalkingRight]) std::cout << "R"; else std::cout << " ";
        if (this->states[isWalkingUp])    std::cout << "U"; else std::cout << " ";
        if (this->states[isWalkingDown])  std::cout << "D"; else std::cout << " ";
        if (this->states[isRunning])      std::cout << "S"; else std::cout << " ";
        std::cout << std::endl;
        */

        // Gotta go fast
        this->speed = (this->states[isRunning] ? 5 : 2.5);

        // Reset walking animation if not moving
        if (this->states[isWalkingLeft] == this->states[isWalkingRight] &&
            this->states[isWalkingUp]   == this->states[isWalkingDown])
            this->getCurrentSprite().reset();

        // Left animation if walking left but not up/left or down/left
        if (this->states[isWalkingLeft])
        {
            this->posX -= this->speed;
            if (!this->states[isWalkingRight] && (this->states[isWalkingUp] == this->states[isWalkingDown]))
                this->changeSpriteTo("walkingLeft");
        }

        // Right animation if walking right but not up/right or down/right
        if (this->states[isWalkingRight])
        {
            this->posX += this->speed;
            if (!this->states[isWalkingLeft] && (this->states[isWalkingUp] == this->states[isWalkingDown]))
                this->changeSpriteTo("walkingRight");
        }

        // Up animation if walking up, up/left or up/right
        if (this->states[isWalkingUp])
        {
            this->posY -= this->speed;
            if (!this->states[isWalkingDown])
                this->changeSpriteTo("walkingUp");
        }

        // Down animation if walking down, down/left or down/right
        if (this->states[isWalkingDown])
        {
            this->posY += this->speed;
            if (!this->states[isWalkingUp])
                this->changeSpriteTo("walkingDown");
        }

        // Update position of current frame of animation
        this->getCurrentSprite().posX = this->posX;
        this->getCurrentSprite().posY = this->posY;
    }
}
