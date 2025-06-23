#ifndef __OPTIONS__
#define __OPTIONS__

// menu de opções
#include "Assets.h"

//info do menu
typedef struct options {
    unsigned char SHOT_selected;
    ALLEGRO_COLOR SHOT_color;
    unsigned char JUMP_selected;
    ALLEGRO_COLOR JUMP_color;
    unsigned char LEFT_selected;
    ALLEGRO_COLOR LEFT_color;
    unsigned char RIGHT_selected;
    ALLEGRO_COLOR RIGHT_color;    
    unsigned char UP_selected;
    ALLEGRO_COLOR UP_color;    
    unsigned char DOWN_selected;
    ALLEGRO_COLOR DOWN_color;
    unsigned char CONFIRM_selected;
    ALLEGRO_COLOR CONFIRM_color;    
    unsigned char PAUSE_selected;
    ALLEGRO_COLOR PAUSE_color;       
    unsigned char DIFFICULTY_selected;
    ALLEGRO_COLOR DIFFICULTY_color;
    unsigned char BACK_selected;
    ALLEGRO_COLOR BACK_color;     
    unsigned char SOUND_selected;
    ALLEGRO_COLOR SOUND_color;
    unsigned char APPLY_selected; // botão para Aplicar mudanças, se estiver em um level ele reseta o level
    ALLEGRO_COLOR APPLY_color;
    unsigned char key_to_switch; // vai falar se está na etapa de trocar o valor de uma chave
    int timer;
} options;

// cria info
options *options_create();

// inicializa
void start_options (game_state *state,options **options_info);

//mostra na tela
void show_options( ALLEGRO_EVENT *event, game_state *state, ALLEGRO_FONT *font, ALLEGRO_DISPLAY *disp, game_assets *assets, int X_SCREEN, int Y_SCREEN );

/////////////////////// FUNÇÕES DE INTERAÇÕES NO MENU ////////////////////////

// para baixo
void options_down_move(options *options_info );

// para cima
void options_up_move(options *options_info );

// é o botão de confirmar
// o mais delicado é o APPLY que reinicia o estado que estava para aplicar mudanças
void options_key_select(game_state *state, game_assets *assets);

// é quando uma tecla está selecionada para mudar o mapeamento e está esperando
// a nova tecla que vai ser configurada. Não permite mudar para uma tecla que já está
// sendo usada ou que não está prevista no dicionário (exemplo: F7)
void options_key_switch(ALLEGRO_EVENT *event, game_state *state, options *options_info);

// para esquerda
void options_left_move(game_state *state, options *options_info);

// para direita
void options_right_move(game_state *state, options *options_info);

/////////////////////////////////////////////////////////////

//////////////////////////// Auxiliares /////////////////////

//desenha o texto
void options_draw_text (game_state *state, ALLEGRO_FONT *font, options *options_info, int X_SCREEN,int  Y_SCREEN);

// pisca o menu de opções (feedback visual de que está aguardando input)
void options_blind (game_state *state, ALLEGRO_FONT *font, options *options_info, int X_SCREEN, int Y_SCREEN, int margin_top, int margin_side, int padding_Y);

// é a função que usa o dicionário que está em game_state para traduzir o valor chave da tecla (do Allegro)
// para a string que descreve a tecla
const char *get_key_name(int keycode);

// função que recebe um float e formata para string, usado no ajustador de volume
const char* float_to_string(float value);
#endif