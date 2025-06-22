#ifndef __LEVEL_SELECT__
#define __LEVEL_SELECT__

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>		
#include <allegro5/allegro_ttf.h>
#include <stdlib.h>
#include <stdio.h>
#include "Game_state.h"

typedef struct game_state game_state;

typedef struct level_select {
    unsigned char Level_1_selected;
    unsigned char Level_2_selected;
    unsigned char Level_3_selected;
    unsigned char Level_4_selected;
    unsigned char Level_5_selected;
    unsigned char Level_6_selected;
    unsigned char Level_7_selected;
    unsigned char Level_8_selected;
    unsigned char Shinji_selected;
    unsigned char Back_title_screen_selected;
    ALLEGRO_COLOR Back_title_screen_color;
    unsigned char Save_game_selected;  
    ALLEGRO_COLOR Save_game_color;
    unsigned char warning_no_level;
    unsigned char level_select_exit;
    unsigned char warning_return_title_screen;
    unsigned char return_yes;
    unsigned char return_no;
    int timer;
} level_select;

level_select *level_select_info_create();
void start_level_select( );
void start_level_select(game_state *state, level_select **level_select_info, ALLEGRO_BITMAP **level_select_image );

void show_level_select(ALLEGRO_EVENT *event, game_state *state, ALLEGRO_FONT *font, ALLEGRO_DISPLAY *disp, ALLEGRO_BITMAP *level_select_image, 
                        level_select *level_select_info, int X_SCREEN, int Y_SCREEN);

// aux 
void warning_return_title_screen(game_state *state, level_select *level_select_info,ALLEGRO_FONT *font, int X_SCREEN, int Y_SCREEN);
void level_select_left_move(level_select *level_select_info);
void title_screen_right_move(level_select *level_select_info);
void level_select_down_move(level_select*level_select_info);
void level_select_up_move(level_select *level_select_info);
void level_select_confirm(game_state *state,level_select *level_select_info,ALLEGRO_BITMAP *level_select_image);
void warning_no_level(ALLEGRO_FONT *font, int X_SCREEN, int Y_SCREEN);
void exit_level_select (game_state *state, level_select *level_select_info,ALLEGRO_BITMAP *level_select_image );
void level_select_draw_text(ALLEGRO_FONT *font, level_select *level_select, int X_SCREEN, int Y_SCREEN) ;
void draw_defeated_levels(game_state *state, int X_SCREEN, int Y_SCREEN) ;
#endif
