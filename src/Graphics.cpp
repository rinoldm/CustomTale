#include "Graphics.hh"

extern Game game;

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
        switch (this->event.type)
        {
        case SDL_QUIT:
            game.states[isQuitting] = true;
            break;

        case SDL_KEYDOWN:
            switch (this->event.key.keysym.sym)
            {
                case SDLK_LEFT:   game.player.states[isGoingLeft]  = true; break;
                case SDLK_RIGHT:  game.player.states[isGoingRight] = true; break;
                case SDLK_UP:     game.player.states[isGoingUp]    = true; break;
                case SDLK_DOWN:   game.player.states[isGoingDown]  = true; break;
                case SDLK_ESCAPE: game.states[isQuitting]          = true; break;
            }
            break;

        case SDL_KEYUP:
            switch (this->event.key.keysym.sym)
            {
                case SDLK_LEFT:   game.player.states[isGoingLeft]  = false; break;
                case SDLK_RIGHT:  game.player.states[isGoingRight] = false; break;
                case SDLK_UP:     game.player.states[isGoingUp]    = false; break;
                case SDLK_DOWN:   game.player.states[isGoingDown]  = false; break;
            }
            break;
        }
    }
}

unsigned int Graphics::loadSprite(std::vector<std::string> filenames, int posX, int posY, double scaleFactor, bool isVisible)
{
    Sprite sprite;

    for (unsigned int i = 0; i < filenames.size(); ++i)
    {
        Frame frame;

        frame.image = IMG_Load(("sprites/" + filenames[i]).c_str());
        if (frame.image == NULL)
            exit(-1);

        frame.texture = SDL_CreateTextureFromSurface(this->renderer, frame.image);
        if (frame.texture == NULL)
            exit(-1);

        frame.name = filenames[i];
        frame.sizeX = scaleFactor * frame.image->w;
        frame.sizeY = scaleFactor * frame.image->h;
        frame.posX = posX;
        frame.posY = posY;
        frame.isVisible = false;

        sprite.frames.push_back(frame);
    }
    sprite.frames[0].isVisible = isVisible;
    sprite.currentFrame = 0;
    this->sprites.insert(std::pair<unsigned int, Sprite>(++this->lastSpriteID, sprite));
    return (this->lastSpriteID);
}

unsigned int Graphics::loadSprite(std::string filename, int posX, int posY, double scaleFactor, bool isVisible)
{
    std::vector<std::string> filenames;
    filenames.push_back(filename);
    return (this->loadSprite(filenames, posX, posY, scaleFactor, isVisible));
}

void Graphics::initBackground()
{
    this->loadSprite("spr_undertaletitle_0.png", 0, 0, 2);
}

void Graphics::renderSprite(unsigned int spriteID)
{
    for (unsigned int frameID = 0; frameID < this->sprites[spriteID].frames.size(); ++frameID)
    {
        Frame frame = this->sprites[spriteID].frames[frameID];
        if (frame.isVisible)
        {
            SDL_Rect rect = {frame.posX, frame.posY, frame.sizeX, frame.sizeY};
            SDL_RenderCopy(this->renderer, frame.texture, NULL, &rect);
        }
    }
}

void Graphics::render()
{
    for (unsigned int i = 0; i < this->sprites.size(); ++i)
        this->renderSprite(i);

    this->renderSprite(game.player.sprites[game.player.currentSprite]);

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
