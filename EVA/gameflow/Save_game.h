#ifndef __SAVE_GAME__
#define __SAVE_GAME__

// tela de salvar jogo

#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro5.h>																																												
#include <allegro5/allegro_font.h>																																											
#include <allegro5/allegro_primitives.h>	
#include "Game_state.h"

struct player_data;

// info do menu
typedef struct save_game {
    unsigned char slot_1_selected;
    unsigned char choose_slot_1_selected;
    ALLEGRO_COLOR choose_slot_1_color;
    unsigned char slot_2_selected;
    unsigned char choose_slot_2_selected; 
    ALLEGRO_COLOR choose_slot_2_color;
    unsigned char slot_3_selected;
    unsigned char choose_slot_3_selected;
    ALLEGRO_COLOR choose_slot_3_color;     
    unsigned char return_to_stage_select_selected;
    unsigned char return_to_stage_select;

    struct player_data *player_progress_slot_1;
    struct player_data *player_progress_slot_2;
    struct player_data *player_progress_slot_3;

    int timer;
} save_game;

// cria info
save_game *save_game_info_create();

// inicializa
void start_save_game (game_state *state, save_game **save_game_info, ALLEGRO_BITMAP **save_game_image, ALLEGRO_BITMAP **default_slot_image);

// mostra na tela
void show_save_game (ALLEGRO_EVENT *event, game_state *state, ALLEGRO_FONT *font, ALLEGRO_DISPLAY *disp, ALLEGRO_BITMAP *save_game_image, ALLEGRO_BITMAP *default_slot_image , 
                        save_game *save_game_info, int X_SCREEN, int Y_SCREEN);

/////////////////////// FUNÇÕES DE INTERAÇÕES NO MENU ////////////////////////

void save_game_down_move (save_game *save_game_info );
void save_game_up_move(save_game *save_game_info );
void save_game_left_move(save_game *save_game_info );
void save_game_right_move(save_game *save_game_info );
void save_game_confirm(game_state *state, save_game *save_game_info, ALLEGRO_BITMAP *save_game_image);
///////////////////////////////////////////////////////////////////////////////////

///////////////////////////// Auxiliares /////////////////////////////////////////

// desenha o texto
void save_game_draw_text(ALLEGRO_BITMAP *default_slot_image, save_game *save_game_info, ALLEGRO_FONT *font, int X_SCREEN, int Y_SCREEN);

// escreve o arquivo binário com o progresso e mapeamento de teclas do jogador, atualiza que aquele slot agora não tem info NULL
void save_game_slot(game_state *state, save_game *save_game_info, int slot);

// libera memoria
void exit_save_game(game_state *state, save_game *save_game_info,ALLEGRO_BITMAP *save_game_image);
#endif