#ifndef __GAME_OVER__
#define __GAME_OVER__

#include "Game_state.h"
#include "Assets.h"

typedef struct game_over {
    unsigned char Load_game_selected;
    ALLEGRO_COLOR Load_game_color;
    unsigned char Options_selected;
    ALLEGRO_COLOR Options_color;
    unsigned char Return_to_stage_select_selected;
    ALLEGRO_COLOR Return_to_stage_select_color;
    unsigned char Back_to_title_screen_selected;
    ALLEGRO_COLOR Back_to_title_screen_color;
    unsigned char game_over_exit;
} game_over;

void start_game_over (game_state *state, game_over **game_over_info, ALLEGRO_BITMAP **game_over_image);

void show_game_over (ALLEGRO_EVENT *event, game_state *state, ALLEGRO_FONT *font, ALLEGRO_DISPLAY *disp, game_assets *assets, int X_SCREEN, int Y_SCREEN);

///////////////////////////////////// Funções auxiliares de Pause /////////////////////////////////////////////////////////////////////////

void game_over_down_move(game_over *game_over_info);

void game_over_up_move(game_over *game_over_info);

void game_over_confirm(game_state *state,game_over *game_over_info);

void game_over_draw_text(game_over *game_over_info, ALLEGRO_FONT *font, int X_SCREEN, int Y_SCREEN);

void exit_game_over(game_state *state,game_over *game_over_info, ALLEGRO_BITMAP *game_over_image);

#endif