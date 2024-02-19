#include "Background.hpp"
#include "TextureManager.hpp"

int bg1[2][3] = {
    {0,0,0},
    {0,0,0}
};


Background :: Background() {

    bgtile_texture = TextureManager::LoadTexture("/home/lewis/cpp/projects/games/Space_Blitz/assets/sprites/background/background_tile.png");
    LoadBG(bg1);

    src.x = src.y = 0;
    src.w = dest.w = 400;
    src.h = dest.h = 400;

    dest.x = dest.y = 0;

}

void Background::LoadBG(int arr[2][3]){

    for (int row = 0; row < 2; row++){
        for (int col = 0; col < 3; col++){
            bg[row][col] = arr[row][col];
            
        }
    }

}

void Background::DrawBG(){
    
    int type = 0;

    for (int row = 0; row < 2; row++){
        for (int col = 0; col < 3; col++){
            type = bg[row][col];

            dest.x = col * 400;
            dest.y = row * 400;

            switch (type) {

                case 0:
                    TextureManager::Draw(bgtile_texture, src, dest);
                    break;
                // Place other background tiles here for different stages of battle
                default:
                    break;
            }
        }
    }


}