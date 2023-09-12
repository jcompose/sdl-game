#include <SDL2/SDL.h>
#include "defs.h"
#include "input.h"
#include <stdio.h>
#include <math.h>

const float SMALLER = 0.8;
const float LARGER = 1 / SMALLER;
const float ASPECT_RATIO = (float) SCREEN_WIDTH / SCREEN_HEIGHT;

bool middle_mouse_button_pressed = false;

void handle_keydown(SDL_Event event) {
    if (event.key.keysym.sym == 'q') {
        GAME_RUNNING = false;
    }
}

int map(int val, int i_lower, int i_upper, int o_lower, int o_upper) {
    return (val-i_lower)*(o_upper-o_lower)/(i_upper-i_lower)+o_lower;
}

void handle_mousewheel(SDL_Event event, SDL_Rect * camera) {
    // Stored so we don't have to compare more than once
    const bool zoom_in = (event.wheel.y > 0);

    // mapped_x and mapped_y represent the pixels in the BG image that were hovered over
    const int mapped_x = map(current_mouse_position.x, 0, SCREEN_WIDTH, camera->x, camera->x + camera->w);
    const int mapped_y = map(current_mouse_position.y, 0, SCREEN_HEIGHT, camera->y, camera->y + camera->h);

    // Update the width and the height to the bigger / smaller values
    const float scale_factor = (zoom_in) ? SMALLER : LARGER;

    // Make sure you can't zoom in / out too far
    if (camera->h * scale_factor * (LARGER-1) < 1) { return; }
    if (camera->h * scale_factor > SCREEN_HEIGHT) { return; }

    // Update the Camera width and height by scale factor
    camera->h = (int)(camera->h * scale_factor);
    camera->w = (int)(camera->h * ASPECT_RATIO); // This is on purpose

    // Update the Camera x and y if zoom in
    if (zoom_in) {
        camera->x = (int)(mapped_x - camera->w / 2.);
        camera->y = (int)(mapped_y - camera->h / 2.);
    }

    // Min and Max bounds
    if (camera->x < 0) { camera->x = 0; }
    if (camera->y < 0) { camera->y = 0; }
    if (camera->x > SCREEN_WIDTH - camera->w) { camera->x = (int)(SCREEN_WIDTH - camera->w); }
    if (camera->y > SCREEN_HEIGHT - camera->h) { camera->y = (int)(SCREEN_HEIGHT - camera->h); }
}

void handle_mousemotion(SDL_Event event, SDL_Rect * camera) {
    SDL_GetMouseState(&current_mouse_position.x, &current_mouse_position.y);

    if (middle_mouse_button_pressed) {
        const float proportion = (float) camera->w / SCREEN_WIDTH;

        const float translation_x = proportion * (current_mouse_position.x - previous_mouse_position.x);
        const float translation_y = proportion * (current_mouse_position.y - previous_mouse_position.y);

        const bool move_x = !(camera->x - translation_x < 0 || camera->x - translation_x > SCREEN_WIDTH - camera->w);
        const bool move_y = !(camera->y - translation_y < 0 || camera->y - translation_y > SCREEN_HEIGHT - camera->h);

        camera->x -= translation_x * move_x;
        camera->y -= translation_y * move_y;
    }

    SDL_GetMouseState(&previous_mouse_position.x, &previous_mouse_position.y);
}

void handle_mousebuttondown(SDL_Event event) { 
    if (event.button.button == SDL_BUTTON_MIDDLE) {
        SDL_GetMouseState(&previous_mouse_position.x, &previous_mouse_position.y);
        middle_mouse_button_pressed = true;
    }
}

void handle_mousebuttonup(SDL_Event event) { 
    if (event.button.button == SDL_BUTTON_MIDDLE) {
        middle_mouse_button_pressed = false;
    }
}

void poll_inputs(SDL_Rect * camera) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                GAME_RUNNING = false;
                break;

            case SDL_KEYDOWN:
                handle_keydown(event);
                break;

            case SDL_MOUSEWHEEL:
                handle_mousewheel(event, camera);
                break;

            case SDL_MOUSEMOTION:
                handle_mousemotion(event, camera);
                break;

            case SDL_MOUSEBUTTONDOWN:
                handle_mousebuttondown(event);
                break;

            case SDL_MOUSEBUTTONUP:
                handle_mousebuttonup(event);
                break;

            default:
                break;
        }
    }
}
