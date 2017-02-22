#include "Sprite.hh"
#include "Graphics.hh"

extern Game     game;
extern Graphics graphics;

Sprite::Sprite(std::vector<std::string> filenames, double posX, double posY, bool isVisible, double scaling)
{
    this->stopped = true;
    for (unsigned int i = 0; i < filenames.size(); ++i)
        this->frames.push_back(this->loadFrame(filenames[i], scaling));
    this->currentFrame = 0;
    this->totalFrames = this->frames.size();
    this->posX = posX;
    this->posY = posY;
    this->isVisible = isVisible;
}

Frame Sprite::loadFrame(std::string filename, double scaling)
{
    Frame frame;

    frame.image = IMG_Load((game.projectPath + "sprites/" + filename).c_str());
    if (frame.image == NULL)
        exit(-1);

    frame.texture = SDL_CreateTextureFromSurface(graphics.renderer, frame.image);
    if (frame.texture == NULL)
        exit(-1);

    frame.name = filename;
    frame.sizeX = scaling * frame.image->w;
    frame.sizeY = scaling * frame.image->h;

    return (frame);
}

Frame &Sprite::getCurrentFrame()
{
    return (this->frames[this->currentFrame]);
}

void Sprite::start()   { this->stopped = false; }
void Sprite::stop()    { this->stopped = true;  }
void Sprite::restart() { this->stopped = false; this->currentFrame = 0; }
void Sprite::reset()   { this->stopped = true;  this->currentFrame = 0; }

void Sprite::update()
{
    if (!this->stopped && ++this->currentFrame >= this->totalFrames)
        this->currentFrame = 0;
}
