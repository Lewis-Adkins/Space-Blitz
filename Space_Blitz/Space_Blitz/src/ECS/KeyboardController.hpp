#pragma once

#include "../Game.hpp"
#include "ECS.hpp"
#include "Components.hpp"

class KeyboardController : public Component {
public:
    TransformComponent *transform;
    SpriteComponent *sprite;
    
    

    void init() override {
        transform = &entity->getComponent<TransformComponent>();
        sprite = &entity->getComponent<SpriteComponent>();
    }

    void update() override {
        transform->velocity.x = 0;
        transform->velocity.y = 0;

        const Uint8* keystates = SDL_GetKeyboardState(NULL);

/*         if (transform->velocity.x == 0 && transform -> velocity.y == 0) {

            sprite->Play("Idle");

        } */

        if (keystates[SDL_SCANCODE_UP]) {
            transform->velocity.y = -1;
            /* sprite->Play("Thrust"); */
        }

        if (keystates[SDL_SCANCODE_LEFT]) {
            transform->velocity.x = -1;
            /* sprite->Play("Thrust"); */
            
        }

        if (keystates[SDL_SCANCODE_DOWN]) {
            transform->velocity.y = 1;
            /* sprite->Play("Thrust"); */
            
        }

        if (keystates[SDL_SCANCODE_RIGHT]) {
            transform->velocity.x = 1;
            /* sprite->Play("Thrust"); */
            
        if (keystates[SDL_SCANCODE_SPACE]) {

            
              
        }
            
        }
    }
};  