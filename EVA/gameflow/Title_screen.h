#ifndef __TITLE_SCREEN__
#define __TITLE_SCREEN__

// tela inicial

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>		
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

typedef struct game_state game_state;

// info do menu
typedef struct title_screen {
    unsigned char new_game_selected;
    ALLEGRO_COLOR new_game_color;
    unsigned char load_game_selected;
    ALLEGRO_COLOR load_game_color;
    unsigned char options_selected;
    ALLEGRO_COLOR options_color;
    unsigned char exit_selected;
    ALLEGRO_COLOR exit_color;
    unsigned char title_screen_exit;
} title_screen;

// cria info
title_screen *title_screen_info_create();

// inicializa
void start_title_screen(game_state *state, title_screen **title_screen_info, ALLEGRO_BITMAP** title_screen_image, ALLEGRO_AUDIO_STREAM **current_music );

// mostra na tela
void show_title_screen(ALLEGRO_EVENT *event,game_state *state,ALLEGRO_FONT *font,ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP* title_screen_image, title_screen *title_screen_info,
                       int X_SCREEN, int Y_SCREEN );

/////////////////////// FUNÇÕES DE INTERAÇÕES NO MENU ////////////////////////

void title_screen_down_move(title_screen *title_screen_info );
void title_screen_up_move(title_screen *title_screen_info );
void title_screen_confirm (game_state *state, title_screen *title_screen_info);
///////////////////////////////////////////////////////////////////////////////////

///////////////////////////// Auxiliares /////////////////////////////////////////

// desenha texto
void title_screen_draw_text(title_screen *title_screen_info, ALLEGRO_FONT *font, int X_SCREEN, int Y_SCREEN);

// libera memoria
void exit_title_screen(game_state *state, title_screen *title_screen_info, ALLEGRO_BITMAP *title_screen_image);

#endif