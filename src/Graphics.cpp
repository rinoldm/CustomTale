#include "Graphics.hh"

extern Game         game;
extern Json::Value  data;

Graphics::Graphics(int winX, int winY, const std::string &winTitle) :
    windowX(winX),
    windowY(winY),
    windowTitle(winTitle),
    fps(30),
    lastSpriteID(-1)
{
    this->init();
}

void Graphics::error(const std::string &msg)
{
    if (!msg.empty())
        std::cerr << "SDL error : " << msg << std::endl;
}

void Graphics::init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        exit(-1);

    this->window = SDL_CreateWindow(this->windowTitle.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->windowX, this->windowY, 0);
    if (this->window == NULL)
        exit(-1);

    this->renderer = SDL_CreateRenderer(this->window, -1, 0);
    if (this->renderer == NULL)
        exit(-1);

    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
}

void Graphics::resetSprite(unsigned int spriteID)
{
    this->sprites[spriteID].currentFrame = 0;
}

Sprite &Graphics::getSprite(unsigned int spriteID)
{
    return (this->sprites[spriteID]);
}

Frame &Graphics::getCurrentFrame(unsigned int spriteID)
{
    return (this->sprites[spriteID].frames[this->sprites[spriteID].currentFrame]);
}

void Graphics::getInput()
{
    while (SDL_PollEvent(&this->event) && !game.states[isQuitting])
    {
        game.states[isQuitting] = (this->event.type == SDL_QUIT);
        this->keydown[this->event.key.keysym.sym] = (this->event.type == SDL_KEYDOWN);
    }
}

unsigned int Graphics::loadSprite(std::vector<std::string> filenames, int posX, int posY, double scaleFactor, bool isVisible, bool isAnimated)
{
    Sprite sprite(filenames, posX, posY, scaleFactor, isVisible, isAnimated);
    this->sprites.insert(std::pair<unsigned int, Sprite>(++this->lastSpriteID, sprite));
    return (this->lastSpriteID);
}

unsigned int Graphics::loadSprite(std::string filename, int posX, int posY, double scaleFactor, bool isVisible, bool isAnimated)
{
    std::vector<std::string> filenames;
    filenames.push_back(filename);
    return (this->loadSprite(filenames, posX, posY, scaleFactor, isVisible, isAnimated));
}

void Graphics::initBackground()
{
    this->loadSprite("spr_undertaletitle_0.png", 0, 0, 2);
    this->loadSprite(game.jsonToStrings(data["Player"]["sprites"]["walkingDown"]), 20, 20, 2, true, true);
}

void Graphics::renderSprite(unsigned int spriteID)
{
    Frame frame = this->sprites[spriteID].frames[this->sprites[spriteID].currentFrame];

    if (frame.isVisible)
    {
        SDL_Rect rect = {frame.posX, frame.posY, frame.sizeX, frame.sizeY};
        SDL_RenderCopy(this->renderer, frame.texture, NULL, &rect);
    }
}

void Graphics::render()
{
    for (unsigned int i = 0; i < this->sprites.size(); ++i)
    {
        if (this->getSprite(i).isAnimated)
        {
            if (++this->getSprite(i).currentFrame == this->getSprite(i).frames.size())
                this->resetSprite(i);
            this->getCurrentFrame(i).isVisible = true;
        }
        this->renderSprite(i);
    }
    SDL_RenderPresent(this->renderer);
}

void Graphics::quit()
{
    this->error(SDL_GetError());

    for (unsigned int i = 0; i < this->sprites.size(); ++i)
    {
        for (unsigned int j = 0; j < this->sprites[i].frames.size(); ++j)
        {
            SDL_FreeSurface(this->sprites[i].frames[j].image);
            SDL_DestroyTexture(this->sprites[i].frames[j].texture);
        }
    }
    IMG_Quit();
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();

    std::cout << "Quitting..." << std::endl;
}
