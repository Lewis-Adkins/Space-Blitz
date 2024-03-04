#include "Game.hpp"


Game *game = nullptr;

using namespace std;

int main(int argc, const char * argv[]) {

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    game = new Game();
    
    game->init("Space Blitz", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 800, false);

    while (game->running()) {

        frameStart = SDL_GetTicks();
 
        game -> handleEvents();
        game -> update();
        game -> render();

        frameTime = SDL_GetTicks() - frameStart;

        if(frameDelay > frameTime) {

            SDL_Delay(frameDelay - frameTime);
        }

    }

    game->clean();

    return 0;
}