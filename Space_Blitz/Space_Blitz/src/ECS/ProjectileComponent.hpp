#pragma once
#include "Components.hpp"
#include "SDL2/SDL.h"

using namespace std;

struct ProjectileComponent : public Component {

    public:

        bool Firing;
        ProjectileComponent *projectile;
    
        ProjectileComponent() {

        }

        void init() override {

            Firing = false;
        }

};
