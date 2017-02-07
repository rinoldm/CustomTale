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

unsigned int Graphics::loadSprite(const std::string &filename, int posX, int posY, double scaleFactor, bool isVisible)
{
    Sprite sprite;

    sprite.image = IMG_Load(("sprites/" + filename).c_str());
    if (sprite.image == NULL)
        exit(-1);

    sprite.texture = SDL_CreateTextureFromSurface(this->renderer, sprite.image);
    if (sprite.texture == NULL)
        exit(-1);

    sprite.name = filename;
    sprite.sizeX = scaleFactor * sprite.image->w;
    sprite.sizeY = scaleFactor * sprite.image->h;
    sprite.posX = posX;
    sprite.posY = posY;
    sprite.isVisible = isVisible;

    this->sprites.insert(std::pair<unsigned int, Sprite>(++this->lastSpriteID, sprite));
    return (this->lastSpriteID);
}

unsigned int Graphics::loadSprite(const std::string &filename, int posX, int posY, double scaleFactor)
{
    return (this->loadSprite(filename, posX, posY, scaleFactor, true));
}

std::vector<unsigned int> Graphics::loadAnimation(Json::Value json, int posX, int posY, double scaleFactor)
{
    std::vector<unsigned int> frames;

    for (unsigned int i = 0; i < json.size(); ++i)
        frames.push_back(this->loadSprite(json[i].asString(), posX, posY, scaleFactor, false));
    return (frames);
}

void Graphics::renderSprite(unsigned int spriteID)
{
    Sprite sprite = this->sprites[spriteID];
    if (sprite.isVisible)
    {
        SDL_Rect rect = {sprite.posX, sprite.posY, sprite.sizeX, sprite.sizeY};
        SDL_RenderCopy(this->renderer, sprite.texture, NULL, &rect);
    }
}

void Graphics::render()
{
    for (unsigned int i = 0; i < this->sprites.size(); ++i)
        this->renderSprite(i);

    this->renderSprite(game.player.sprites[game.player.currentSprite][game.player.currentFrame]);
    SDL_RenderPresent(this->renderer);
}

void Graphics::quit()
{
    this->error(SDL_GetError());

    for (unsigned int i = 0; i < this->sprites.size(); ++i)
    {
        SDL_FreeSurface(this->sprites[i].image);
        SDL_DestroyTexture(this->sprites[i].texture);
    }
    IMG_Quit();
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();

    std::cout << "Quitting..." << std::endl;
}
