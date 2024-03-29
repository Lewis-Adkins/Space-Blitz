#ifndef Game_hpp
#define Game_hpp
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <stdio.h>
#include <iostream>


using namespace std;

class Game {

public:
    Game();
    ~Game();

    void init(const char* title,
     int x_position, int y_position,
    int width, int height, bool fullscreen);

    void handleEvents();
    void update();
    void render();
    void clean();

    static SDL_Renderer *renderer;
    static SDL_Event event;

    bool running(){
        return isRunning;
    };

private:
    int cnt = 0;
    bool isRunning = false;
    SDL_Window *window;
   

};

#endif /* Game_hpp */