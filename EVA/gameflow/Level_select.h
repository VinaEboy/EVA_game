#ifndef __LEVEL_SELECT__
#define __LEVEL_SELECT__


// Menu de seleção de fases

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>		
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <stdlib.h>
#include <stdio.h>
#include "Game_state.h"

typedef struct game_state game_state;

// informações do menu de seleção de fase
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
    unsigned char level_select_exit;
    unsigned char warning_return_title_screen; //aviso que está voltando para tela principal e pode perder progresso
    unsigned char return_yes;
    unsigned char return_no;
    int timer;
} level_select;

//cria a informação inicial
level_select *level_select_info_create();

// inicializa
void start_level_select(game_state *state, level_select **level_select_info, ALLEGRO_BITMAP **level_select_image, ALLEGRO_AUDIO_STREAM **current_music );

// mostra na tela
void show_level_select(ALLEGRO_EVENT *event, game_state *state, ALLEGRO_FONT *font, ALLEGRO_DISPLAY *disp, ALLEGRO_BITMAP *level_select_image, 
                        level_select *level_select_info, int X_SCREEN, int Y_SCREEN, ALLEGRO_AUDIO_STREAM **current_music);

///////////////////// FUNÇÕES DE INTERAÇÕES NO MENU ////////////////////////

// mover para esquerda
void level_select_left_move(level_select *level_select_info);

// mover para direita
void title_screen_right_move(level_select *level_select_info);

//mover para baixo
void level_select_down_move(level_select*level_select_info);

//mover para cima
void level_select_up_move(level_select *level_select_info);

//apertar confimar (selecionar uma fase ou outra etapa)
void level_select_confirm(game_state *state,level_select *level_select_info,ALLEGRO_BITMAP *level_select_image);
////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////// AUXILIARES//////////////////////////////////

//aviso de retornar para tela principal
void warning_return_title_screen(game_state *state, level_select *level_select_info,ALLEGRO_FONT *font, int X_SCREEN, int Y_SCREEN);

// função que libera memória ao sair da etapa
void exit_level_select (game_state *state, level_select *level_select_info,ALLEGRO_BITMAP *level_select_image, ALLEGRO_AUDIO_STREAM **current_music );

// desenha o texto da etapa
void level_select_draw_text(ALLEGRO_FONT *font, level_select *level_select, int X_SCREEN, int Y_SCREEN) ;

//feedback visual de que a fase foi concluida, colocando um quadrado cinza em cima do chefão derroado
void draw_defeated_levels(game_state *state, int X_SCREEN, int Y_SCREEN) ;

#endif
