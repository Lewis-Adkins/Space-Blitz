#include "Game.hpp"
#include "TextureManager.hpp"
#include "Background.hpp"
#include <string>
#include "ECS/Components.hpp"
#include "Vector2D.hpp"
#include "Collision.hpp"
//----------------------------------------------------------------------------------------------------------------------------------

Background* bg;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game :: event;

Manager manager;

auto& planet(manager.addEntity());
auto& galaxy(manager.addEntity());

auto& player(manager.addEntity());

auto& border1(manager.addEntity());
auto& border2(manager.addEntity());
auto& border3(manager.addEntity());
auto& border4(manager.addEntity());

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

    planet.addComponent<TransformComponent>(225.0f,125.0f, 100, 100, 1.5);
    planet.addComponent<SpriteComponent>("/home/lewis/cpp/projects/games/Space_Blitz/assets/sprites/background/planet.png");
    
    planet.addComponent<TransformComponent>(600.0f,400.0f, 100, 100, 1.5);
    planet.addComponent<SpriteComponent>("/home/lewis/cpp/projects/games/Space_Blitz/assets/sprites/background/galaxy.png");

    border1.addComponent<TransformComponent>(0.0f,0.0f, 5, 1200, 1);
    
    border1.addComponent<ColliderComponent>("border1");

    border2.addComponent<TransformComponent>(0.0f,0.0f, 800, 5, 1);
    border2.addComponent<ColliderComponent>("border1");

    border3.addComponent<TransformComponent>(0.0f,800.0f, 5, 1200, 1);
    border3.addComponent<ColliderComponent>("border1");

    border4.addComponent<TransformComponent>(1200.0f, 0.0f, 800, 5, 1);
    border4.addComponent<ColliderComponent>("border1");

    player.addComponent<TransformComponent>(100.0f,300.0f, 100, 100, 1);
    player.addComponent<SpriteComponent>("/home/lewis/cpp/projects/games/Space_Blitz/assets/sprites/spaceship/states/spaceship_idle.png");
    player.addComponent<KeyboardController>();
    player.addComponent<ColliderComponent>("player");
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
    Vector2D playerPos = player.getComponent<TransformComponent>().position;
    manager.refresh();
    manager.update();

    if (Collision::AABB(player.getComponent<ColliderComponent>().collider,
        border1.getComponent<ColliderComponent>().collider)){
        player.getComponent<TransformComponent>().position = playerPos;
        player.getComponent<TransformComponent>().velocity * -1;
        cout << "Crashed \n";
    }

    if (Collision::AABB(player.getComponent<ColliderComponent>().collider,
        border2.getComponent<ColliderComponent>().collider)){
        player.getComponent<TransformComponent>().position = playerPos;
        player.getComponent<TransformComponent>().velocity * -1;
        cout << "Crashed \n";
    }

    if (Collision::AABB(player.getComponent<ColliderComponent>().collider,
        border3.getComponent<ColliderComponent>().collider)){
        player.getComponent<TransformComponent>().position = playerPos;
        player.getComponent<TransformComponent>().velocity * -1;
        cout << "Crashed \n";
    }

    if (Collision::AABB(player.getComponent<ColliderComponent>().collider,
        border4.getComponent<ColliderComponent>().collider)){
        player.getComponent<TransformComponent>().position = playerPos;
        player.getComponent<TransformComponent>().velocity * -1;
        cout << "Crashed \n";
    }

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