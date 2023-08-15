#include "SDL_rect.h"
#include <stdint.h>
#include <stdio.h>

typedef union {
    uint32_t whole;
    struct {
        uint8_t red;
        uint8_t green;
        uint8_t blue;
        uint8_t alpha;
    } split;
} Color;

typedef struct {
    SDL_Rect hitbox;
    float vx;
    float vy;
    Color color;
} Player;

void update_player(Player * p) {
    p->hitbox.x += p->vx;
    p->hitbox.y += p->vy;
}
