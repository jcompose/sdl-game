#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "heroes.h"

// FIXME at some point add a Player deconstructor
Hero * hero_factory(Hero * source) {
    Hero * h = (Hero *) malloc(sizeof(Hero));

    // Deep copy
    strcpy(h->name, source->name);
    strcpy(h->voice_line, source->voice_line);
    h->left_click = source->left_click;
    h->right_click = source->right_click;
    h->shift = source->shift;
    h->e = source->e;

    return h;
}

Hero Lucio = {
    .voice_line = "Lucio, comin' atcha!"
};
