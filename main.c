#include "SDL.h"
#include "player.h"
#include "SDL_events.h"
#include "SDL_keycode.h"
#include "SDL_rect.h"
#include "SDL_render.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

// Global Variables 
bool running = true;

Player p = {
    .hitbox.x = 100,
    .hitbox.y = 100,
    .hitbox.w = 100,
    .hitbox.h = 100,
    .vx = 0,
    .vy = 0,
    .c = 0xFFFF00FF
};

void handle_keydown(SDL_Renderer * renderer, SDL_Event event) {
    // Quit the game
    if (event.key.keysym.sym == SDLK_q) { running = false; }

    // Movement
    if (event.key.keysym.sym == SDLK_UP) { p.vy = -5; }
    if (event.key.keysym.sym == SDLK_DOWN) { p.vy = 5; }
    if (event.key.keysym.sym == SDLK_LEFT) { p.vx = -5; }
    if (event.key.keysym.sym == SDLK_RIGHT) { p.vx = 5; }
}

void handle_keyup(SDL_Renderer * renderer, SDL_Event event) {
    // Movement
    if (event.key.keysym.sym == SDLK_UP) { p.vy = 0; }
    if (event.key.keysym.sym == SDLK_DOWN) { p.vy = 0; }
    if (event.key.keysym.sym == SDLK_LEFT) { p.vx = 0; }
    if (event.key.keysym.sym == SDLK_RIGHT) { p.vx = 0; }
}

// Main game loop
void loop(SDL_Renderer * renderer) {
    // Clear the screen
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Event handling loop -- breaks when there
    // are no more events to deal with
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN:
                handle_keydown(renderer, event);
                break;
            case SDL_KEYUP:
                handle_keyup(renderer, event);
                break;
            default:
                break;
        }
    }

    update_player(&p);
    
    // Draw the player
    SDL_SetRenderDrawColor(renderer, p.c.split.red, p.c.split.green, p.c.split.blue, p.c.split.alpha);
    SDL_RenderFillRect(renderer, &p.hitbox);
    SDL_RenderPresent(renderer);
}

int main() {
    // Init video, audio, etc. systems + error checking
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    // Game window
    SDL_Window * window = SDL_CreateWindow("SDL Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 1000, 0);

    // Error checking
    if (window == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        return 1;
    }

    // Game renderer
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Error checking
    if (renderer == NULL) {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        return 1;
    }

    // Event loop
    while (running) {
        loop(renderer);
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
