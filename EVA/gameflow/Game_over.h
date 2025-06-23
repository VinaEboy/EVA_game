#ifndef __GAME_OVER__
#define __GAME_OVER__

// Tela de game over

#include "Game_state.h"
#include "Assets.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

// informações do menu de game over
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

//inicializa o menu
void start_game_over (game_state *state, game_over **game_over_info, ALLEGRO_BITMAP **game_over_image, ALLEGRO_AUDIO_STREAM **current_music);

// mostra o menu
void show_game_over (ALLEGRO_EVENT *event, game_state *state, ALLEGRO_FONT *font, ALLEGRO_DISPLAY *disp, game_assets *assets, int X_SCREEN, int Y_SCREEN);

///////////////////// FUNÇÕES DE INTERAÇÕES NO MENU ////////////////////////

//mover para baixo no menu
void game_over_down_move(game_over *game_over_info);

//mover para cima no menu
void game_over_up_move(game_over *game_over_info);

//clicando em pressionar no menu
void game_over_confirm(game_state *state,game_over *game_over_info);

////////////////////////////////////////////////////////////////////////////////

// Função auxiliar para desenhar o texto no menu
void game_over_draw_text(game_over *game_over_info, ALLEGRO_FONT *font, int X_SCREEN, int Y_SCREEN);

// Sai da etapa do jogo, liberando memória alocada
void exit_game_over(game_state *state,game_over *game_over_info, ALLEGRO_BITMAP *game_over_image);

#endif