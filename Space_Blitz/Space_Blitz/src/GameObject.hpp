#pragma once
#include "Game.hpp"
class GameObject {

    public:
        GameObject(const char* texturesheet, int x, int y);
        ~GameObject();

        void Update();
        void Render();

    private:

        int x_position;
        int y_position;

        SDL_Texture* objTexture;
        SDL_Rect srcRect, destRect;
        

};