#pragma once

#include "Components.hpp"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <stdio.h>
#include "../TextureManager.hpp"
#include "../Vector2D.hpp"

class SpriteComponent : public Component {

    private:
        TransformComponent *transform;
        SDL_Texture *texture;
        SDL_Rect srcRect, destRect;

    public:
        SpriteComponent() = default;
        SpriteComponent(const char* path) {

            texture = TextureManager::LoadTexture(path);

        }

        void init() override {

            transform = &entity-> getComponent<TransformComponent>();

            srcRect.x = srcRect.y = 0;
            srcRect.w =  srcRect.h = 128;
            destRect.w = destRect.h = 128;
        }

        void update() override {

            destRect.x = (int)transform-> position.x;
            destRect.y = (int)transform-> position.y;

        }

        void draw() override {

            TextureManager::Draw(texture, srcRect, destRect);

        }

};