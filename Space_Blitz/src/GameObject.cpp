#include "GameObject.hpp"
#include "TextureManager.hpp"
GameObject :: GameObject(const char* texturesheet, int x, int y) {

    
    objTexture = TextureManager :: LoadTexture(texturesheet);

    x_position = x;
    y_position = y;

}

void GameObject:: Update() {

    x_position++;
    y_position++;
    srcRect.h = 128;
    srcRect.w = 128;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = x_position;
    destRect.y = y_position;
    destRect.w = srcRect.w ;
    destRect.h = srcRect.h ;
}

void GameObject:: Render() {

    SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);

}