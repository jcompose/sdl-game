#pragma once

#include "defs.h"

// Basic hero facotry design
Hero * hero_factory(Hero * source);
void hero_deconstructor(Hero * hero);

// Hero-agnostic voiceline function
void voice_line(char * line);

void lucio_left_click(void);
void lucio_right_click(void);
void lucio_shift(void);
void lucio_e(void);

void reinhardt_left_click(void);
void reinhardt_right_click(void);
void reinhardt_shift(void);
void reinhardt_e(void);

void pharah_left_click(void);
void pharah_right_click(void);
void pharah_shift(void);
void pharah_e(void);

// Hero Structs
extern Hero Ana;
extern Hero Ashe;
extern Hero Baptiste;
extern Hero Bastion;
extern Hero Brigitte;
extern Hero Cassidy;
extern Hero D_va;
extern Hero Doomfist;
extern Hero Echo;
extern Hero Genji;
extern Hero Hanzo;
extern Hero Illari;
extern Hero Junker_Queen;
extern Hero Junkrat;
extern Hero Kiriko;
extern Hero Lifeweaver;
extern Hero Lucio;
extern Hero Mei;
extern Hero Mercy;
extern Hero Moira;
extern Hero Orisa;
extern Hero Pharah;
extern Hero Ramattra;
extern Hero Reaper;
extern Hero Reinhardt;
extern Hero Roadhog;
extern Hero Sigma;
extern Hero Sojourn;
extern Hero Soldier_76;
extern Hero Sombra;
extern Hero Symmetra;
extern Hero Torbjorn;
extern Hero Tracer;
extern Hero Widowmaker;
extern Hero Winston;
extern Hero Wrecking_Ball;
extern Hero Zarya;
extern Hero Zenyatta;
