#pragma once
#include "Components.hpp"
#include "SDL2/SDL.h"

using namespace std;

struct HealthComponent : public Component {

    
    TransformComponent* transform;

    int health;
    HealthComponent(int h) {
        health = h;
    }

    void init() override {
        if(!entity->hasComponent<TransformComponent>()) {
            entity->addComponent<TransformComponent>();
        }
        transform = &entity -> getComponent<TransformComponent>();
    }
};

