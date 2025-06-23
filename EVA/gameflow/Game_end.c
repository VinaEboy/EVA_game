#include "Game_end.h"

#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro5.h>																																												
#include <allegro5/allegro_font.h>																																											
#include <allegro5/allegro_primitives.h>	
#include <allegro5/allegro_ttf.h>
#include <string.h>

//cria o default do game_end_info
game_end *game_end_info_create() {
    game_end *game_end_info = (game_end *) malloc(sizeof(game_end));
    if (!game_end_info) {
        fprintf(stderr, "Falha ao criar infomarções da game_end\n");
        exit(1);
    }

    game_end_info->Return_to_stage_select_selected = 1;
    game_end_info->Return_to_stage_select_color = al_map_rgb(184, 134, 11);
    game_end_info->Back_to_title_screen_selected = 0;
    game_end_info->Back_to_title_screen_color = al_map_rgb(255, 255, 255);
    game_end_info->game_end_exit = 0;

    return game_end_info;
}

// carrega as imagens e cria struct info
void start_game_end (game_state *state, game_end **game_end_info, ALLEGRO_BITMAP **game_end_image, ALLEGRO_AUDIO_STREAM **current_music) {
    if (*current_music) {
        al_set_audio_stream_playing(*current_music, false);
        al_destroy_audio_stream(*current_music);
    }
    *current_music = al_load_audio_stream("sounds/Game_end_theme.ogg", 4, 2048); // (arquivo, buffer count, buffer size)
    al_attach_audio_stream_to_mixer(*current_music, al_get_default_mixer());
    al_set_audio_stream_playmode(*current_music, ALLEGRO_PLAYMODE_LOOP);
    al_set_audio_stream_gain(*current_music, state->sound_volume); // configura o volume do jogo
    

    *game_end_image = al_load_bitmap("images/backscreen/game_end_screen.png");
    if (!*game_end_image) {
        fprintf(stderr, "Falha ao carregar imagem do game_end\n");
        exit(1);
    }
    *game_end_info = game_end_info_create();
    if (!*game_end_info) {
        fprintf(stderr, "Falha ao criar informações do game_end \n");
        exit(1);
    }

    state->game_end_started = 1;
}

//mostra no display a imagem assim como escreve texto
void show_game_end (ALLEGRO_EVENT *event, game_state *state, ALLEGRO_FONT *font, ALLEGRO_DISPLAY *disp, game_assets *assets, int X_SCREEN, int Y_SCREEN) {

    ALLEGRO_BITMAP *game_end_image = assets->game_end_image;
    game_end *game_end_info = assets->game_end_info;

    al_clear_to_color(al_map_rgb(0, 0, 0));

    int img_width = al_get_bitmap_width(game_end_image);
    int img_height = al_get_bitmap_height(game_end_image);


    // desenha a imagem escalada para preencher a tela inteira
    al_draw_scaled_bitmap(game_end_image,0, 0,img_width, img_height,0, 0,X_SCREEN, Y_SCREEN,0);

    if (event->type == ALLEGRO_EVENT_KEY_DOWN) {
        if (event->keyboard.keycode == state->controls->DOWN)
            game_end_down_move(game_end_info);
        if (event->keyboard.keycode == state->controls->UP)
            game_end_up_move(game_end_info);
        if (event->keyboard.keycode == state->controls->CONFIRM)
            game_end_confirm(state,game_end_info);
    }

    game_end_draw_text(game_end_info, font, X_SCREEN, Y_SCREEN);

    al_flip_display();

    if (game_end_info->game_end_exit) 
        exit_game_end(state, game_end_info,game_end_image);
    
}

///////////////////// FUNÇÕES DE INTERAÇÕES NO MENU ////////////////////////

//mover para baixo no menu
void game_end_down_move(game_end *game_end_info) {
    if (game_end_info->Return_to_stage_select_selected) {
        game_end_info->Return_to_stage_select_selected = 0;
        game_end_info->Return_to_stage_select_color = al_map_rgb(255, 255, 255);
        game_end_info->Back_to_title_screen_selected = 1;
        game_end_info->Back_to_title_screen_color = al_map_rgb(184, 134, 11);
    }
}

//mover para cima no menu
void game_end_up_move(game_end *game_end_info) {
    if (game_end_info->Back_to_title_screen_selected) {
        game_end_info->Back_to_title_screen_selected = 0;
        game_end_info->Back_to_title_screen_color = al_map_rgb(255, 255, 255);
        game_end_info->Return_to_stage_select_selected = 1;
        game_end_info->Return_to_stage_select_color = al_map_rgb(184, 134, 11);
    }
}

//clicando em pressionar no menu
void game_end_confirm(game_state *state,game_end *game_end_info) {
    state->checkpoint = 0; //reseta os checkpoints
    if (game_end_info->Return_to_stage_select_selected) {
        state->level_select = 1;
        game_end_info->game_end_exit = 1;
    } else if (game_end_info->Back_to_title_screen_selected) {
        state->title_screen = 1;
        game_end_info->game_end_exit = 1;
    } 
}
/////////////////////////////////////////////////////////////

// Função auxiliar para desenhar o texto no menu
void game_end_draw_text(game_end *game_end_info, ALLEGRO_FONT *font, int X_SCREEN, int Y_SCREEN) {

    long int coord_X = X_SCREEN/2;
    long int coord_Y = Y_SCREEN*0.25;
    long int espaçamento = Y_SCREEN*0.1;

    al_draw_text(font, al_map_rgb(135, 206, 235), X_SCREEN/2, Y_SCREEN*0.05, ALLEGRO_ALIGN_CENTER, "OMEDETOU");
    al_draw_text(font, al_map_rgb(135, 206, 235), X_SCREEN/2, Y_SCREEN*0.1, ALLEGRO_ALIGN_CENTER, "CONGRATULATIONS");
     al_draw_text(font, al_map_rgb(135, 206, 235), X_SCREEN/2, Y_SCREEN*0.15, ALLEGRO_ALIGN_CENTER, "PARABAINS");   

    al_draw_text(font, game_end_info->Return_to_stage_select_color,coord_X, coord_Y, ALLEGRO_ALIGN_CENTER, "RETURN TO STAGE SELECT");

    al_draw_text(font, game_end_info->Back_to_title_screen_color, coord_X, coord_Y + espaçamento, ALLEGRO_ALIGN_CENTER, "BACK TO TITLE SCREEN");

}

// Sai da etapa do jogo, liberando memória alocada
void exit_game_end(game_state *state,game_end *game_end_info, ALLEGRO_BITMAP *game_end_image) {
    state->game_end_started = 0;
    state->game_end = 0;
    free(game_end_info);
    al_destroy_bitmap(game_end_image);
}
