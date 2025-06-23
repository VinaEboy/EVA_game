#ifndef __PAUSE__
#define __PAUSE__

// é o menu de pausar o jogo
// ao pausar o jogo, você não sai da etapa do level, por isso é possível
// voltar ao jogo da onde você parou

#include "Game_state.h"
#include "Assets.h"

// info do menu de pause
typedef struct pause_game {
    unsigned char Return_to_mission_selected;
    ALLEGRO_COLOR Return_to_mission_color;
    unsigned char Options_selected;
    ALLEGRO_COLOR Options_color;
    unsigned char Return_to_stage_select_selected;
    ALLEGRO_COLOR Return_to_stage_select_color;
    unsigned char Back_to_title_screen_selected;
    ALLEGRO_COLOR Back_to_title_screen_color;
    unsigned char pause_exit;
} pause_game;

// inicializa
void start_pause (game_state *state, pause_game **pause_info, ALLEGRO_BITMAP **pause_image);

// mostra
void show_pause (ALLEGRO_EVENT *event, game_state *state, ALLEGRO_FONT *font, ALLEGRO_DISPLAY *disp, game_assets *assets, int X_SCREEN, int Y_SCREEN);

/////////////////////// FUNÇÕES DE INTERAÇÕES NO MENU ////////////////////////

// para baixo
void pause_down_move(pause_game *pause_info);

// para cima
void pause_up_move(pause_game *pause_info);

// confirmar
void pause_confirm(game_state *state,pause_game *pause_info);

///////////////////////////////////////////////////////////////////////////////////

///////////////////////////// Auxiliares /////////////////////////////////////////

// desenha o texto
void pause_draw_text(pause_game *pause_info, ALLEGRO_FONT *font, int X_SCREEN, int Y_SCREEN);

// sai da etapa de pause
void exit_pause(game_state *state,pause_game *pause_info, ALLEGRO_BITMAP *pause_image);

// sai do level que estava (porque o pause está disponivel no level)
void exit_level(game_state *state, game_assets *assets);

#endif
