#ifndef __GAME_STATE__
#define __GAME_STATE__

// Arquivo que contém informações essenciais para rodar as etapas
// informações guardadas além do próprio estado que está rodando

//é o arquivo mãe, por isso está incluindo todos os outros
#include "Assets.h"
#include "Title_screen.h"
#include "Level_select.h"
#include "Options.h"
#include "Pause.h"
#include "Save_game.h"
#include "Load_game.h"
#include "Game_over.h"
#include "Game_end.h"
#include <allegro5/allegro.h>

#include "../levels/Level_1.h"
#include "../levels/Level_2.h"
#include "../levels/Level_3.h"
#include "../levels/Level_4.h"
#include "../levels/Level_5.h"
#include "../levels/Level_6.h"
#include "../levels/Level_7.h"
#include "../levels/Level_8.h" 

// a dificuldade do jogo é um fator multiplicativo
#define DIFFICULTY_EASY 0.75 
#define DIFFICULTY_MEDIUM 1.0
#define DIFFICULTY_HARD 1.25

// Estrutura com os valores chaves (para o Allegro conseguir comparar)
// do mapeamento do teclado do jogador
typedef struct buttom_map {
    int SHOT;
    int JUMP;
    int LEFT;
    int RIGHT;
    int UP;
    int DOWN;
    int CONFIRM;
    int PAUSE;    
} buttom_map;

// informações do jogador sobre o progresso dele no jogo
typedef struct player_data {
    int Lifes;
    float dificulty; //corresponde a um fator multiplicativo do EASY, MEDIUM, HARD

    unsigned char Level_1_completed; //progresso
    unsigned char Level_2_completed;
    unsigned char Level_3_completed;
    unsigned char Level_4_completed;
    unsigned char Level_5_completed;
    unsigned char Level_6_completed;
    unsigned char Level_7_completed;
    unsigned char Level_8_completed;

    double start_time;  //informação útil para calcular o tempo de jogo
    double total_play_time; //tempo de jogo

} player_data;

// a estrutura mãe, que nos informa a etapa que o jogo está
typedef struct game_state {
    unsigned char running;
    unsigned char title_screen;
    unsigned char title_screen_started;
    unsigned char level_select;
    unsigned char level_select_started;
    unsigned char load_game;
    unsigned char load_game_started;
    unsigned char options;
    unsigned char options_started;
    unsigned char pause;
    unsigned char pause_started;
    unsigned char save_game;
    unsigned char save_game_started;
    unsigned char game_over;
    unsigned char game_over_started;
    unsigned char game_end;
    unsigned char game_end_started;

    unsigned char level_1;
    unsigned char level_1_started;
    unsigned char level_2;
    unsigned char level_2_started;
    unsigned char level_3;
    unsigned char level_3_started;
    unsigned char level_4;
    unsigned char level_4_started;
    unsigned char level_5;
    unsigned char level_5_started;
    unsigned char level_6;
    unsigned char level_6_started;
    unsigned char level_7;
    unsigned char level_7_started;
    unsigned char level_8;
    unsigned char level_8_started;

    float sound_volume;
    int checkpoint; //serve para saber se está em algum checkpoint na fase 
    buttom_map *controls;
    player_data *player_progress;
} game_state;

////////////////////// Dicionário para o mapeamento de tecla //////////////////////////////////

// o dicionário (chave - valor) da chave do allegro de uma tecla
// e da string dessa tecla (para imprimir na tela em Options)
typedef struct {
    int keycode;         // ALLEGRO_KEY
    const char *name;    // a tecla em si
} key_map_t;


//O mapeamento de teclas tem suporte para as teclas desse dicionário
// outras teclas não são reconhecidas
static const key_map_t key_map[] = {
    // Letras
    {ALLEGRO_KEY_A, "A"},
    {ALLEGRO_KEY_B, "B"},
    {ALLEGRO_KEY_C, "C"},
    {ALLEGRO_KEY_D, "D"},
    {ALLEGRO_KEY_E, "E"},
    {ALLEGRO_KEY_F, "F"},
    {ALLEGRO_KEY_G, "G"},
    {ALLEGRO_KEY_H, "H"},
    {ALLEGRO_KEY_I, "I"},
    {ALLEGRO_KEY_J, "J"},
    {ALLEGRO_KEY_K, "K"},
    {ALLEGRO_KEY_L, "L"},
    {ALLEGRO_KEY_M, "M"},
    {ALLEGRO_KEY_N, "N"},
    {ALLEGRO_KEY_O, "O"},
    {ALLEGRO_KEY_P, "P"},
    {ALLEGRO_KEY_Q, "Q"},
    {ALLEGRO_KEY_R, "R"},
    {ALLEGRO_KEY_S, "S"},
    {ALLEGRO_KEY_T, "T"},
    {ALLEGRO_KEY_U, "U"},
    {ALLEGRO_KEY_V, "V"},
    {ALLEGRO_KEY_W, "W"},
    {ALLEGRO_KEY_X, "X"},
    {ALLEGRO_KEY_Y, "Y"},
    {ALLEGRO_KEY_Z, "Z"},

    // Números (teclado alfanumérico)
    {ALLEGRO_KEY_0, "0"},
    {ALLEGRO_KEY_1, "1"},
    {ALLEGRO_KEY_2, "2"},
    {ALLEGRO_KEY_3, "3"},
    {ALLEGRO_KEY_4, "4"},
    {ALLEGRO_KEY_5, "5"},
    {ALLEGRO_KEY_6, "6"},
    {ALLEGRO_KEY_7, "7"},
    {ALLEGRO_KEY_8, "8"},
    {ALLEGRO_KEY_9, "9"},

    // Números (teclado numérico)
    {ALLEGRO_KEY_PAD_0, "PAD 0"},
    {ALLEGRO_KEY_PAD_1, "PAD 1"},
    {ALLEGRO_KEY_PAD_2, "PAD 2"},
    {ALLEGRO_KEY_PAD_3, "PAD 3"},
    {ALLEGRO_KEY_PAD_4, "PAD 4"},
    {ALLEGRO_KEY_PAD_5, "PAD 5"},
    {ALLEGRO_KEY_PAD_6, "PAD 6"},
    {ALLEGRO_KEY_PAD_7, "PAD 7"},
    {ALLEGRO_KEY_PAD_8, "PAD 8"},
    {ALLEGRO_KEY_PAD_9, "PAD 9"},

    // Teclas especiais
    {ALLEGRO_KEY_SPACE, "SPACE"},
    {ALLEGRO_KEY_ENTER, "ENTER"},
    {ALLEGRO_KEY_ESCAPE, "ESCAPE"},
    {ALLEGRO_KEY_LSHIFT, "LEFT SHIFT"},
    {ALLEGRO_KEY_RSHIFT, "RIGHT SHIFT"},
    {ALLEGRO_KEY_LCTRL, "LEFT CTRL"},
    {ALLEGRO_KEY_RCTRL, "RIGHT CTRL"},
    {ALLEGRO_KEY_PAD_ENTER, "PAD ENTER"},

    // Setas
    {ALLEGRO_KEY_UP, "UP"},
    {ALLEGRO_KEY_DOWN, "DOWN"},
    {ALLEGRO_KEY_LEFT, "LEFT"},
    {ALLEGRO_KEY_RIGHT, "RIGHT"},

};

// cria a estrutura de progresso do player
player_data *create_player_progress();

//cria o estado do jogo
game_state *game_state_create();

//libera memória
void game_state_destroy(game_state *state);

#endif