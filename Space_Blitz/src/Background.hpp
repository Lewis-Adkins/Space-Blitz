#pragma once
#include "Game.hpp"

class Background {

    public:

        Background();
        ~Background();

        void LoadBG(int arr[2][3]);
        void DrawBG();

    private:

        SDL_Rect src, dest;

        SDL_Texture* bgtile_texture;
        SDL_Texture* galaxy_texture;

        int bg[2][3];
        
};
