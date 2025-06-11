#ifndef __PAUSE__
#define __PAUSE__

#include "Game_state.h"
#include "Assets.h"

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

void start_pause (game_state *state, pause_game **pause_info, ALLEGRO_BITMAP **pause_image);

void show_pause (ALLEGRO_EVENT *event, game_state *state, ALLEGRO_FONT *font, ALLEGRO_DISPLAY *disp, game_assets *assets, int X_SCREEN, int Y_SCREEN);

///////////////////////////////////// Funções auxiliares de Pause /////////////////////////////////////////////////////////////////////////

void pause_down_move(pause_game *pause_info);

void pause_up_move(pause_game *pause_info);

void pause_confirm(game_state *state,pause_game *pause_info);

void pause_draw_text(pause_game *pause_info, ALLEGRO_FONT *font, int X_SCREEN, int Y_SCREEN);

void exit_pause(game_state *state,pause_game *pause_info, ALLEGRO_BITMAP *pause_image);

void exit_level(game_state *state, game_assets *assets);
#endif