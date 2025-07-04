#include "Game_over.h"

#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro5.h>																																												
#include <allegro5/allegro_font.h>																																											
#include <allegro5/allegro_primitives.h>	
#include <allegro5/allegro_ttf.h>
#include <string.h>

//informações necessárias para a tela inicial rodar
game_over *game_over_info_create() {
    game_over *game_over_info = (game_over *) malloc(sizeof(game_over));
    if (!game_over_info) {
        fprintf(stderr, "Falha ao criar infomarções da game_over\n");
        exit(1);
    }

    game_over_info->Load_game_selected = 1;
    game_over_info->Load_game_color = al_map_rgb(184, 134, 11);
    game_over_info->Options_selected = 0;
    game_over_info->Options_color = al_map_rgb(255, 255, 255);
    game_over_info->Return_to_stage_select_selected = 0;
    game_over_info->Return_to_stage_select_color = al_map_rgb(255, 255, 255);
    game_over_info->Back_to_title_screen_selected = 0;
    game_over_info->Back_to_title_screen_color = al_map_rgb(255, 255, 255);
    game_over_info->game_over_exit = 0;

    return game_over_info;
}

//inicializa o menu
void start_game_over (game_state *state, game_over **game_over_info, ALLEGRO_BITMAP **game_over_image, ALLEGRO_AUDIO_STREAM **current_music) {
    if (*current_music) {
        al_set_audio_stream_playing(*current_music, false);
        al_destroy_audio_stream(*current_music);
    }
    *current_music = al_load_audio_stream("sounds/Game_over_theme.ogg", 4, 2048); // (arquivo, buffer count, buffer size)
    al_attach_audio_stream_to_mixer(*current_music, al_get_default_mixer());
    al_set_audio_stream_playmode(*current_music, ALLEGRO_PLAYMODE_LOOP);
    al_set_audio_stream_gain(*current_music, state->sound_volume); // configura o volume do jogo

    
    *game_over_image = al_load_bitmap("images/backscreen/game_over_screen.png");
    if (!*game_over_image) {
        fprintf(stderr, "Falha ao carregar imagem do game_over\n");
        exit(1);
    }
    *game_over_info = game_over_info_create();
    if (!*game_over_info) {
        fprintf(stderr, "Falha ao criar informações do game_over \n");
        exit(1);
    }

    state->game_over_started = 1;
}

// mostra o menu
void show_game_over (ALLEGRO_EVENT *event, game_state *state, ALLEGRO_FONT *font, ALLEGRO_DISPLAY *disp, game_assets *assets, int X_SCREEN, int Y_SCREEN) {

    ALLEGRO_BITMAP *game_over_image = assets->game_over_image;
    game_over *game_over_info = assets->game_over_info;

    al_clear_to_color(al_map_rgb(0, 0, 0));

    int img_width = al_get_bitmap_width(game_over_image);
    int img_height = al_get_bitmap_height(game_over_image);


    // desenha a imagem escalada para preencher a tela inteira
    al_draw_scaled_bitmap(game_over_image,0, 0,img_width, img_height,0, 0,X_SCREEN, Y_SCREEN,0);

    if (event->type == ALLEGRO_EVENT_KEY_DOWN) {
        if (event->keyboard.keycode == state->controls->DOWN)
            game_over_down_move(game_over_info);
        if (event->keyboard.keycode == state->controls->UP)
            game_over_up_move(game_over_info);
        if (event->keyboard.keycode == state->controls->CONFIRM)
            game_over_confirm(state,game_over_info);
    }

    game_over_draw_text(game_over_info, font, X_SCREEN, Y_SCREEN);

    al_flip_display();

    if (game_over_info->game_over_exit) 
        exit_game_over(state, game_over_info,game_over_image);
    
}

///////////////////// FUNÇÕES DE INTERAÇÕES NO MENU ////////////////////////

//mover para baixo no menu
void game_over_down_move(game_over *game_over_info) {
    if (game_over_info->Load_game_selected) {
        game_over_info->Load_game_selected = 0;
        game_over_info->Load_game_color = al_map_rgb(255, 255, 255);
        game_over_info->Options_selected = 1;
        game_over_info->Options_color = al_map_rgb(184, 134, 11);
    } else if (game_over_info->Options_selected) {
        game_over_info->Options_selected = 0;
        game_over_info->Options_color = al_map_rgb(255, 255, 255);
        game_over_info->Return_to_stage_select_selected = 1;
        game_over_info->Return_to_stage_select_color = al_map_rgb(184, 134, 11);
    } else if (game_over_info->Return_to_stage_select_selected) {
        game_over_info->Return_to_stage_select_selected = 0;
        game_over_info->Return_to_stage_select_color = al_map_rgb(255, 255, 255);
        game_over_info->Back_to_title_screen_selected = 1;
        game_over_info->Back_to_title_screen_color = al_map_rgb(184, 134, 11);
    }
}

//mover para cima no menu
void game_over_up_move(game_over *game_over_info) {
    if (game_over_info->Back_to_title_screen_selected) {
        game_over_info->Back_to_title_screen_selected = 0;
        game_over_info->Back_to_title_screen_color = al_map_rgb(255, 255, 255);
        game_over_info->Return_to_stage_select_selected = 1;
        game_over_info->Return_to_stage_select_color = al_map_rgb(184, 134, 11);
    } else if (game_over_info->Return_to_stage_select_selected) {
        game_over_info->Return_to_stage_select_selected = 0;
        game_over_info->Return_to_stage_select_color = al_map_rgb(255, 255, 255);
        game_over_info->Options_selected = 1;
        game_over_info->Options_color = al_map_rgb(184, 134, 11);
    } else if (game_over_info->Options_selected) {
        game_over_info->Options_selected = 0;
        game_over_info->Options_color = al_map_rgb(255, 255, 255);
        game_over_info->Load_game_selected = 1;
        game_over_info->Load_game_color = al_map_rgb(184, 134, 11);
    }
}

//clicando em pressionar no menu
void game_over_confirm(game_state *state,game_over *game_over_info) {
    state->checkpoint = 0;
    state->player_progress->Lifes = 3; //reseta as vidas
    if (game_over_info->Load_game_selected) {
        state->load_game = 1;
    } else if (game_over_info->Options_selected) {
        state->options = 1;
    } else if (game_over_info->Return_to_stage_select_selected) {
        state->level_select = 1;
        game_over_info->game_over_exit = 1;
    } else if (game_over_info->Back_to_title_screen_selected) {
        state->title_screen = 1;
        game_over_info->game_over_exit = 1;
    }
}
/////////////////////////////////////////////////////////////////////////

// Função auxiliar para desenhar o texto no menu
void game_over_draw_text(game_over *game_over_info, ALLEGRO_FONT *font, int X_SCREEN, int Y_SCREEN) {

    long int coord_X = X_SCREEN/2;
    long int coord_Y = Y_SCREEN*0.2;
    long int espaçamento = Y_SCREEN/13;

    al_draw_text(font, game_over_info->Load_game_color,coord_X, coord_Y, ALLEGRO_ALIGN_CENTER, "LOAD GAME");

    al_draw_text(font, game_over_info->Options_color, coord_X, coord_Y + espaçamento, ALLEGRO_ALIGN_CENTER, "OPTIONS");

    al_draw_text(font, game_over_info->Return_to_stage_select_color, coord_X, coord_Y + 2*espaçamento, ALLEGRO_ALIGN_CENTER, "RETURN TO LEVEL SELECT");

    al_draw_text(font, game_over_info->Back_to_title_screen_color, coord_X, coord_Y + 3*espaçamento, ALLEGRO_ALIGN_CENTER, "BACK TO TITLE SCREEN");

}

// Sai da etapa do jogo, liberando memória alocada
void exit_game_over(game_state *state,game_over *game_over_info, ALLEGRO_BITMAP *game_over_image) {
    state->game_over_started = 0;
    state->game_over = 0;
    free(game_over_info);
    al_destroy_bitmap(game_over_image);
}
