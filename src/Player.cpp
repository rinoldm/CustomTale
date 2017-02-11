#include "Player.hh"
#include "Graphics.hh"

extern Game         game;
extern Json::Value  data;
extern Graphics     graphics;

Player::Player(int posX, int posY, std::string initialSprite) : Entity("Player", posX, posY, initialSprite, 2), speed(5)
{
    this->states.resize(1, 0);
    this->states[canMove] = true;
}

void Player::update()
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
                this->animate("charaWalkingLeft");
        }

        // Right animation if walking right but not up/right or down/right
        if (game.states[isPressingRight])
        {
            this->posX += this->speed;
            if (!game.states[isPressingLeft] && (game.states[isPressingUp] == game.states[isPressingDown]))
                this->animate("charaWalkingRight");
        }

        // Up animation if walking up, up/left or up/right
        if (game.states[isPressingUp])
        {
            this->posY -= this->speed;
            if (!game.states[isPressingDown])
                this->animate("charaWalkingUp");
        }

        // Down animation if walking down, down/left or down/right
        if (game.states[isPressingDown])
        {
            this->posY += this->speed;
            if (!game.states[isPressingUp])
                this->animate("charaWalkingDown");
        }

        // Update position of current frame of animation
        graphics.getCurrentFrame(this->sprites[this->currentSprite]).posX = this->posX;
        graphics.getCurrentFrame(this->sprites[this->currentSprite]).posY = this->posY;
        graphics.getCurrentFrame(this->sprites[this->currentSprite]).isVisible = true;
    }
}
