#include "Load_game.h"

#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro5.h>																																												
#include <allegro5/allegro_font.h>																																											
#include <allegro5/allegro_primitives.h>	
#include "Game_state.h"
#include "Title_screen.h" //para a função exit
#include "Game_over.h" //para a função exit

load_game *load_game_info_create( ) {
    load_game *load_game_info = (load_game *) malloc(sizeof(load_game));
    if (!load_game_info) return NULL;

    load_game_info->slot_1_selected = 1; 
    load_game_info->choose_slot_1_selected = 0; 
    load_game_info->slot_2_selected = 0; 
    load_game_info->choose_slot_2_selected = 0; 
    load_game_info->slot_3_selected = 0; 
    load_game_info->choose_slot_3_selected = 0; 
    load_game_info->return_selected = 1;
    load_game_info->load_game_exit = 0;
    load_game_info->choose_slot_1_color = al_map_rgb(255,255,255);
    load_game_info->choose_slot_2_color = al_map_rgb(255,255,255);
    load_game_info->choose_slot_3_color = al_map_rgb(255,255,255);
    load_game_info->timer = 0;
    load_game_info->game_loaded = 0;

    FILE *arquivo = NULL;
    arquivo = fopen("save_data/slot_1.sav","rb");
    if (arquivo) {
        load_game_info->player_progress_slot_1 = malloc(sizeof(player_data));
        load_game_info->controls_slot_1 = malloc(sizeof(buttom_map));

        fread(load_game_info->player_progress_slot_1, sizeof(player_data), 1, arquivo);
        fread(load_game_info->controls_slot_1, sizeof(buttom_map),1,arquivo);
        fclose(arquivo);
    } else {
        load_game_info->player_progress_slot_1 = NULL;
        load_game_info->controls_slot_1 = NULL;
    }


    arquivo = fopen("save_data/slot_2.sav","rb");
    if (arquivo) {
        load_game_info->player_progress_slot_2 = malloc(sizeof(player_data));
        load_game_info->controls_slot_2 = malloc(sizeof(buttom_map));

        fread(load_game_info->player_progress_slot_2, sizeof(player_data), 1, arquivo);
        fread(load_game_info->controls_slot_2, sizeof(buttom_map),1,arquivo);
        fclose(arquivo);
    } else {
        load_game_info->player_progress_slot_2 = NULL;
        load_game_info->controls_slot_2 = NULL;
    }


    arquivo = fopen("save_data/slot_3.sav","rb");
    if (arquivo) {
        load_game_info->player_progress_slot_3 = malloc(sizeof(player_data));
        load_game_info->controls_slot_3 = malloc(sizeof(buttom_map));

        fread(load_game_info->player_progress_slot_3, sizeof(player_data), 1, arquivo);
        fread(load_game_info->controls_slot_3, sizeof(buttom_map),1,arquivo);
        fclose(arquivo);
    } else {
        load_game_info->player_progress_slot_3 = NULL;
        load_game_info->controls_slot_3 = NULL;
    }

    return load_game_info;
}

void start_load_game (game_state *state, load_game **load_game_info, ALLEGRO_BITMAP **load_game_image, ALLEGRO_BITMAP **default_slot_image) {
    *load_game_image = al_load_bitmap("images/backscreen/save_or_load_screen.png");
    if (!*load_game_image) {
        fprintf(stderr, "Falha ao carregar imagem da tela de salvar jogo \n");
        exit(1);
    }
    *default_slot_image = al_load_bitmap("images/backscreen/default_slot.png");
    if (!*default_slot_image) {
        fprintf(stderr, "Falha ao carregar imagem da tela de salvar jogo \n");
        exit(1);
    }    
    *load_game_info = load_game_info_create();
    if (!*load_game_info) {
        fprintf(stderr, "Falha ao criar informações da tela de salvar jogo \n");
        exit(1);
    }

    state->load_game_started = 1;
}

void show_load_game (ALLEGRO_EVENT *event, game_state *state, ALLEGRO_FONT *font, ALLEGRO_DISPLAY *disp, game_assets *assets, int X_SCREEN, int Y_SCREEN)  {
    
    ALLEGRO_BITMAP *load_game_image = assets->load_game_image;
    ALLEGRO_BITMAP *default_slot_image = assets->default_slot_image;
    load_game *load_game_info = assets->load_game_info;

    al_clear_to_color(al_map_rgb(0, 0, 0));


    int img_width = al_get_bitmap_width(load_game_image);
    int img_height = al_get_bitmap_height(load_game_image);

    // desenha a imagem escalada para preencher a tela inteira
    al_draw_scaled_bitmap(load_game_image,0, 0,img_width, img_height,0, 0,X_SCREEN, Y_SCREEN,0);

    if (event->type == ALLEGRO_EVENT_TIMER) load_game_info->timer++;

    if (event->type == ALLEGRO_EVENT_KEY_DOWN) {
        load_game_info->timer = 0; // para resetar o tempo que pisca
        if (event->keyboard.keycode == state->controls->DOWN)
            load_game_down_move(load_game_info);
        if (event->keyboard.keycode == state->controls->UP)
            load_game_up_move(load_game_info);
        if (event->keyboard.keycode == state->controls->LEFT)
            load_game_left_move(load_game_info);
        if (event->keyboard.keycode == state->controls->RIGHT)
            load_game_right_move(load_game_info);
        if (event->keyboard.keycode == state->controls->CONFIRM)
            load_game_confirm(state,load_game_info,load_game_image);
    }

    load_game_draw_text(default_slot_image, load_game_info, font, X_SCREEN, Y_SCREEN);

    al_flip_display();

    if (load_game_info->load_game_exit) exit_load_game(state,assets);

}

////////////////////////////////////////////////////////////////////////////////////////////////////////
// AUX
//////////////////////////

void load_game_down_move (load_game *load_game_info ) {
    if (load_game_info->choose_slot_1_selected) {
        load_game_info->choose_slot_1_selected = 0;
        load_game_info->choose_slot_1_color = al_map_rgb(255,255,255);
        load_game_info->slot_1_selected = 1;
    } else if (load_game_info->choose_slot_2_selected) {
        load_game_info->choose_slot_2_selected = 0;
        load_game_info->choose_slot_2_color = al_map_rgb(255,255,255);
        load_game_info->slot_2_selected = 1;
    } else if (load_game_info->choose_slot_3_selected) {
        load_game_info->choose_slot_3_selected = 0;
        load_game_info->choose_slot_3_color = al_map_rgb(255,255,255);
        load_game_info->slot_3_selected = 1;
    } 
    //não reseta o slot selecionado pq precisa lembrar dessa info para retornar depois
    else if (load_game_info->slot_1_selected || load_game_info->slot_2_selected || load_game_info->slot_3_selected) {
        load_game_info->return_selected = 1;
    } 
}

void load_game_up_move(load_game *load_game_info ) {
    if (load_game_info->slot_1_selected && !load_game_info->return_selected) {
        load_game_info->slot_1_selected = 0;
        load_game_info->choose_slot_1_selected = 1;
        load_game_info->choose_slot_1_color = al_map_rgb(184, 134, 11);
    } else if (load_game_info->slot_2_selected && !load_game_info->return_selected) {
        load_game_info->slot_2_selected = 0;
        load_game_info->choose_slot_2_selected = 1;
        load_game_info->choose_slot_2_color = al_map_rgb(184, 134, 11);
    } else if (load_game_info->slot_3_selected && !load_game_info->return_selected) {
        load_game_info->slot_3_selected = 0;
        load_game_info->choose_slot_3_selected = 1;
        load_game_info->choose_slot_3_color = al_map_rgb(184, 134, 11);
    } else if (load_game_info->return_selected) {
        load_game_info->return_selected = 0;
    }
}

void load_game_left_move(load_game *load_game_info ) {
    if (load_game_info->choose_slot_1_selected) {
        load_game_info->choose_slot_1_selected = 0;
        load_game_info->choose_slot_1_color = al_map_rgb(255,255,255);
        load_game_info->choose_slot_3_selected = 1;
        load_game_info->choose_slot_3_color = al_map_rgb(184, 134, 11);
    } else if (load_game_info->choose_slot_2_selected) {
        load_game_info->choose_slot_2_selected = 0;
        load_game_info->choose_slot_2_color = al_map_rgb(255,255,255);
        load_game_info->choose_slot_1_selected = 1;
        load_game_info->choose_slot_1_color = al_map_rgb(184, 134, 11);
    } else if (load_game_info->choose_slot_3_selected) {
        load_game_info->choose_slot_3_selected = 0;
        load_game_info->choose_slot_3_color = al_map_rgb(255,255,255);
        load_game_info->choose_slot_2_selected = 1;
        load_game_info->choose_slot_2_color = al_map_rgb(184, 134, 11);
    }
}

void load_game_right_move(load_game *load_game_info ) {
    if (load_game_info->choose_slot_1_selected) {
        load_game_info->choose_slot_1_selected = 0;
        load_game_info->choose_slot_1_color = al_map_rgb(255,255,255);
        load_game_info->choose_slot_2_selected = 1;
        load_game_info->choose_slot_2_color = al_map_rgb(184, 134, 11);
    } else if (load_game_info->choose_slot_2_selected) {
        load_game_info->choose_slot_2_selected = 0;
        load_game_info->choose_slot_2_color = al_map_rgb(255,255,255);
        load_game_info->choose_slot_3_selected = 1;
        load_game_info->choose_slot_3_color = al_map_rgb(184, 134, 11);
    } else if (load_game_info->choose_slot_3_selected) {
        load_game_info->choose_slot_3_selected = 0;
        load_game_info->choose_slot_3_color = al_map_rgb(255,255,255);
        load_game_info->choose_slot_1_selected = 1;
        load_game_info->choose_slot_1_color = al_map_rgb(184, 134, 11);
    }
}

void load_game_confirm(game_state *state, load_game *load_game_info, ALLEGRO_BITMAP *load_game_image) {
    if (load_game_info->slot_1_selected && !load_game_info->return_selected) {
        load_game_slot(state,load_game_info, 1);
    } else if (load_game_info->slot_2_selected && !load_game_info->return_selected) {
        load_game_slot(state, load_game_info, 2);
    } else if (load_game_info->slot_3_selected && !load_game_info->return_selected) {
        load_game_slot(state,load_game_info, 3);
    } else if (load_game_info->return_selected) {
        load_game_info->load_game_exit = 1;
    }
}


// Lê 2 structs do arquivo: player_progress e controls
// Como essas structs não apontam para outras structs, a implementação é simples
void load_game_slot(game_state *state, load_game *load_game_info, int slot) {
    if (slot == 1) {
        if (!load_game_info->player_progress_slot_1 || !load_game_info->controls_slot_1) return;

        free(state->player_progress); 
        state->player_progress = malloc(sizeof(player_data));
        if (state->player_progress) 
            memcpy(state->player_progress, load_game_info->player_progress_slot_1, sizeof(player_data));

        free(state->controls); 
        state->controls = malloc(sizeof(buttom_map));
        if (state->controls) 
            memcpy(state->controls, load_game_info->controls_slot_1, sizeof(buttom_map));
        
    } else if (slot == 2) {
        if (!load_game_info->player_progress_slot_2 || !load_game_info->controls_slot_2) return;

        free(state->player_progress); 
        state->player_progress = malloc(sizeof(player_data));
        if (state->player_progress) 
            memcpy(state->player_progress, load_game_info->player_progress_slot_2, sizeof(player_data));
    
        free(state->controls); 
        state->controls = malloc(sizeof(buttom_map));
        if (state->controls) 
            memcpy(state->controls, load_game_info->controls_slot_2, sizeof(buttom_map));

    } else if (slot == 3) {
        if (!load_game_info->player_progress_slot_3 || !load_game_info->controls_slot_3) return;

        free(state->player_progress); 
        state->player_progress = malloc(sizeof(player_data));
        if (state->player_progress) 
            memcpy(state->player_progress, load_game_info->player_progress_slot_3, sizeof(player_data));
    
        free(state->controls); 
        state->controls = malloc(sizeof(buttom_map));
        if (state->controls) 
            memcpy(state->controls, load_game_info->controls_slot_3, sizeof(buttom_map));
    
    }

    state->player_progress->start_time = al_get_time(); //agora o tempo que vc começou a jogar é esse
    
    load_game_info->game_loaded = 1;
    state->level_select = 1;
    load_game_info->load_game_exit = 1;
}



void load_game_draw_text(ALLEGRO_BITMAP *default_slot_image, load_game *load_game_info, ALLEGRO_FONT *font, int X_SCREEN, int Y_SCREEN) {
    int default_slot_width = al_get_bitmap_width(default_slot_image);
    int default_slot_height = al_get_bitmap_height(default_slot_image);
    

    if (load_game_info->return_selected) 
        al_draw_text(font,al_map_rgb(184, 134, 11), X_SCREEN/2, Y_SCREEN*0.55, ALLEGRO_ALIGN_CENTER, "Return");
    else 
        al_draw_text(font,al_map_rgb(255, 255, 255), X_SCREEN/2, Y_SCREEN*0.55, ALLEGRO_ALIGN_CENTER, "Return");    

    if (load_game_info->slot_1_selected || load_game_info->choose_slot_1_selected) {
        al_draw_text(font,load_game_info->choose_slot_1_color, X_SCREEN/2, Y_SCREEN/20, ALLEGRO_ALIGN_CENTER, "<- SLOT 1 ->");
        
        if (load_game_info->choose_slot_1_selected) 
            if (load_game_info->timer > 20)
                        al_draw_text(font,al_map_rgb(0,0,0), X_SCREEN/2, Y_SCREEN/20, ALLEGRO_ALIGN_CENTER, "<- SLOT 1 ->");
        
        if (load_game_info->slot_1_selected && !load_game_info->return_selected && load_game_info->timer < 20) 
            al_draw_rectangle(X_SCREEN/4, Y_SCREEN/2, X_SCREEN*0.75, Y_SCREEN/6, al_map_rgb(184, 134, 11), 8);
            
        
        if (load_game_info->player_progress_slot_1) {
            al_draw_scaled_bitmap(default_slot_image,0, 0,default_slot_width,default_slot_height, X_SCREEN/4, Y_SCREEN/6, X_SCREEN/2, Y_SCREEN/3, 0);    
            al_draw_text(font,al_map_rgb(255,255,255), X_SCREEN*0.4, Y_SCREEN*0.25, ALLEGRO_ALIGN_CENTER, get_progress_string(load_game_info->player_progress_slot_1));
            al_draw_text(font,al_map_rgb(255,255,255), X_SCREEN*0.4, Y_SCREEN*0.35, ALLEGRO_ALIGN_CENTER, get_time_string(load_game_info->player_progress_slot_1));
        }
        else {
            al_draw_filled_rectangle(X_SCREEN/4, Y_SCREEN/2, X_SCREEN*0.75, Y_SCREEN/6, al_map_rgb(36, 36, 36));
            al_draw_text(font, al_map_rgb(255,255,255),X_SCREEN/2, Y_SCREEN/3, ALLEGRO_ALIGN_CENTER, "EMPTY");
        }
    }

    if (load_game_info->slot_2_selected || load_game_info->choose_slot_2_selected) {
        al_draw_text(font,load_game_info->choose_slot_2_color, X_SCREEN/2, Y_SCREEN/20, ALLEGRO_ALIGN_CENTER, "<- SLOT 2 ->");

        if (load_game_info->choose_slot_2_selected && load_game_info->timer > 20) 
            al_draw_text(font,al_map_rgb(0,0,0), X_SCREEN/2, Y_SCREEN/20, ALLEGRO_ALIGN_CENTER, "<- SLOT 2 ->");
        
        if (load_game_info->slot_2_selected && !load_game_info->return_selected && load_game_info->timer < 20)
            al_draw_rectangle(X_SCREEN/4, Y_SCREEN/2, X_SCREEN*0.75, Y_SCREEN/6, al_map_rgb(184, 134, 11), 8);
    

        if (load_game_info->player_progress_slot_2) {
            al_draw_scaled_bitmap(default_slot_image,0, 0,default_slot_width,default_slot_height, X_SCREEN/4, Y_SCREEN/6, X_SCREEN/2, Y_SCREEN/3, 0);   
            al_draw_text(font,al_map_rgb(255,255,255), X_SCREEN*0.4, Y_SCREEN*0.25, ALLEGRO_ALIGN_CENTER, get_progress_string(load_game_info->player_progress_slot_2));
            al_draw_text(font,al_map_rgb(255,255,255), X_SCREEN*0.4, Y_SCREEN*0.35, ALLEGRO_ALIGN_CENTER, get_time_string(load_game_info->player_progress_slot_2)); 
        }
        else {
            al_draw_filled_rectangle(X_SCREEN/4, Y_SCREEN/2, X_SCREEN*0.75, Y_SCREEN/6, al_map_rgb(36, 36, 36));
            al_draw_text(font, al_map_rgb(255,255,255),X_SCREEN/2, Y_SCREEN/3, ALLEGRO_ALIGN_CENTER, "EMPTY");
        }  
    }

    if (load_game_info->slot_3_selected || load_game_info->choose_slot_3_selected) {
        al_draw_text(font,load_game_info->choose_slot_3_color, X_SCREEN/2, Y_SCREEN/20, ALLEGRO_ALIGN_CENTER, "<- SLOT 3 ->");

        if (load_game_info->choose_slot_3_selected && load_game_info->timer > 20) 
            al_draw_text(font,al_map_rgb(0,0,0), X_SCREEN/2, Y_SCREEN/20, ALLEGRO_ALIGN_CENTER, "<- SLOT 3 ->");
        
        if (load_game_info->slot_3_selected && !load_game_info->return_selected && load_game_info->timer < 20)
            al_draw_rectangle(X_SCREEN/4, Y_SCREEN/2, X_SCREEN*0.75, Y_SCREEN/6, al_map_rgb(184, 134, 11), 8);
    

        if (load_game_info->player_progress_slot_3) {
            al_draw_scaled_bitmap(default_slot_image,0, 0,default_slot_width,default_slot_height, X_SCREEN/4, Y_SCREEN/6, X_SCREEN/2, Y_SCREEN/3, 0);    
            al_draw_text(font,al_map_rgb(255,255,255), X_SCREEN*0.4, Y_SCREEN*0.25, ALLEGRO_ALIGN_CENTER, get_progress_string(load_game_info->player_progress_slot_3));
            al_draw_text(font,al_map_rgb(255,255,255), X_SCREEN*0.4, Y_SCREEN*0.35, ALLEGRO_ALIGN_CENTER, get_time_string(load_game_info->player_progress_slot_3));    
        }
        else {
            al_draw_filled_rectangle(X_SCREEN/4, Y_SCREEN/2, X_SCREEN*0.75, Y_SCREEN/6, al_map_rgb(36, 36, 36));
            al_draw_text(font, al_map_rgb(255,255,255),X_SCREEN/2, Y_SCREEN/3, ALLEGRO_ALIGN_CENTER, "EMPTY");
        }
    }


    if (load_game_info->timer == 30)
        load_game_info->timer = 0;
} 


void exit_load_game(game_state *state, game_assets *assets) {
    
    load_game *load_game_info = assets->load_game_info;
    ALLEGRO_BITMAP *default_slot_image = assets->default_slot_image;
    ALLEGRO_BITMAP *load_game_image = assets->load_game_image;

    //se um jogo foi carregado tem que liberar a etapa que estava antes do load (porque o load não conta como sair de uma etapa)
    if (assets->load_game_info->game_loaded) {
        if (state->title_screen) exit_title_screen(state, assets->title_screen_info, assets->title_screen_image );
        else if (state->game_over) exit_game_over(state,assets->game_over_info, assets->game_over_image);
    }
    
    state->load_game = 0;
    state->load_game_started = 0;
    al_destroy_bitmap(load_game_image);
    al_destroy_bitmap(default_slot_image);
    free(load_game_info->player_progress_slot_1);
    free(load_game_info->player_progress_slot_2);
    free(load_game_info->player_progress_slot_3);
    free(load_game_info->controls_slot_1);
    free(load_game_info->controls_slot_2);
    free(load_game_info->controls_slot_3);
    free(load_game_info);
}



///////////////////////// AUXILIARES PARA PEGAR STRINGS PARA ESCREVER /////////////////

const char* get_progress_string(struct player_data *progress) {
    static char progress_buffer[30];


    int completed_count = 0;
    if (progress->Level_1_completed) completed_count++;
    if (progress->Level_2_completed) completed_count++;
    if (progress->Level_3_completed) completed_count++;
    if (progress->Level_4_completed) completed_count++;
    if (progress->Level_5_completed) completed_count++;
    if (progress->Level_6_completed) completed_count++;
    if (progress->Level_7_completed) completed_count++;
    if (progress->Level_8_completed) completed_count++;
    
    const int total_levels = 8;

    snprintf(progress_buffer, sizeof(progress_buffer), "Progress: %d/%d", completed_count, total_levels);

    return progress_buffer;
}


const char* get_time_string(struct player_data *progress) {

    static char time_buffer[30];

    double total_seconds = progress->total_play_time;

    int total_minutes = (int)(total_seconds / 60);
    int hours = total_minutes / 60;
    int minutes = total_minutes % 60;
    
    snprintf(time_buffer, sizeof(time_buffer), "Playtime: %dh%02d", hours, minutes);

    return time_buffer;
}

