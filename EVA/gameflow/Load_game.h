#ifndef __LOAD_GAME__
#define __LOAD_GAME__

// tela de carregar jogo

#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro5.h>																																												
#include <allegro5/allegro_font.h>																																											
#include <allegro5/allegro_primitives.h>	
#include "Game_state.h"
#include "Assets.h"

struct player_data;

// info do menu
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

//cria info menu
load_game *load_game_info_create();

// Além de inicializar, carrega as informações de jogo salva dos slots para caso o jogador carregue um jogo
// seja só substituir. Além disso, para o feedback visual de ver se o slot está vazio ou se tem algum jogo salvo com progresso
void start_load_game (game_state *state, load_game **load_game_info, ALLEGRO_BITMAP **load_game_image, ALLEGRO_BITMAP **default_slot_image);

//mostra na tela
void show_load_game (ALLEGRO_EVENT *event, game_state *state, ALLEGRO_FONT *font, ALLEGRO_DISPLAY *disp, game_assets *assets, int X_SCREEN, int Y_SCREEN);

///////////////////// FUNÇÕES DE INTERAÇÕES NO MENU ////////////////////////

// move para baixo
void load_game_down_move (load_game *load_game_info );

// move pra cima
void load_game_up_move(load_game *load_game_info );

// move pra esquerda
void load_game_left_move(load_game *load_game_info );

// move pra direita
void load_game_right_move(load_game *load_game_info );

// tecla de confirmar
// antes de carregar um jogo, verifica se não é NULL
void load_game_confirm(game_state *state, load_game *load_game_info, ALLEGRO_BITMAP *load_game_image);

////////////////////////////////////////////////////////////////////////////

/////////////////////// Auxiliares ///////////////////////////////////////

//desenha o texto
void load_game_draw_text(ALLEGRO_BITMAP *default_slot_image, load_game *load_game_info, ALLEGRO_FONT *font, int X_SCREEN, int Y_SCREEN);

// Carrega o dado salvo em si, ou seja, substitui as informações do player_progress e controles atuais
// pelas informações do slot
void load_game_slot(game_state *state, load_game *load_game_info, int slot);

// sai do load game liberando memória
void exit_load_game(game_state *state, game_assets *assets);

//////////////////////////// Auxiliares de tradução ///////////////////////////

// Transforma o progresso das fases em uma string da forma "Progress: X/8"
const char* get_progress_string(struct player_data *progress);

// Transforma o tempo de jogo em uma string da forma "Playtime: XhY"
const char* get_time_string(struct player_data *progress);
#endif