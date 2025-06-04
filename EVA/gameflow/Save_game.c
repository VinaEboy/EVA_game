#include "Save_game.h"

#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro5.h>																																												
#include <allegro5/allegro_font.h>																																											
#include <allegro5/allegro_primitives.h>	
#include "Game_state.h"

save_game *save_game_info_create( ) {
    save_game *save_game_info = (save_game *) malloc(sizeof(save_game));
    if (!save_game_info) return NULL;

    save_game_info->slot_1_selected = 0; 
    save_game_info->choose_slot_1_selected = 0; 
    save_game_info->slot_2_selected = 0; 
    save_game_info->choose_slot_2_selected = 0; 
    save_game_info->slot_3_selected = 0; 
    save_game_info->choose_slot_3_selected = 0; 
    save_game_info->return_to_stage_select_selected = 1;
    save_game_info->return_to_stage_select_selected = 0;
    return save_game_info;
}

void start_save_game (game_state *state, ALLEGRO_BITMAP **save_game_image, save_game **save_game_info) {
    *save_game_image = al_load_bitmap("images/save_or_load.png");
    if (!*save_game_image) {
        fprintf(stderr, "Falha ao carregar imagem da tela de salvar jogo \n");
        exit(1);
    }
    *save_game_info = save_game_info_create();
    if (!*save_game_info) {
        fprintf(stderr, "Falha ao criar informações da tela de salvar jogo \n");
    }

    state->save_game_started = 1;
}

void show_save_game ( ) {
    return ;
}

// aux

void save_game_down_move (save_game *save_game_info ) {
    if (save_game_info->choose_slot_1_selected) {
        save_game_info->choose_slot_1_selected = 0;
        save_game_info->slot_1_selected = 1;
    } else if (save_game_info->choose_slot_2_selected) {
        save_game_info->choose_slot_2_selected = 0;
        save_game_info->slot_2_selected = 1;
    } else if (save_game_info->choose_slot_3_selected) {
        save_game_info->choose_slot_3_selected = 0;
        save_game_info->slot_3_selected = 1;
    } 
    //não reseta o slot selecionado pq precisa lembrar dessa info para retornar depois
    else if (save_game_info->slot_1_selected || save_game_info->slot_2_selected || save_game_info->slot_3_selected) {
        save_game_info->return_to_stage_select_selected = 1;
    } 
}

void save_game_up_move(save_game *save_game_info ) {
    if (save_game_info->slot_1_selected) {
        save_game_info->slot_1_selected = 0;
        save_game_info->choose_slot_1_selected = 1;
    } else if (save_game_info->slot_2_selected) {
        save_game_info->slot_2_selected = 0;
        save_game_info->choose_slot_2_selected = 1;
    } else if (save_game_info->slot_3_selected) {
        save_game_info->slot_3_selected = 0;
        save_game_info->choose_slot_3_selected = 1;
    } else if (save_game_info->return_to_stage_select_selected) {
        save_game_info->return_to_stage_select_selected = 0;
    }
}

void save_game_left_move(save_game *save_game_info ) {
    if (save_game_info->choose_slot_1_selected) {
        save_game_info->choose_slot_1_selected = 0;
        save_game_info->choose_slot_3_selected = 1;
    } else if (save_game_info->choose_slot_2_selected) {
        save_game_info->choose_slot_2_selected = 0;
        save_game_info->choose_slot_1_selected = 1;
    } else if (save_game_info->choose_slot_3_selected) {
        save_game_info->choose_slot_3_selected = 0;
        save_game_info->choose_slot_2_selected = 1;
    }
}

void save_game_right_move(save_game *save_game_info ) {
    if (save_game_info->choose_slot_1_selected) {
        save_game_info->choose_slot_1_selected = 0;
        save_game_info->choose_slot_2_selected = 1;
    } else if (save_game_info->choose_slot_2_selected) {
        save_game_info->choose_slot_2_selected = 0;
        save_game_info->choose_slot_3_selected = 1;
    } else if (save_game_info->choose_slot_3_selected) {
        save_game_info->choose_slot_3_selected = 0;
        save_game_info->choose_slot_1_selected = 1;
    }
}

void save_game_confirm(game_state *state, save_game *save_game_info, ALLEGRO_BITMAP *save_game_image) {
    if (save_game_info->slot_1_selected) {
        save_game();
    } else if (save_game_info->slot_2_selected) {
        save_game();
    } else if (save_game_info->slot_3_selected) {
        save_game();
    } else if (save_game_info->return_to_stage_select_selected) {
        state->return_to_stage_select = 1;
    }
}

void save_game() {
    return ;
}

