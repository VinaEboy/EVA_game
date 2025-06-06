#ifndef __LEVEL_1__
#define __LEVEL_1__

#include "Title_screen.h"
#include "Assets.h"
#include "Level_1.h"

typedef entities_sprites entities_sprites;

typedef struct level_1 {
    unsigned char inicio;
} level_1;

void start_level_1(game_state *state, level_1 **level_1_info, entities_sprites *sprites);

void show_level_1(ALLEGRO_EVENT *event, game_state *state, ALLEGRO_FONT *font, ALLEGRO_DISPLAY *disp, entities_sprites *sprites, level_1 *level_1_info, int X_SCREEN, int Y_SCREEN);

// aux

void draw_level_1_background(float camera_x, entities_sprites *sprites, int X_SCREEN, int Y_SCREEN);

#endif