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
auto& boss(manager.addEntity());

auto& border1(manager.addEntity());
auto& border2(manager.addEntity());
auto& border3(manager.addEntity());
auto& border4(manager.addEntity());

auto& laser(manager.addEntity());

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
    player.addComponent<HealthComponent>(10);

    laser.addComponent<TransformComponent>(100.0f,310.0f, 1, 1, .5);
    laser.addComponent<SpriteComponent>("/home/lewis/cpp/projects/games/Space_Blitz/assets/sprites/spaceship/weapons/spaceship_laser.png");
    laser.addComponent<ColliderComponent>("laser");
    laser.addComponent<ProjectileComponent>(10, 10, Vector2D{10,0});

    boss.addComponent<TransformComponent>(610.0f, 200.0f, 500,600, 1);
    boss.addComponent<SpriteComponent>("/home/lewis/cpp/projects/games/Space_Blitz/assets/sprites/boss/boss.png");
    boss.addComponent<ColliderComponent>("boss");
    boss.addComponent<HealthComponent>(100);

     Uint32 laserSpawnTimer;
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

void BossMovement(const Vector2D& bossPos) {
    auto& transform = boss.getComponent<TransformComponent>();
    Uint64 index = SDL_GetPerformanceCounter();

    transform.position = bossPos;
    transform.position.y = 175 * sin(10e-10 * index) + 130;
    //cout << index << endl;
}

void handleborderCollision(const ColliderComponent& playerCollider, const ColliderComponent& borderCollider, const Vector2D& playerPos) {
    if (Collision::AABB(playerCollider.collider, borderCollider.collider)) {
        auto& transform   = player.getComponent<TransformComponent>();
        double delta_time = 0;

        Uint64 LAST = SDL_GetPerformanceCounter();
        Uint64 NOW  = SDL_GetPerformanceCounter();

        delta_time  = (double)((NOW - LAST) * 1000 / (double)(SDL_GetPerformanceFrequency()));

        transform.position = playerPos;
        transform.position.x -= transform.velocity.x * delta_time;
        transform.position.y -= transform.velocity.y * delta_time;
        //cout << "Border hit!" << endl;
    }
}

void PlayerDamage(const ColliderComponent& playerCollider, const ColliderComponent& enemyCollider){
    if (Collision::AABB(playerCollider.collider, enemyCollider.collider)) {
        auto& transform = player.getComponent<HealthComponent>();
        transform.health --;
        cout << transform.health << endl;
    }
}

void laserTrajectory(const Vector2D laserPos, const double speed ) {

    auto& transform = laser.getComponent<TransformComponent>();
    transform.position = laserPos;
    transform.position.x += speed;

}

void Game::update(){
    int laserSpawnTimer = 0;
    Vector2D playerPos = player.getComponent<TransformComponent>().position;
    manager.refresh();
    manager.update();

    handleborderCollision(player.getComponent<ColliderComponent>(), border1.getComponent<ColliderComponent>(), playerPos);
    handleborderCollision(player.getComponent<ColliderComponent>(), border2.getComponent<ColliderComponent>(), playerPos);
    handleborderCollision(player.getComponent<ColliderComponent>(), border3.getComponent<ColliderComponent>(), playerPos);
    handleborderCollision(player.getComponent<ColliderComponent>(), border4.getComponent<ColliderComponent>(), playerPos);

    BossMovement(boss.getComponent<TransformComponent>().position);

    PlayerDamage(player.getComponent<ColliderComponent>(), boss.getComponent<ColliderComponent>());

    if (SDL_GetTicks() - laserSpawnTimer >= 5000) {
        // Spawn a laser at the player's position
        auto& newLaser(manager.addEntity());
        newLaser.addComponent<TransformComponent>(playerPos.x + 40, playerPos.y + 35, 50, 50, 1);
        newLaser.addComponent<SpriteComponent>("/home/lewis/cpp/projects/games/Space_Blitz/assets/sprites/spaceship/weapons/spaceship_laser.png");
        newLaser.addComponent<ColliderComponent>("player");
        newLaser.addComponent<ProjectileComponent>(10, 10, Vector2D{5, 0});

        //laserTrajectory(newLaser.getComponent<TransformComponent>().position, 5);
        // Reset the timer
        laserSpawnTimer = SDL_GetTicks();
    }

   // auto& projectile = player.getComponent<ProjectileComponent>();
   // cout << projectile.Firing<< endl;
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