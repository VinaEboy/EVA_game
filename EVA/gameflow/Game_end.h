#ifndef __GAME_END__
#define __GAME_END__

//é a etapa em que o jogo foi concluido COM SUCESSO

#include "Game_state.h"
#include "Assets.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

//estrutura de informações do "menu"
typedef struct game_end {
    unsigned char Return_to_stage_select_selected;
    ALLEGRO_COLOR Return_to_stage_select_color;
    unsigned char Back_to_title_screen_selected;
    ALLEGRO_COLOR Back_to_title_screen_color;
    unsigned char game_end_exit;
} game_end;

// carrega as imagens e cria struct info
void start_game_end (game_state *state, game_end **game_end_info, ALLEGRO_BITMAP **game_end_image, ALLEGRO_AUDIO_STREAM **current_music);

//mostra no display a imagem assim como escreve texto
void show_game_end (ALLEGRO_EVENT *event, game_state *state, ALLEGRO_FONT *font, ALLEGRO_DISPLAY *disp, game_assets *assets, int X_SCREEN, int Y_SCREEN);

///////////////////// FUNÇÕES DE INTERAÇÕES NO MENU ////////////////////////

//mover para baixo no menu
void game_end_down_move(game_end *game_end_info);

//mover para cima no menu
void game_end_up_move(game_end *game_end_info);

//clicando em pressionar no menu
void game_end_confirm(game_state *state,game_end *game_end_info);
//////////////////////////////////////////////////////////////////////////////

// Função auxiliar para desenhar o texto no menu
void game_end_draw_text(game_end *game_end_info, ALLEGRO_FONT *font, int X_SCREEN, int Y_SCREEN);

// Sai da etapa do jogo, liberando memória alocada
void exit_game_end(game_state *state,game_end *game_end_info, ALLEGRO_BITMAP *game_end_image);

#endif