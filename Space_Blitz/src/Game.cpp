#include "Game.hpp"
#include "TextureManager.hpp"
#include "Background.hpp"
#include <string>
#include "ECS/Components.hpp"
#include "Vector2D.hpp"
//----------------------------------------------------------------------------------------------------------------------------------

Background* bg;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game :: event;

Manager manager;

auto& player(manager.addEntity());

Game::Game() {

}

Game:: ~Game() {

}

void Game::init(const char *title, int x_position, int y_position, int width, int height, bool fullscreen) {

    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        cout << "Subsystems Initialized! \n";
    
        window = SDL_CreateWindow(title, x_position, y_position, width, height, flags);
        if(window) {
            cout << "Window created! \n";
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 100);
            cout << "Renderer created \n";
        }
        isRunning = true;
    } else {
        isRunning = false;
    }
    
    bg = new Background();

    player.addComponent<TransformComponent>();
    player.addComponent<SpriteComponent>("/home/lewis/cpp/projects/games/Space_Blitz/assets/sprites/spaceship/states/spaceship_idle.png");
    player.addComponent<KeyboardController>();
}

void Game::handleEvents(){

    
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;

        default:
            break;
    }
}

void Game::update(){
    manager.refresh();
    manager.update();
    

}

void Game::render(){
    SDL_RenderClear(renderer);
    bg       -> DrawBG();
    
    manager.draw();
    SDL_RenderPresent(renderer);
}

void Game:: clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    cout << "Game Cleaned \n";

}