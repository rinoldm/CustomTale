#include "Graphics.hh"

extern Game         game;
extern Json::Value  data;

Graphics::Graphics(int winX, int winY, const std::string &winTitle)
{
    this->windowX = winX;
    this->windowY = winY;
    this->windowTitle = winTitle;
    this->fps = 30;
    this->lastSpriteID = -1;

    this->initWindow();
}

void Graphics::error(const std::string &msg)
{
    if (!msg.empty())
        std::cerr << "SDL error : " << msg << std::endl;
}

void Graphics::initWindow()
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

void Graphics::getInput()
{
    while (SDL_PollEvent(&this->event) && !game.states[isQuitting])
    {
        game.states[isQuitting] = (this->event.type == SDL_QUIT);
        this->keydown[this->event.key.keysym.sym] = (this->event.type == SDL_KEYDOWN);
    }
}

unsigned int Graphics::loadSprite(std::vector<std::string> filenames, int posX, int posY, double scaleFactor, bool isVisible = true)
{
    Sprite sprite(filenames, posX, posY, scaleFactor, isVisible);
    this->sprites.insert({++this->lastSpriteID, sprite});
    if (isVisible)
        this->sprites[this->lastSpriteID].start();
    return (this->lastSpriteID);
}

unsigned int Graphics::loadSprite(std::string filename, int posX, int posY, double scaleFactor, bool isVisible = true)
{
    std::vector<std::string> filenames;
    filenames.push_back(filename);
    return (this->loadSprite(filenames, posX, posY, scaleFactor, isVisible));
}

void Graphics::initBackground()
{
    this->loadSprite("spr_undertaletitle_0.png", 0, 0, 2);
    this->loadSprite(game.jsonToStrings(data["Player"]["sprites"]["walkingDown"]), 250, 60, 2);
}

void Graphics::renderSprite(Sprite sprite)
{
    if (sprite.isVisible)
    {
        Frame frame = sprite.getCurrentFrame();
        SDL_Rect rect = {sprite.posX, sprite.posY, frame.sizeX, frame.sizeY};
        SDL_RenderCopy(this->renderer, frame.texture, NULL, &rect);
    }
}

void Graphics::render()
{
    for (unsigned int i = 0; i < this->sprites.size(); ++i)
    {
        this->sprites[i].update();
        this->renderSprite(this->sprites[i]);
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
