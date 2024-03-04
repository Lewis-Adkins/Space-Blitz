#pragma once

#include "Components.hpp"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <stdio.h>
#include "../TextureManager.hpp"
#include "../Vector2D.hpp"
#include "Animation.hpp"
#include <map>

using namespace std;

class SpriteComponent : public Component {

    private:
        TransformComponent *transform;
        SDL_Texture *texture;
        SDL_Rect srcRect, destRect;

        bool animated = true;
        int frames = 0;
        int speed = 100;

    public:

        int animIndex = 0;

        map<const char*, Animation> animations;

        SpriteComponent() = default;
        SpriteComponent(const char* path) {

            setTex(path);

        }

/*         SpriteComponent(const char* path, bool isAnimated) {

            animated = isAnimated;

            Animation idle = Animation(0,1,100);
            Animation thrust = Animation(1,8,100);

            animations.emplace("Idle", idle);
            animations.emplace("Thrust", thrust);

            Play("Idle");

            setTex(path);

        } */
        ~SpriteComponent() {

            SDL_DestroyTexture(texture);

        }

        void setTex(const char* path) {

            texture = TextureManager::LoadTexture(path);

        }

        void init() override {

            transform = &entity-> getComponent<TransformComponent>();

            srcRect.x = srcRect.y = 0;
            srcRect.w = transform->width;
            srcRect.h = transform->height;
            
        }

        void update() override {

            //if (animated) {

            //    srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks()/speed) % frames);

            //}

            srcRect.y = animIndex * transform -> height;

            destRect.x = static_cast<int>(transform-> position.x);
            destRect.y = static_cast<int>(transform-> position.y);
            destRect.w = transform->width * transform->scale;
            destRect.h = transform->height * transform->scale;

        }

        void draw() override {

            TextureManager::Draw(texture, srcRect, destRect);

        }

        //void Play(const char* animName) {

        //    frames = animations[animName].frames;
        //    animIndex = animations[animName].index;
        //   speed = animations[animName].speed;

//        }

};