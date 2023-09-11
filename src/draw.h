#pragma once

#include "defs.h"

void clear_screen(Game * game);
void draw_hexagons(Game * game, SDL_Rect * camera);
void draw_map(Game * game, SDL_Rect * camera, SDL_Texture * map);
void present_scene(Game * game);
