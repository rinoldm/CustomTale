#include "Sprite.hh"
#include "Graphics.hh"

extern Graphics graphics;

Sprite::Sprite(std::vector<std::string> filenames, int posX, int posY, double scaleFactor, bool isVisible, bool isAnimated)
{
    this->currentFrame = 0;
    this->isAnimated = isAnimated;

    for (unsigned int i = 0; i < filenames.size(); ++i)
        this->frames.push_back(this->loadFrame(filenames[i], posX, posY, scaleFactor));
    this->frames[0].isVisible = isVisible;
}

Frame Sprite::loadFrame(std::string filename, int posX, int posY, double scaleFactor)
{
    Frame frame;

    frame.image = IMG_Load(("sprites/" + filename).c_str());
    if (frame.image == NULL)
        exit(-1);

    frame.texture = SDL_CreateTextureFromSurface(graphics.renderer, frame.image);
    if (frame.texture == NULL)
        exit(-1);

    frame.name = filename;
    frame.sizeX = scaleFactor * frame.image->w;
    frame.sizeY = scaleFactor * frame.image->h;
    frame.posX = posX;
    frame.posY = posY;
    frame.isVisible = false;

    return (frame);
}
