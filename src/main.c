#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <string.h>
#include "SDL_render.h"
#include "defs.h"
#include "heroes.h"
#include "input.h"
#include "draw.h"
#include "map.h"

void init_SDL(Game * game) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("Failed to initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    game->window = SDL_CreateWindow("Top-Down Overwatch", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

    if (!game->window) {
        printf("Failed to open %d x %d window: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
        exit(1);
    }

    game->renderer = SDL_CreateRenderer(game->window, -1, SDL_RENDERER_ACCELERATED);

    if (!game->renderer) {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        exit(1);
    }
}

int main(void) {
    Game game;
    SDL_Rect camera = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};

    init_SDL(&game);

    SDL_Texture * eichenwalde = load_map(&game, "/home/jackson/td_ow/img/eich.jpeg");

    GAME_RUNNING = true;
    while (GAME_RUNNING) {
        clear_screen(&game);
        poll_inputs(&camera);

        draw_map(&game, &camera, eichenwalde);
        draw_hexagons(&game, &camera);
        present_scene(&game);
        SDL_Delay(16);
    }

    SDL_Quit();

    return 0;
}
