#include "Sprite.hh"
#include "Graphics.hh"

extern Graphics graphics;

Sprite::Sprite(std::vector<std::string> filenames, int posX, int posY, double scaleFactor, bool isVisible)
{
    this->stopped = true;
    for (unsigned int i = 0; i < filenames.size(); ++i)
        this->frames.push_back(this->loadFrame(filenames[i], scaleFactor, 1));
    this->currentFrame = 0;
    this->totalFrames = this->frames.size();
    this->posX = posX;
    this->posY = posY;
    this->isVisible = isVisible;
}

Frame Sprite::loadFrame(std::string filename, double scaleFactor, int duration)
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
    frame.duration = duration;

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
