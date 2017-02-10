#include "Sprite.hh"
#include "Graphics.hh"

extern Graphics graphics;

Sprite::Sprite(std::vector<std::string> filenames, int posX, int posY, double scaleFactor, bool isVisible, bool isAnimated) : currentFrame(0), isAnimated(isAnimated)
{
    for (unsigned int i = 0; i < filenames.size(); ++i)
    {
        Frame frame;

        frame.image = IMG_Load(("sprites/" + filenames[i]).c_str());
        if (frame.image == NULL)
            exit(-1);

        frame.texture = SDL_CreateTextureFromSurface(graphics.renderer, frame.image);
        if (frame.texture == NULL)
            exit(-1);

        frame.name = filenames[i];
        frame.sizeX = scaleFactor * frame.image->w;
        frame.sizeY = scaleFactor * frame.image->h;
        frame.posX = posX;
        frame.posY = posY;
        frame.isVisible = false;

        this->frames.push_back(frame);
    }
    this->frames[0].isVisible = isVisible;
}
