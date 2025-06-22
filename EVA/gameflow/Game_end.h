#ifndef __GAME_END__
#define __GAME_END__

#include "Game_state.h"
#include "Assets.h"

typedef struct game_end {
    unsigned char Return_to_stage_select_selected;
    ALLEGRO_COLOR Return_to_stage_select_color;
    unsigned char Back_to_title_screen_selected;
    ALLEGRO_COLOR Back_to_title_screen_color;
    unsigned char game_end_exit;
} game_end;

void start_game_end (game_state *state, game_end **game_end_info, ALLEGRO_BITMAP **game_end_image);
void show_game_end (ALLEGRO_EVENT *event, game_state *state, ALLEGRO_FONT *font, ALLEGRO_DISPLAY *disp, game_assets *assets, int X_SCREEN, int Y_SCREEN);
void game_end_down_move(game_end *game_end_info);
void game_end_up_move(game_end *game_end_info);
void game_end_confirm(game_state *state,game_end *game_end_info);
void game_end_draw_text(game_end *game_end_info, ALLEGRO_FONT *font, int X_SCREEN, int Y_SCREEN);
void exit_game_end(game_state *state,game_end *game_end_info, ALLEGRO_BITMAP *game_end_image);

#endif