#include "SDL.h"
#include "SDL_events.h"
#include "SDL_mouse.h"
#include "defs.h"
#include "input.h"
#include <stdio.h>

struct {
    int x;
    int y;
} mouse;

const float SMALLER = 0.8;
const float LARGER = 1 / SMALLER;
const float ASPECT_RATIO = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;

void handle_keydown(SDL_Event event) {
    if (event.key.keysym.sym == 'q') {
        GAME_RUNNING = false;
    }
}

int map(int val, int i_lower, int i_upper, int o_lower, int o_upper) {
    return (val-i_lower)*(o_upper-o_lower)/(i_upper-i_lower)+o_lower;
}

void handle_mousewheel(SDL_Event event, SDL_Rect * camera) {
    // Update the literal mouse position (x: [0, w]; y: [0, h])
    SDL_GetMouseState(&mouse.x, &mouse.y);

    // mapped_x and mapped_y represent the pixels in the BG image that were hovered over
    const int mapped_x = map(mouse.x, 0, SCREEN_WIDTH, camera->x, camera->x + camera->w);
    const int mapped_y = map(mouse.y, 0, SCREEN_HEIGHT, camera->y, camera->y + camera->h);

    // Update the width and the height to the bigger / smaller values
    const float scale_factor = (event.wheel.y > 0) ? SMALLER : LARGER;

    // Make sure you can't zoom in too far
    // TODO this only works if W > H
    if (camera->h * scale_factor * (LARGER-1) < 1) { return; }

    // Make sure you can't zoom in too not far
    // TODO this only works if W > H
    if (camera->h * scale_factor > SCREEN_HEIGHT) { return; }

    // Update the Camera width and height by scale factor
    camera->h = (int)(camera->h * scale_factor);
    camera->w = (int)(camera->h * ASPECT_RATIO);

    // Update the Camera x and y
    camera->x = (int)(mapped_x - camera->w / 2.);
    camera->y = (int)(mapped_y - camera->h / 2.);

    // Min and Max bounds
    if (camera->x < 0) { camera->x = 0; }
    if (camera->y < 0) { camera->y = 0; }
    if (camera->x > SCREEN_WIDTH - camera->w) { camera->x = (int)(SCREEN_WIDTH - camera->w); }
    if (camera->y > SCREEN_HEIGHT - camera->h) { camera->y = (int)(SCREEN_HEIGHT - camera->h); }

    // BUG print statements
    printf("----------\n");
    printf("Camera x: %i\n", camera->x);
    printf("Camera y: %i\n", camera->y);
    printf("Camera w: %i\n", camera->w);
    printf("Camera h: %i\n", camera->h);
    printf("----------\n");
}

void handle_mousemotion(SDL_Event event) { }

void handle_mousebuttondown(SDL_Event event, SDL_Rect * camera) { }

void poll_inputs(SDL_Rect * camera) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                exit(0);
                break;

            case SDL_KEYDOWN:
                handle_keydown(event);
                break;

            case SDL_MOUSEWHEEL:
                handle_mousewheel(event, camera);
                break;

            case SDL_MOUSEMOTION:
                handle_mousemotion(event);
                break;

            case SDL_MOUSEBUTTONDOWN:
                handle_mousebuttondown(event, camera);
                break;

            default:
                break;
        }
    }
}
