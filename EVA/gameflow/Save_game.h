#ifndef __SAVE_GAME__
#define __SAVE_GAME__

#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro5.h>																																												
#include <allegro5/allegro_font.h>																																											
#include <allegro5/allegro_primitives.h>	
#include "Game_state.h"

typedef struct save_game {

    unsigned char slot_1_selected;
    unsigned char choose_slot_1_selected;
    unsigned char slot_2_selected;
    unsigned char choose_slot_2_selected; 
    unsigned char slot_3_selected;
    unsigned char choose_slot_3_selected; 
    unsigned char return_to_stage_select_selected;
    unsigned char return_to_stage_select;

} save_game;

save_game *save_game_info_create();
void start_save_game (game_state *state, ALLEGRO_BITMAP **save_game_image, save_game **save_game_info);
void show_save_game();

//aux
void save_game_down_move (save_game *save_game_info );
void save_game_up_move(save_game *save_game_info );
void save_game_left_move(save_game *save_game_info );
void save_game_right_move(save_game *save_game_info );
void save_game_confirm(game_state *state, save_game *save_game_info, ALLEGRO_BITMAP *save_game_image);
void save_game();
#endif