#ifndef __LOAD_GAME__
#define __LOAD_GAME__

#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro5.h>																																												
#include <allegro5/allegro_font.h>																																											
#include <allegro5/allegro_primitives.h>	
#include "Game_state.h"
#include "Assets.h"

struct player_data;

typedef struct load_game {
    unsigned char slot_1_selected;
    unsigned char choose_slot_1_selected;
    ALLEGRO_COLOR choose_slot_1_color;
    unsigned char slot_2_selected;
    unsigned char choose_slot_2_selected; 
    ALLEGRO_COLOR choose_slot_2_color;
    unsigned char slot_3_selected;
    unsigned char choose_slot_3_selected;
    ALLEGRO_COLOR choose_slot_3_color;     
    unsigned char return_selected;
    unsigned char load_game_exit;
    unsigned char game_loaded; //para saber se algum jogo foi carregado ou se está saindo porque retornou

    struct player_data *player_progress_slot_1;
    struct player_data *player_progress_slot_2;
    struct player_data *player_progress_slot_3;
    struct buttom_map *controls_slot_1;
    struct buttom_map *controls_slot_2;
    struct buttom_map *controls_slot_3;

    int timer;
} load_game;

load_game *load_game_info_create();
void start_load_game (game_state *state, load_game **load_game_info, ALLEGRO_BITMAP **load_game_image, ALLEGRO_BITMAP **default_slot_image);
void show_load_game (ALLEGRO_EVENT *event, game_state *state, ALLEGRO_FONT *font, ALLEGRO_DISPLAY *disp, game_assets *assets, int X_SCREEN, int Y_SCREEN);

//aux
void load_game_down_move (load_game *load_game_info );
void load_game_up_move(load_game *load_game_info );
void load_game_left_move(load_game *load_game_info );
void load_game_right_move(load_game *load_game_info );
void load_game_confirm(game_state *state, load_game *load_game_info, ALLEGRO_BITMAP *load_game_image);
void load_game_draw_text(ALLEGRO_BITMAP *default_slot_image, load_game *load_game_info, ALLEGRO_FONT *font, int X_SCREEN, int Y_SCREEN);
void load_game_slot(game_state *state, load_game *load_game_info, int slot);
void exit_load_game(game_state *state, game_assets *assets);

const char* get_progress_string(struct player_data *progress);
const char* get_time_string(struct player_data *progress);
#endif