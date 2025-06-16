#include "Pause.h"

#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro5.h>																																												
#include <allegro5/allegro_font.h>																																											
#include <allegro5/allegro_primitives.h>	
#include <allegro5/allegro_ttf.h>
#include <string.h>
#include "../levels/Level_1.h" //por causa do "exit level"

//informações necessárias para a tela inicial rodar
pause_game *pause_info_create() {
    pause_game *pause_info = (pause_game *) malloc(sizeof(pause_game));
    if (!pause_info) {
        fprintf(stderr, "Falha ao criar infomarções da pause\n");
        exit(1);
    }

    pause_info->Return_to_mission_selected = 1;
    pause_info->Return_to_mission_color = al_map_rgb(184, 134, 11);
    pause_info->Options_selected = 0;
    pause_info->Options_color = al_map_rgb(255, 255, 255);
    pause_info->Return_to_stage_select_selected = 0;
    pause_info->Return_to_stage_select_color = al_map_rgb(255, 255, 255);
    pause_info->Back_to_title_screen_selected = 0;
    pause_info->Back_to_title_screen_color = al_map_rgb(255, 255, 255);
    pause_info->pause_exit = 0;

    return pause_info;
}

void start_pause (game_state *state, pause_game **pause_info, ALLEGRO_BITMAP **pause_image) {
    *pause_image = al_load_bitmap("images/backscreen/pause_screen.png");
    if (!*pause_image) {
        fprintf(stderr, "Falha ao carregar imagem do pause\n");
        exit(1);
    }
    *pause_info = pause_info_create();
    if (!*pause_info) {
        fprintf(stderr, "Falha ao criar informações do pause \n");
        exit(1);
    }

    state->pause_started = 1;
}


void show_pause (ALLEGRO_EVENT *event, game_state *state, ALLEGRO_FONT *font, ALLEGRO_DISPLAY *disp, game_assets *assets, int X_SCREEN, int Y_SCREEN) {

    ALLEGRO_BITMAP *pause_image = assets->pause_image;
    pause_game *pause_info = assets->pause_info;

    al_clear_to_color(al_map_rgb(0, 0, 0));

    int img_width = al_get_bitmap_width(pause_image);
    int img_height = al_get_bitmap_height(pause_image);


    // desenha a imagem escalada para preencher a tela inteira
    al_draw_scaled_bitmap(pause_image,0, 0,img_width, img_height,0, 0,X_SCREEN, Y_SCREEN,0);

    if (event->type == ALLEGRO_EVENT_KEY_DOWN) {
        if (event->keyboard.keycode == state->controls->DOWN)
            pause_down_move(pause_info);
        if (event->keyboard.keycode == state->controls->UP)
            pause_up_move(pause_info);
        if (event->keyboard.keycode == state->controls->CONFIRM)
            pause_confirm(state,pause_info);
        if (event->keyboard.keycode == state->controls->PAUSE) {
            pause_info->Return_to_mission_selected = 1;
            pause_info->pause_exit = 1;
        }
    }

    pause_draw_text(pause_info, font, X_SCREEN, Y_SCREEN);

    al_flip_display();

    if (pause_info->pause_exit) {
        if (!pause_info->Return_to_mission_selected) //significa que estou saindo do pause e da fase por isso tenho que descarregar a fase
            exit_level(state, assets);
        exit_pause(state, pause_info,pause_image);
    }
}

///////////////////////////////////// Funções auxiliares de Pause /////////////////////////////////////////////////////////////////////////


void pause_down_move(pause_game *pause_info) {
    if (pause_info->Return_to_mission_selected) {
        pause_info->Return_to_mission_selected = 0;
        pause_info->Return_to_mission_color = al_map_rgb(255, 255, 255);
        pause_info->Options_selected = 1;
        pause_info->Options_color = al_map_rgb(184, 134, 11);
    } else if (pause_info->Options_selected) {
        pause_info->Options_selected = 0;
        pause_info->Options_color = al_map_rgb(255, 255, 255);
        pause_info->Return_to_stage_select_selected = 1;
        pause_info->Return_to_stage_select_color = al_map_rgb(184, 134, 11);
    } else if (pause_info->Return_to_stage_select_selected) {
        pause_info->Return_to_stage_select_selected = 0;
        pause_info->Return_to_stage_select_color = al_map_rgb(255, 255, 255);
        pause_info->Back_to_title_screen_selected = 1;
        pause_info->Back_to_title_screen_color = al_map_rgb(184, 134, 11);
    }
}

void pause_up_move(pause_game *pause_info) {
    if (pause_info->Back_to_title_screen_selected) {
        pause_info->Back_to_title_screen_selected = 0;
        pause_info->Back_to_title_screen_color = al_map_rgb(255, 255, 255);
        pause_info->Return_to_stage_select_selected = 1;
        pause_info->Return_to_stage_select_color = al_map_rgb(184, 134, 11);
    } else if (pause_info->Return_to_stage_select_selected) {
        pause_info->Return_to_stage_select_selected = 0;
        pause_info->Return_to_stage_select_color = al_map_rgb(255, 255, 255);
        pause_info->Options_selected = 1;
        pause_info->Options_color = al_map_rgb(184, 134, 11);
    } else if (pause_info->Options_selected) {
        pause_info->Options_selected = 0;
        pause_info->Options_color = al_map_rgb(255, 255, 255);
        pause_info->Return_to_mission_selected = 1;
        pause_info->Return_to_mission_color = al_map_rgb(184, 134, 11);
    }
}

void pause_confirm(game_state *state,pause_game *pause_info) {
    if (pause_info->Return_to_mission_selected) {
        pause_info->pause_exit = 1;
    } else if (pause_info->Options_selected) {
        state->options = 1;
    } else if (pause_info->Return_to_stage_select_selected) {
        state->level_select = 1;
        pause_info->pause_exit = 1;
    } else if (pause_info->Back_to_title_screen_selected) {
        state->title_screen = 1;
        pause_info->pause_exit = 1;
    }
}


void pause_draw_text(pause_game *pause_info, ALLEGRO_FONT *font, int X_SCREEN, int Y_SCREEN) {

    long int coord_X = X_SCREEN/3;
    long int coord_Y = Y_SCREEN/4;
    long int espaçamento = Y_SCREEN/10;

    al_draw_text(font, pause_info->Return_to_mission_color,coord_X, coord_Y, ALLEGRO_ALIGN_CENTER, "RETURN TO MISSION");

    al_draw_text(font, pause_info->Options_color, coord_X, coord_Y + espaçamento, ALLEGRO_ALIGN_CENTER, "OPTIONS");

    al_draw_text(font, pause_info->Return_to_stage_select_color, coord_X, coord_Y + 2*espaçamento, ALLEGRO_ALIGN_CENTER, "RETURN TO LEVEL SELECT");

    al_draw_text(font, pause_info->Back_to_title_screen_color, coord_X, coord_Y + 3*espaçamento, ALLEGRO_ALIGN_CENTER, "BACK TO TITLE SCREEN");

}


//Tem que pensar em como eu vou descarregar a primeira fase também
void exit_pause(game_state *state,pause_game *pause_info, ALLEGRO_BITMAP *pause_image) {
    state->pause_started = 0;
    state->pause = 0;
    free(pause_info);
    al_destroy_bitmap(pause_image);
}

//tem que "lembrar" qual level que estava
void exit_level(game_state *state, game_assets *assets) {
    if (state->level_1)
        exit_level_1(state, assets->level_1_info, assets->sprites);
}