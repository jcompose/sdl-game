#include "SDL_image.h"
#include "SDL_render.h"
#include "defs.h"

SDL_Texture * load_map(Game * game, char * path) {
    SDL_Texture * original_map = IMG_LoadTexture(game->renderer, path);
    SDL_Texture * resized_map;
    int original_width, original_height;

    if (original_map == (SDL_Texture *) NULL) {
        printf("ERROR: Image not found.");
        exit(1);
    }

    SDL_QueryTexture(original_map, NULL, NULL, &original_width, &original_height);

    resized_map = SDL_CreateTexture(game->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);

    SDL_SetRenderTarget(game->renderer, resized_map);
    SDL_RenderCopy(game->renderer, original_map, NULL, NULL);
    SDL_SetRenderTarget(game->renderer, (SDL_Texture *) NULL);

    return resized_map;
}
