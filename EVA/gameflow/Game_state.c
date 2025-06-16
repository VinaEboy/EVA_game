#include <stdlib.h>
#include "Game_state.h"

#include "Title_screen.h"
#include <allegro5/allegro5.h>	

game_state *game_state_create() {
    game_state *new_game_state = (game_state*) malloc(sizeof(game_state));
    if(!new_game_state) return NULL;
    new_game_state->running = 1;
    new_game_state->title_screen = 1; // o jogo começa pela tela principal
    new_game_state->title_screen_started = 0; // ainda não carregou/inicializou a tela principal
    new_game_state->level_select = 0;
    new_game_state->level_select_started = 0;
    new_game_state->level_1= 0;
    new_game_state->level_1_started = 0;
    new_game_state->load_game = 0;
    new_game_state->load_game_started = 0;
    new_game_state->options = 0;
    new_game_state->options_started = 0;
    new_game_state->pause = 0;
    new_game_state->pause_started = 0;
    new_game_state->save_game = 0;
    new_game_state->save_game_started = 0;
    new_game_state->checkpoint = 0;
    new_game_state->game_over = 0;
    new_game_state->game_over_started = 0;

    player_data *player_progress = (player_data *) malloc(sizeof(player_data));
    if (!player_progress) {
        free(player_progress);
        return NULL;
    }
    player_progress->Lifes = 3;
    player_progress->Hearts = 0;
    player_progress->dificulty = DIFFICULTY_MEDIUM; //o default é dificuldade média
    player_progress->Level_1_completed = 0;
    player_progress->Level_2_completed = 0;
    player_progress->Level_3_completed = 0;
    player_progress->Level_4_completed = 0;
    player_progress->Level_5_completed = 0;
    player_progress->Level_6_completed = 0;
    player_progress->Level_7_completed = 0;
    player_progress->Level_8_completed = 0;
    player_progress->start_time = al_get_time();
    player_progress->total_play_time = 0;
    new_game_state->player_progress = player_progress;

    buttom_map *controls = (buttom_map *) malloc(sizeof(buttom_map));
    if(!controls) {
        free(new_game_state->player_progress);
        free(new_game_state);
        return NULL;
    } 
    controls->SHOT = ALLEGRO_KEY_K ;
    controls->JUMP = ALLEGRO_KEY_SPACE;
    controls->LEFT = ALLEGRO_KEY_A;
    controls->RIGHT = ALLEGRO_KEY_D;
    controls->UP = ALLEGRO_KEY_W;
    controls->DOWN = ALLEGRO_KEY_S;
    controls->CONFIRM = ALLEGRO_KEY_ENTER;
    controls->PAUSE = ALLEGRO_KEY_ESCAPE;    
    new_game_state->controls = controls;
    return new_game_state;
}

void game_state_destroy(game_state *state) {
    free(state);
}

