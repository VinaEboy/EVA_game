#include <stdlib.h>
#include "Game_state.h"

#include "Title_screen.h"

game_state *game_state_create() {
    game_state *new_game_state = (game_state*) malloc(sizeof(game_state));
    if(!new_game_state) return NULL;
    new_game_state->running = 1;
    new_game_state->title_screen = 1; // o jogo começa pela tela principal
    new_game_state->title_screen_started = 0; // ainda não carregou/inicializou a tela principal
    new_game_state->level_select = 0;
    new_game_state->level_select_started = 0;
    new_game_state->level_sachiel = 0;
    new_game_state->level_sachiel_started = 0;
    new_game_state->load_game = 0;
    new_game_state->load_game_started = 0;
    new_game_state->options = 0;
    buttom_map *controls = (buttom_map *) malloc(sizeof(buttom_map));
    if(!controls) {
        free(new_game_state);
        return NULL;
    } 
    controls->SHOT = ALLEGRO_KEY_Z ;
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