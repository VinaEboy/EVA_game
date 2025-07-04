#include "Level_select.h"
#include <allegro5/allegro_primitives.h>	
#include <allegro5/allegro5.h>																																												
#include <allegro5/allegro_font.h>	

//cria a informação inicial
level_select *level_select_info_create() {
    level_select *level_select_info = (level_select *) malloc (sizeof(level_select));
    if (!level_select_info) return NULL;

    level_select_info->Level_1_selected = 0;
    level_select_info->Level_2_selected = 0;
    level_select_info->Level_3_selected = 0;
    level_select_info->Level_4_selected = 0;
    level_select_info->Level_5_selected = 0;
    level_select_info->Level_6_selected = 0;
    level_select_info->Level_7_selected = 0;
    level_select_info->Level_8_selected = 0;
    level_select_info->Shinji_selected = 1;
    level_select_info->Back_title_screen_selected = 0;
    level_select_info->Back_title_screen_color = al_map_rgb(255, 255, 255);
    level_select_info->Save_game_selected = 0; 
    level_select_info->Save_game_color = al_map_rgb(255, 255, 255); 
    level_select_info->level_select_exit = 0;
    level_select_info->timer = 0;
    level_select_info->warning_return_title_screen = 0;
    level_select_info->return_yes = 0;
    level_select_info->return_no = 0;
    return level_select_info;
}   

// inicializa
void start_level_select(game_state *state, level_select **level_select_info, ALLEGRO_BITMAP **level_select_image, ALLEGRO_AUDIO_STREAM **current_music ) {
    if (*current_music) {
        al_set_audio_stream_playing(*current_music, false);
        al_destroy_audio_stream(*current_music);
    }
    *current_music = al_load_audio_stream("sounds/Level_select_theme.ogg", 4, 2048); // (arquivo, buffer count, buffer size)
    al_attach_audio_stream_to_mixer(*current_music, al_get_default_mixer());
    al_set_audio_stream_playmode(*current_music, ALLEGRO_PLAYMODE_LOOP);
    al_set_audio_stream_gain(*current_music, state->sound_volume); // configura o volume do jogo
    
    *level_select_image = al_load_bitmap("images/backscreen/level_select_screen.png");
    if (!*level_select_image) {
        fprintf(stderr, "Falha ao carregar imagem da seleção de fase\n");
        exit(1);
    }
    *level_select_info = level_select_info_create();
    if (!*level_select_info) {
        fprintf(stderr, "Falha ao criar informações da seleção de fase\n");
    }

    state->level_select_started = 1;
}

// mostra na tela
void show_level_select(ALLEGRO_EVENT *event, game_state *state, ALLEGRO_FONT *font, ALLEGRO_DISPLAY *disp, ALLEGRO_BITMAP *level_select_image, 
                        level_select *level_select_info, int X_SCREEN, int Y_SCREEN, ALLEGRO_AUDIO_STREAM **current_music) {
        
    al_clear_to_color(al_map_rgb(0, 0, 0));

    int img_width = al_get_bitmap_width(level_select_image);
    int img_height = al_get_bitmap_height(level_select_image);


    // desenha a imagem escalada para preencher a tela inteira
    al_draw_scaled_bitmap(level_select_image,0, 0,img_width, img_height,0, 0,X_SCREEN, Y_SCREEN,0);

    if (event->type == ALLEGRO_EVENT_TIMER) level_select_info->timer++;

    if (event->type == ALLEGRO_EVENT_KEY_DOWN) {
        level_select_info->timer = 0;
        if (event->keyboard.keycode == state->controls->LEFT)
            level_select_left_move(level_select_info);
        if (event->keyboard.keycode == state->controls->RIGHT)
            title_screen_right_move(level_select_info);
        if (event->keyboard.keycode == state->controls->DOWN)
            level_select_down_move(level_select_info);
        if (event->keyboard.keycode == state->controls->UP)
            level_select_up_move(level_select_info);
        if (event->keyboard.keycode == state->controls->CONFIRM)
            level_select_confirm(state,level_select_info,level_select_image);        
    }

    
    level_select_draw_text(font, level_select_info, X_SCREEN, Y_SCREEN);


    if(level_select_info->warning_return_title_screen) 
        warning_return_title_screen(state, level_select_info, font, X_SCREEN, Y_SCREEN);
    else
        draw_defeated_levels(state, X_SCREEN,Y_SCREEN);

    al_flip_display();
    
    if (level_select_info->level_select_exit) exit_level_select(state, level_select_info,level_select_image, current_music);
}

///////////////////// FUNÇÕES DE INTERAÇÕES NO MENU ////////////////////////


/* Level_select screen:

                  1        2         3
BACK              4      SHINJI      5        Save Game
                  6        7         8

*/

// mover para esquerda
void level_select_left_move(level_select *level_select_info) {

    if (level_select_info->Level_1_selected || level_select_info->Level_4_selected || level_select_info->Level_6_selected) {
        level_select_info->Level_1_selected = 0; //tudo bem se sobrescrever algum desses com 0
        level_select_info->Level_4_selected = 0;
        level_select_info->Level_6_selected = 0;
        level_select_info->Back_title_screen_selected = 1;
        level_select_info->Back_title_screen_color = al_map_rgb(184, 134, 11);
    } else if (level_select_info->Level_2_selected) {
        level_select_info->Level_2_selected = 0;
        level_select_info->Level_1_selected = 1; 
    } else if (level_select_info->Shinji_selected) {
        level_select_info->Shinji_selected = 0;
        level_select_info->Level_4_selected = 1;
    } else if (level_select_info->Level_7_selected) {
        level_select_info->Level_7_selected = 0;
        level_select_info->Level_6_selected = 1;
    } else if (level_select_info->Level_3_selected) {
        level_select_info->Level_3_selected = 0;
        level_select_info->Level_2_selected = 1;
    } else if (level_select_info->Level_5_selected) {
        level_select_info->Level_5_selected = 0;
        level_select_info->Shinji_selected = 1;
    } else if (level_select_info->Level_8_selected) {
        level_select_info->Level_8_selected = 0;
        level_select_info->Level_7_selected = 1;
    }
    else if (level_select_info->Save_game_selected) {
        level_select_info->Save_game_selected = 0;
        level_select_info->Save_game_color = al_map_rgb(255, 255, 255);
        level_select_info->Level_5_selected = 1;
    } else if (level_select_info->return_no) {
        level_select_info->return_no = 0;
        level_select_info->return_yes = 1;
    }
}

// mover para direita
void title_screen_right_move(level_select *level_select_info) {

    if (level_select_info->Level_3_selected || level_select_info->Level_5_selected || level_select_info->Level_8_selected) {
        level_select_info->Level_3_selected = 0; //tudo bem se sobrescrever algum desses com 0
        level_select_info->Level_5_selected = 0;
        level_select_info->Level_8_selected = 0;
        level_select_info->Save_game_selected = 1;
        level_select_info->Save_game_color = al_map_rgb(184, 134, 11);
    } else if (level_select_info->Level_2_selected) {
        level_select_info->Level_2_selected = 0;
        level_select_info->Level_3_selected = 1; 
    } else if (level_select_info->Shinji_selected) {
        level_select_info->Shinji_selected = 0;
        level_select_info->Level_5_selected = 1;
    } else if (level_select_info->Level_7_selected) {
        level_select_info->Level_7_selected = 0;
        level_select_info->Level_8_selected = 1;
    } else if (level_select_info->Level_1_selected) {
        level_select_info->Level_1_selected = 0;
        level_select_info->Level_2_selected = 1;
    } else if (level_select_info->Level_4_selected) {
        level_select_info->Level_4_selected = 0;
        level_select_info->Shinji_selected = 1;
    } else if (level_select_info->Level_6_selected) {
        level_select_info->Level_6_selected = 0;
        level_select_info->Level_7_selected = 1;
    } else if (level_select_info->Back_title_screen_selected) {
        level_select_info->Back_title_screen_selected = 0;
        level_select_info->Back_title_screen_color = al_map_rgb(255, 255, 255);
        level_select_info->Level_4_selected = 1;
    } else if (level_select_info->return_yes) {
        level_select_info->return_yes = 0;
        level_select_info->return_no = 1;
    }

}

//mover para baixo
void level_select_down_move(level_select *level_select_info) {

    if (level_select_info->Level_1_selected) {
        level_select_info->Level_1_selected = 0;
        level_select_info->Level_4_selected = 1;
    } else if (level_select_info->Level_2_selected) {
        level_select_info->Level_2_selected = 0;
        level_select_info->Shinji_selected = 1;
    } else if (level_select_info->Level_3_selected) {
        level_select_info->Level_3_selected = 0;
        level_select_info->Level_5_selected = 1;
    } else if (level_select_info->Level_4_selected) {
        level_select_info->Level_4_selected = 0;
        level_select_info->Level_6_selected = 1;
    } else if (level_select_info->Shinji_selected) {
        level_select_info->Shinji_selected = 0;
        level_select_info->Level_7_selected = 1;
    } else if (level_select_info->Level_5_selected) {
        level_select_info->Level_5_selected = 0;
        level_select_info->Level_8_selected = 1;
    }
}

//mover para cima
void level_select_up_move(level_select *level_select_info) {

    if (level_select_info->Level_4_selected) {
        level_select_info->Level_4_selected = 0;
        level_select_info->Level_1_selected = 1;
    } else if (level_select_info->Shinji_selected) {
        level_select_info->Shinji_selected = 0;
        level_select_info->Level_2_selected = 1;
    } else if (level_select_info->Level_5_selected) {
        level_select_info->Level_5_selected = 0;
        level_select_info->Level_3_selected = 1;
    } else if (level_select_info->Level_6_selected) {
        level_select_info->Level_6_selected = 0;
        level_select_info->Level_4_selected = 1;
    } else if (level_select_info->Level_7_selected) {
        level_select_info->Level_7_selected = 0;
        level_select_info->Shinji_selected = 1;
    } else if (level_select_info->Level_8_selected) {
        level_select_info->Level_8_selected = 0;
        level_select_info->Level_5_selected = 1;
    }
}

//apertar confimar (selecionar uma fase ou outra etapa)
void level_select_confirm(game_state *state,level_select *level_select_info,ALLEGRO_BITMAP *level_select_image) {
    
    if (level_select_info->Back_title_screen_selected) {
        level_select_info->warning_return_title_screen = 1;
        level_select_info->return_no = 1;
        level_select_info->Back_title_screen_selected = 0;
        return;
    }

    if (level_select_info->Save_game_selected) {
        state->save_game = 1;
        return;
    }

    if (level_select_info->Level_1_selected) {
        level_select_info->level_select_exit = 1;
        state->level_1 = 1;
        return;
    }

    if (level_select_info->Level_2_selected) {
        level_select_info->level_select_exit = 1;
        state->level_2 = 1;
        return;
    }

    if (level_select_info->Level_3_selected) {
        level_select_info->level_select_exit = 1;
        state->level_3 = 1;
        return;
    }

    if (level_select_info->Level_4_selected) {
        level_select_info->level_select_exit = 1;
        state->level_4 = 1;
        return;
    }

    if (level_select_info->Level_5_selected) {
        level_select_info->level_select_exit = 1;
        state->level_5 = 1;
        return;
    }

    if (level_select_info->Level_6_selected) {
        level_select_info->level_select_exit = 1;
        state->level_6 = 1;
        return;
    }

    if (level_select_info->Level_7_selected) {
        level_select_info->level_select_exit = 1;
        state->level_7 = 1;
        return;
    }

    if (level_select_info->Level_8_selected) {
        level_select_info->level_select_exit = 1;
        state->level_8 = 1;
        return;
    }

    if (level_select_info->return_no) {
        level_select_info->return_no = 0;
        level_select_info->warning_return_title_screen = 0;
        level_select_info->Back_title_screen_selected = 1;
        return;
    } 

    if (level_select_info->return_yes) {
        state->title_screen = 1;
        level_select_info->level_select_exit = 1;
    }

}

////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////// AUXILIARES//////////////////////////////////

//desenha o texto
void level_select_draw_text(ALLEGRO_FONT *font, level_select *level_select_info, int X_SCREEN, int Y_SCREEN) {
 
    al_draw_text(font, level_select_info->Save_game_color, 7*X_SCREEN/8, Y_SCREEN/2, ALLEGRO_ALIGN_CENTER, "Save Game");

    al_draw_text(font, level_select_info->Back_title_screen_color, X_SCREEN/8, Y_SCREEN/2 - Y_SCREEN/48, ALLEGRO_ALIGN_CENTER,"Return to");
    al_draw_text(font, level_select_info->Back_title_screen_color, X_SCREEN/8, Y_SCREEN/2 + Y_SCREEN/48, ALLEGRO_ALIGN_CENTER,"title screen");

    if (level_select_info->timer == 30) level_select_info->timer = 0;
    if(!level_select_info->Save_game_selected && !level_select_info->Back_title_screen_selected && level_select_info->timer < 20) {
        int center_x;
        int center_y;

        if (level_select_info->Level_1_selected || level_select_info->Level_2_selected || level_select_info->Level_3_selected)
            center_y = Y_SCREEN/7;
        else if (level_select_info->Level_4_selected || level_select_info->Shinji_selected || level_select_info->Level_5_selected) {
            center_y = Y_SCREEN/7 + Y_SCREEN/4;
        } else {
            center_y = Y_SCREEN/7 + Y_SCREEN/2;
        }

        if (level_select_info->Level_1_selected || level_select_info->Level_4_selected || level_select_info->Level_6_selected)
            center_x = X_SCREEN/2 - X_SCREEN/6;
        else if (level_select_info->Level_2_selected || level_select_info->Shinji_selected || level_select_info->Level_7_selected) {
            center_x = X_SCREEN/2;
        } else {
            center_x = X_SCREEN/2 + X_SCREEN/6;
        }

        al_draw_rectangle(center_x - X_SCREEN*0.05, center_y - Y_SCREEN*0.1,
        center_x + X_SCREEN*0.05, center_y + Y_SCREEN*0.1, al_map_rgb(184, 134, 11), 8);
    }

}

// libera memória ao sair da etapa
void exit_level_select (game_state *state, level_select *level_select_info,ALLEGRO_BITMAP *level_select_image,ALLEGRO_AUDIO_STREAM **current_music) {
    state->level_select = 0;
    state->level_select_started = 0;

    //destroi a música da fase de seleção para não ficar tocando em outros lugares
    if (*current_music) {
        al_set_audio_stream_playing(*current_music, false);
        al_detach_audio_stream(*current_music);
        al_destroy_audio_stream(*current_music);
        *current_music = NULL;
    }

    //significa que está voltando para tela principal, ou seja, a informação do player_progress reseta
    if (state->title_screen) {
        free(state->player_progress);
        state->player_progress = create_player_progress();
    }

    free(level_select_info);
    al_destroy_bitmap(level_select_image);
}

//aviso de que vai perder progresso ao retornar para tela principal
void warning_return_title_screen(game_state *state, level_select *level_select_info,ALLEGRO_FONT *font, int X_SCREEN, int Y_SCREEN) {

    al_clear_to_color(al_map_rgb(0, 0, 0));

    al_draw_text(font, al_map_rgb(255, 255, 255), X_SCREEN/2, 3*Y_SCREEN/8, ALLEGRO_ALIGN_CENTER,"Unsaved progress will be lost");

    al_draw_text(font, al_map_rgb(255, 255, 255), X_SCREEN/2, 3*Y_SCREEN/8 - Y_SCREEN/10, ALLEGRO_ALIGN_CENTER," Return to title screen?");

    if (level_select_info->return_yes) {
        al_draw_text(font, al_map_rgb(184, 134, 11), X_SCREEN/2 - X_SCREEN/8, 5*Y_SCREEN/8, ALLEGRO_ALIGN_CENTER,"Yes");
        al_draw_text(font, al_map_rgb(255, 255, 255), X_SCREEN/2 + X_SCREEN/8, 5*Y_SCREEN/8, ALLEGRO_ALIGN_CENTER,"No");
    } else {
        al_draw_text(font, al_map_rgb(255, 255, 255), X_SCREEN/2 - X_SCREEN/8, 5*Y_SCREEN/8, ALLEGRO_ALIGN_CENTER,"Yes");
        al_draw_text(font, al_map_rgb(184, 134, 11), X_SCREEN/2 + X_SCREEN/8, 5*Y_SCREEN/8, ALLEGRO_ALIGN_CENTER,"No");

    }
}

//feedback visual de que a fase foi concluida, colocando um quadrado cinza em cima do chefão derroado
void draw_defeated_levels(game_state *state, int X_SCREEN, int Y_SCREEN) {
    // cinza opaco para desenhar por cima dos chefes derrotados
    ALLEGRO_COLOR defeated_overlay_color = al_map_rgba(40, 40, 40, 153);

    // modo de mesclaagem
    al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_INVERSE_ALPHA);

    // dimensões do quadrado
    const float rect_half_width = X_SCREEN * 0.05f;
    const float rect_half_height = Y_SCREEN * 0.1f;
    
    // coordenadas dos quadrados.
    const float y_coords[] = { Y_SCREEN / 7.0f, Y_SCREEN / 7.0f + Y_SCREEN / 4.0f, Y_SCREEN / 7.0f + Y_SCREEN / 2.0f };
    const float x_coords[] = { X_SCREEN / 2.0f - X_SCREEN / 6.0f, X_SCREEN / 2.0f, X_SCREEN / 2.0f + X_SCREEN / 6.0f };


    if (state->player_progress->Level_1_completed) {
        float center_x = x_coords[0];
        float center_y = y_coords[0];
        al_draw_filled_rectangle(center_x - rect_half_width, center_y - rect_half_height, 
                                 center_x + rect_half_width, center_y + rect_half_height, 
                                 defeated_overlay_color);
    }
    
    if (state->player_progress->Level_2_completed) {
        float center_x = x_coords[1];
        float center_y = y_coords[0];
        al_draw_filled_rectangle(center_x - rect_half_width, center_y - rect_half_height, 
                                 center_x + rect_half_width, center_y + rect_half_height, 
                                 defeated_overlay_color);
    }


    if (state->player_progress->Level_3_completed) {
        float center_x = x_coords[2];
        float center_y = y_coords[0];
        al_draw_filled_rectangle(center_x - rect_half_width, center_y - rect_half_height, 
                                 center_x + rect_half_width, center_y + rect_half_height, 
                                 defeated_overlay_color);
    }

    if (state->player_progress->Level_4_completed) {
        float center_x = x_coords[0];
        float center_y = y_coords[1];
        al_draw_filled_rectangle(center_x - rect_half_width, center_y - rect_half_height, 
                                 center_x + rect_half_width, center_y + rect_half_height, 
                                 defeated_overlay_color);
    }

    if (state->player_progress->Level_5_completed) {
        float center_x = x_coords[2];
        float center_y = y_coords[1];
        al_draw_filled_rectangle(center_x - rect_half_width, center_y - rect_half_height, 
                                 center_x + rect_half_width, center_y + rect_half_height, 
                                 defeated_overlay_color);
    }

    if (state->player_progress->Level_6_completed) {
        float center_x = x_coords[0];
        float center_y = y_coords[2];
        al_draw_filled_rectangle(center_x - rect_half_width, center_y - rect_half_height, 
                                 center_x + rect_half_width, center_y + rect_half_height, 
                                 defeated_overlay_color);
    }

    if (state->player_progress->Level_7_completed) {
        float center_x = x_coords[1];
        float center_y = y_coords[2];
        al_draw_filled_rectangle(center_x - rect_half_width, center_y - rect_half_height, 
                                 center_x + rect_half_width, center_y + rect_half_height, 
                                 defeated_overlay_color);
    }

    if (state->player_progress->Level_8_completed) {
        float center_x = x_coords[2];
        float center_y = y_coords[2];
        al_draw_filled_rectangle(center_x - rect_half_width, center_y - rect_half_height, 
                                 center_x + rect_half_width, center_y + rect_half_height, 
                                 defeated_overlay_color);
    }
    
    // se não restaurar o blender padrão os outros desenhos podem ficar zoados
    al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_INVERSE_ALPHA);
}