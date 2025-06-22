#ifndef __OPTIONS__
#define __OPTIONS__

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
    unsigned char key_to_switch; // vai falar se está na etapa de trocar o valor de uma chave
    int timer;
} options;


options *options_create();
void start_options (game_state *state,options **options_info);
void show_options( ALLEGRO_EVENT *event, game_state *state, ALLEGRO_FONT *font, ALLEGRO_DISPLAY *disp, options *options_info, int X_SCREEN, int Y_SCREEN );

// aux

void options_draw_text (game_state *state, ALLEGRO_FONT *font, options *options_info, int X_SCREEN,int  Y_SCREEN);
void options_blind (game_state *state, ALLEGRO_FONT *font, options *options_info, int X_SCREEN, int Y_SCREEN, int margin_top, int margin_side, int padding_Y);
void options_down_move(options *options_info );
void options_up_move(options *options_info );
void options_key_select(game_state *state, options *options_info);
void options_key_switch(ALLEGRO_EVENT *event, game_state *state, options *options_info);
void options_left_move(game_state *state, options *options_info);
void options_right_move(game_state *state, options *options_info);

#endif