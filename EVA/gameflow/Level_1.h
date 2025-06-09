// Level_1.h
#ifndef __LEVEL_1__
#define __LEVEL_1__

#include "Title_screen.h"
#include "Assets.h"
#include "../entities/Player.h"
#include "../mechanics/Objects.h"
#define MAX_PLATFORMS 20


typedef entities_sprites entities_sprites;

typedef struct level_1 {
    float FLOOR; //altura do chão no começo
    Player *player; 
    float camera_x;   
    Platform platforms[MAX_PLATFORMS]; // Um array para até 20 plataformas
    int num_platforms;     // O número de plataformas que realmente existem
} level_1;


void start_level_1(game_state *state, level_1 **level_1_info, entities_sprites *sprites, int Y_SCREEN);
void show_level_1(ALLEGRO_EVENT *event, game_state *state, ALLEGRO_FONT *font, ALLEGRO_DISPLAY *disp,entities_sprites *sprites, level_1 *level_1_info, int X_SCREEN, int Y_SCREEN);
void level_1_update(level_1 *level_1_info, int X_SCREEN);

//aux
void draw_level_1_background(float camera_x, entities_sprites *sprites, int X_SCREEN, int Y_SCREEN, float FLOOR);
void draw_player(float camera_x, Player *player, entities_sprites *sprites); // <<< NOVO

#endif