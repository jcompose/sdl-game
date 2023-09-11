#pragma once

#include <SDL.h>
#include <stdbool.h>

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define PI 3.14159265358979323846

extern bool GAME_RUNNING;
extern float GAME_SCALE;

// Main SDL tools
typedef struct {
    SDL_Renderer * renderer;
    SDL_Window * window;
} Game;

// Hero
typedef struct {
    char name[20];
    char voice_line[30];
    float reload_time;
    float ult_charge;
    void (*left_click)();
    void (*right_click)();
    void (*shift)();
    void (*e)();
    SDL_Texture * textures;
} Hero;

typedef enum {
    LOADING = 0,
    ALIVE = 1,
    DEAD = 2,
    INACTIVE = 3
} Player_State;

// Player
typedef struct {
    char name[20];
    Hero * hero;
    Player_State state;
} Player;
