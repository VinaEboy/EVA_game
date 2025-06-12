#ifndef __GAME_STATE__
#define __GAME_STATE__

#include "Assets.h"
#include "Title_screen.h"
#include "Level_select.h"
#include "Options.h"
#include "../levels/Level_1.h"
#include "Pause.h"
#include "Save_game.h"
#include "Load_game.h"
#include <allegro5/allegro.h>

#define DIFFICULTY_EASY 0.75
#define DIFFICULTY_MEDIUM 1.0
#define DIFFICULTY_HARD 1.25


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

typedef struct player_data {
    int Lifes;
    int Hearts; //extensão da barra de vida original
    float Difficulty; 

    unsigned char Level_1_completed;
    unsigned char Level_2_completed;
    unsigned char Level_3_completed;
    unsigned char Level_4_completed;
    unsigned char Level_5_completed;
    unsigned char Level_6_completed;
    unsigned char Level_7_completed;
    unsigned char Level_8_completed;

    double start_time;  //informações úteis para calcular o tempo de jogo
    double total_play_time;

} player_data;

typedef struct game_state {
    unsigned char running;
    unsigned char title_screen;
    unsigned char title_screen_started;
    unsigned char level_select;
    unsigned char level_select_started;
    unsigned char level_1;
    unsigned char level_1_started;
    unsigned char load_game;
    unsigned char load_game_started;
    unsigned char options;
    unsigned char options_started;
    unsigned char pause;
    unsigned char pause_started;
    unsigned char save_game;
    unsigned char save_game_started;
    buttom_map *controls;
    player_data *player_progress;
} game_state;


typedef struct {
    int keycode;         // Ex: ALLEGRO_KEY_W
    const char *name;    // Ex: "W"
} key_map_t;


//O mapeamento de teclas tem suporte para as teclas desse dicionário
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

    // Setas
    {ALLEGRO_KEY_UP, "UP"},
    {ALLEGRO_KEY_DOWN, "DOWN"},
    {ALLEGRO_KEY_LEFT, "LEFT"},
    {ALLEGRO_KEY_RIGHT, "RIGHT"},

};


game_state *game_state_create();
void game_state_destroy(game_state *state);

#endif