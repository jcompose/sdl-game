#include <math.h>
#include <SDL.h>
#include <SDL2/SDL_image.h>
#include "SDL_rect.h"
#include "SDL_render.h"
#include "draw.h"
#include "defs.h"

void clear_screen(Game * game) {
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
    SDL_RenderClear(game->renderer);
}

void draw_map(Game * game, SDL_Rect * camera, SDL_Texture * map) {
    SDL_RenderCopy(game->renderer, map, camera, NULL);
}

void draw_hexagons(Game * game, SDL_Rect * camera) {
    const int size = 8;
    const float root_3 = (float)(sqrt(3));

    // Each possible x and y value for the hexagon
    const int x[] = { 0, (int)(size/2), (int)(3*size/2), (int)(2*size) };
    const int y[] = { 0, (int)(size*root_3/2), (int)(size*root_3) };

    // These points specify a perfect hexagon
    const SDL_Point points[] = {
        {x[0], y[1]},
        {x[1], y[0]},
        {x[2], y[0]},
        {x[3], y[1]},
        {x[2], y[2]},
        {x[1], y[2]},
        {x[0], y[1]}
    };

    SDL_Texture * hexagon = SDL_CreateTexture(game->renderer , SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_SetTextureBlendMode(hexagon, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(hexagon, 128);

    SDL_Texture * hexagon_grid = SDL_CreateTexture(game->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_SetTextureBlendMode(hexagon_grid, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(hexagon_grid, 128);

    SDL_SetRenderTarget(game->renderer, hexagon);

    SDL_SetRenderDrawColor(game->renderer, 87, 57, 28, 128);
    SDL_RenderDrawLines(game->renderer, points, 7);

    SDL_SetRenderTarget(game->renderer, hexagon_grid);

    SDL_Rect src = {0, 0, x[3], y[2]};

    for (int x_index = 0; x_index < (SCREEN_WIDTH/size) + 1; x_index++) {
        for (int y_index = 0; y_index < (SCREEN_HEIGHT/size) + 1; y_index++) {
            SDL_Rect dest = {x_index*x[2], y_index*y[2] - y[1]*(x_index%2 == 0), x[3], y[2]};
            SDL_RenderCopy(game->renderer, hexagon, &src, &dest);
        }
    }

    SDL_SetRenderTarget(game->renderer, (SDL_Texture *) NULL);
    SDL_RenderCopy(game->renderer, hexagon_grid, camera, NULL);
}

void present_scene(Game * game) {
    SDL_RenderPresent(game->renderer);
}
