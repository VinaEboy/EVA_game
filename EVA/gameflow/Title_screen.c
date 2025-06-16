#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro5.h>																																												
#include <allegro5/allegro_font.h>																																											
#include <allegro5/allegro_primitives.h>			

#include "Title_screen.h"
#include "Game_state.h"

//informações necessárias para a tela inicial rodar
title_screen *title_screen_info_create() {
    title_screen *title_screen_info = (title_screen *) malloc(sizeof(title_screen));
    if (!title_screen_info) {
        fprintf(stderr, "Falha ao criar infomarções da tela principal\n");
        exit(1);
    }

    title_screen_info->new_game_selected = 1;
    title_screen_info->new_game_color = al_map_rgb(184, 134, 11);

    title_screen_info->load_game_selected = 0;
    title_screen_info->load_game_color = al_map_rgb(255, 255, 255);

    title_screen_info->options_selected = 0;
    title_screen_info->options_color = al_map_rgb(255, 255, 255);     

    title_screen_info->exit_selected = 0;
    title_screen_info->exit_color = al_map_rgb(255, 255, 255);  
    
    title_screen_info->title_screen_exit = 0;

    return title_screen_info;
}

//carrega imagem e inicializa valores necessários para a tela inicial rodar
void start_title_screen(game_state *state, title_screen **title_screen_info, ALLEGRO_BITMAP **title_screen_image ) {
    *title_screen_image = al_load_bitmap("images/backscreen/title_screen.png");
    if (!*title_screen_image) {
        fprintf(stderr, "Falha ao carregar imagem da tela principal\n");
        exit(1);
    }
    *title_screen_info = title_screen_info_create();
    if (!*title_screen_info) {
        fprintf(stderr, "Falha ao criar informações da tela principal \n");
        exit(1);
    }

    state->title_screen_started = 1;
}

//loop em que vai ficar mostrando a tela inicial e o jogador vai interagir com as opções do menu
void show_title_screen(ALLEGRO_EVENT *event, game_state *state, ALLEGRO_FONT *font, ALLEGRO_DISPLAY *disp, ALLEGRO_BITMAP *title_screen_image, 
                        title_screen *title_screen_info, int X_SCREEN, int Y_SCREEN) {
    
    al_clear_to_color(al_map_rgb(0, 0, 0));

    int img_width = al_get_bitmap_width(title_screen_image);
    int img_height = al_get_bitmap_height(title_screen_image);


    // desenha a imagem escalada para preencher a tela inteira
    al_draw_scaled_bitmap(title_screen_image,0, 0,img_width, img_height,0, 0,X_SCREEN, Y_SCREEN,0);

    if (event->type == ALLEGRO_EVENT_KEY_DOWN) {
        if (event->keyboard.keycode == state->controls->DOWN)
            title_screen_down_move(title_screen_info);
        if (event->keyboard.keycode == state->controls->UP)
            title_screen_up_move(title_screen_info);
        if (event->keyboard.keycode == state->controls->CONFIRM)
            title_screen_confirm(state,title_screen_info);
    }

    title_screen_draw_text(title_screen_info, font, X_SCREEN, Y_SCREEN);

    al_flip_display();

    if (title_screen_info->title_screen_exit) exit_title_screen(state, title_screen_info,title_screen_image);
}


///////////////////////////////////// Funções auxiliares de Title Screnn /////////////////////////////////////////////////////////////////////////


void title_screen_down_move (title_screen *title_screen_info ) {
    if(title_screen_info->new_game_selected) {
        title_screen_info->new_game_selected = 0;
        title_screen_info->new_game_color = al_map_rgb(255, 255, 255);
        title_screen_info->load_game_selected = 1;
        title_screen_info->load_game_color = al_map_rgb(184, 134, 11);
    } else if (title_screen_info->load_game_selected) {
        title_screen_info->load_game_selected = 0;
        title_screen_info->load_game_color = al_map_rgb(255, 255, 255);
        title_screen_info->options_selected = 1;
        title_screen_info->options_color = al_map_rgb(184, 134, 11);        
    } else if (title_screen_info->options_selected) {
        title_screen_info->options_selected = 0;
        title_screen_info->options_color = al_map_rgb(255, 255, 255);
        title_screen_info->exit_selected = 1;
        title_screen_info->exit_color = al_map_rgb(184, 134, 11);  
    }
}

void title_screen_up_move(title_screen *title_screen_info ) {
    if(title_screen_info->exit_selected ) {
        title_screen_info->exit_selected  = 0;
        title_screen_info->exit_color = al_map_rgb(255, 255, 255);          
        title_screen_info->options_selected  = 1;
        title_screen_info->options_color = al_map_rgb(184, 134, 11);    
    } else if (title_screen_info->options_selected ) {
        title_screen_info->options_selected  = 0;
        title_screen_info->options_color = al_map_rgb(255, 255, 255);
        title_screen_info->load_game_selected = 1;
        title_screen_info->load_game_color = al_map_rgb(184, 134, 11);
    } else if (title_screen_info->load_game_selected) {
        title_screen_info->load_game_selected = 0;
        title_screen_info->load_game_color = al_map_rgb(255, 255, 255);
        title_screen_info->new_game_selected  = 1;
        title_screen_info->new_game_color = al_map_rgb(184, 134, 11);
    }
}

void title_screen_confirm(game_state *state, title_screen *title_screen_info) {
    if (title_screen_info->exit_selected) {
        state->running = 0;
        title_screen_info->title_screen_exit = 1;
    }
    else if(title_screen_info->options_selected) {
        //não dá exit porque opções é como se fosse um pause da fase
        state->options = 1;
    }
    else if(title_screen_info->load_game_selected) {
        state->load_game = 1;
        title_screen_info->title_screen_exit = 1;
    }
    
    else if(title_screen_info->new_game_selected) {
        state->level_select = 1;
        title_screen_info->title_screen_exit = 1;
    }
}


void title_screen_draw_text(title_screen *title_screen_info, ALLEGRO_FONT *font, int X_SCREEN, int Y_SCREEN) {

    long int coord_X = X_SCREEN/4;
    long int coord_Y = Y_SCREEN/2;
    long int espaçamento = Y_SCREEN/10;

    al_draw_text(font, title_screen_info->new_game_color,coord_X, coord_Y, ALLEGRO_ALIGN_CENTER, "START NEW GAME");

    al_draw_text(font, title_screen_info->load_game_color, coord_X, coord_Y + espaçamento, ALLEGRO_ALIGN_CENTER, "LOAD GAME");

    al_draw_text(font, title_screen_info->options_color, coord_X, coord_Y + 2*espaçamento, ALLEGRO_ALIGN_CENTER, "OPTIONS");

    al_draw_text(font, title_screen_info->exit_color, coord_X, coord_Y + 3*espaçamento, ALLEGRO_ALIGN_CENTER, "EXIT");

}


void exit_title_screen(game_state *state, title_screen *title_screen_info, ALLEGRO_BITMAP *title_screen_image) {
    state->title_screen = 0;
    state->title_screen_started = 0;
    free(title_screen_info);
    al_destroy_bitmap(title_screen_image);
}
