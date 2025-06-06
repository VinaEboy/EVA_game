#include "Load_game.h"

#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro5.h>																																												
#include <allegro5/allegro_font.h>																																											
#include <allegro5/allegro_primitives.h>	
#include "Game_state.h"

load_game *load_game_info_create( ) {
    load_game *load_game_info = (load_game *) malloc(sizeof(load_game));
    if (!load_game_info) return NULL;

    load_game_info->slot_1_selected = 1; 
    load_game_info->choose_slot_1_selected = 0; 
    load_game_info->slot_2_selected = 0; 
    load_game_info->choose_slot_2_selected = 0; 
    load_game_info->slot_3_selected = 0; 
    load_game_info->choose_slot_3_selected = 0; 
    load_game_info->return_to_title_screen_selected = 1;
    load_game_info->return_to_title_screen = 0;
    load_game_info->choose_slot_1_color = al_map_rgb(255,255,255);
    load_game_info->choose_slot_2_color = al_map_rgb(255,255,255);
    load_game_info->choose_slot_3_color = al_map_rgb(255,255,255);
    load_game_info->timer = 0;
    return load_game_info;
}

void start_load_game (game_state *state, load_game **load_game_info, ALLEGRO_BITMAP **load_game_image, ALLEGRO_BITMAP **default_slot_image) {
    *load_game_image = al_load_bitmap("images/save_or_load_screen.png");
    if (!*load_game_image) {
        fprintf(stderr, "Falha ao carregar imagem da tela de salvar jogo \n");
        exit(1);
    }
    *default_slot_image = al_load_bitmap("images/default_slot.png");
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

void show_load_game (ALLEGRO_EVENT *event, game_state *state, ALLEGRO_FONT *font, ALLEGRO_DISPLAY *disp, ALLEGRO_BITMAP *load_game_image, ALLEGRO_BITMAP *default_slot_image,
                        load_game *load_game_info, int X_SCREEN, int Y_SCREEN)  {
    
    al_clear_to_color(al_map_rgb(0, 0, 0));


    int img_width = al_get_bitmap_width(load_game_image);
    int img_height = al_get_bitmap_height(load_game_image);

    // desenha a imagem escalada para preencher a tela inteira
    al_draw_scaled_bitmap(load_game_image,0, 0,img_width, img_height,0, 0,X_SCREEN, Y_SCREEN,0);

    if (event->type == ALLEGRO_EVENT_KEY_UP) {
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

    if (load_game_info->return_to_title_screen) exit_load_game(state,load_game_info,load_game_image);

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
        load_game_info->return_to_title_screen_selected = 1;
    } 
}

void load_game_up_move(load_game *load_game_info ) {
    if (load_game_info->slot_1_selected && !load_game_info->return_to_title_screen_selected) {
        load_game_info->slot_1_selected = 0;
        load_game_info->choose_slot_1_selected = 1;
        load_game_info->choose_slot_1_color = al_map_rgb(184, 134, 11);
    } else if (load_game_info->slot_2_selected && !load_game_info->return_to_title_screen_selected) {
        load_game_info->slot_2_selected = 0;
        load_game_info->choose_slot_2_selected = 1;
        load_game_info->choose_slot_2_color = al_map_rgb(184, 134, 11);
    } else if (load_game_info->slot_3_selected && !load_game_info->return_to_title_screen_selected) {
        load_game_info->slot_3_selected = 0;
        load_game_info->choose_slot_3_selected = 1;
        load_game_info->choose_slot_3_color = al_map_rgb(184, 134, 11);
    } else if (load_game_info->return_to_title_screen_selected) {
        load_game_info->return_to_title_screen_selected = 0;
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
    if (load_game_info->slot_1_selected && !load_game_info->return_to_title_screen_selected) {
        load_game_slot(state,load_game_info, 1);
    } else if (load_game_info->slot_2_selected && !load_game_info->return_to_title_screen_selected) {
        load_game_slot(state, load_game_info, 2);
    } else if (load_game_info->slot_3_selected && !load_game_info->return_to_title_screen_selected) {
        load_game_slot(state,load_game_info, 3);
    } else if (load_game_info->return_to_title_screen_selected) {
        state->title_screen = 1;
        load_game_info->return_to_title_screen = 1;
    }
}


// Lê 2 structs do arquivo: player_progress e controls
// Como essas structs não apontam para outras structs, a implementação é simples
void load_game_slot(game_state *state, load_game *load_game_info, int slot) {
    FILE *arquivo;

    if (slot == 1) 
        arquivo = fopen("save_data/slot_1.sav", "rb");
    else if (slot == 2) 
        arquivo = fopen("save_data/slot_2.sav", "rb");
    else
        arquivo = fopen("save_data/slot_3.sav", "rb");

    //erro na leitura, arquivo vazio, não faz nada
    if (!arquivo) return;
    

    fread(state->player_progress, sizeof(player_data), 1, arquivo);
    fread(state->controls, sizeof(buttom_map), 1, arquivo);
    state->level_select = 1;
    load_game_info->return_to_title_screen = 1; //é uma flag de que vai sair, nesse caso vai para level select porque fez load

    fclose(arquivo);
}



void load_game_draw_text(ALLEGRO_BITMAP *default_slot_image, load_game *load_game_info, ALLEGRO_FONT *font, int X_SCREEN, int Y_SCREEN) {

    FILE *arquivo;

    int default_slot_width = al_get_bitmap_width(default_slot_image);
    int default_slot_height = al_get_bitmap_height(default_slot_image);
    
    load_game_info->timer++;

    if (load_game_info->return_to_title_screen_selected) {
        al_draw_text(font,al_map_rgb(184, 134, 11), X_SCREEN/2, Y_SCREEN*0.55, ALLEGRO_ALIGN_CENTER, "Return to");
        al_draw_text(font,al_map_rgb(184, 134, 11), X_SCREEN/2, Y_SCREEN*0.6, ALLEGRO_ALIGN_CENTER, "Title Screen");
    } else {
        al_draw_text(font,al_map_rgb(255, 255, 255), X_SCREEN/2, Y_SCREEN*0.55, ALLEGRO_ALIGN_CENTER, "Return to");
        al_draw_text(font,al_map_rgb(255, 255, 255), X_SCREEN/2, Y_SCREEN*0.6, ALLEGRO_ALIGN_CENTER, "Title Screen");        
    }

    if (load_game_info->slot_1_selected || load_game_info->choose_slot_1_selected) {
        al_draw_text(font,load_game_info->choose_slot_1_color, X_SCREEN/2, Y_SCREEN/20, ALLEGRO_ALIGN_CENTER, "<- SLOT 1 ->");
        
        if (load_game_info->choose_slot_1_selected) 
            if (load_game_info->timer > 20)
                        al_draw_text(font,al_map_rgb(0,0,0), X_SCREEN/2, Y_SCREEN/20, ALLEGRO_ALIGN_CENTER, "<- SLOT 1 ->");
        
        if (load_game_info->slot_1_selected && !load_game_info->return_to_title_screen_selected && load_game_info->timer < 20) 
            al_draw_rectangle(X_SCREEN/4, Y_SCREEN/2, X_SCREEN*0.75, Y_SCREEN/6, al_map_rgb(184, 134, 11), 8);
            
        
        arquivo = fopen("save_data/slot_1.sav","rb");
        if (arquivo) {
            al_draw_scaled_bitmap(default_slot_image,0, 0,default_slot_width,default_slot_height, X_SCREEN/4, Y_SCREEN/6, X_SCREEN/2, Y_SCREEN/3, 0);    
            fclose(arquivo); 
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
        
        if (load_game_info->slot_2_selected && !load_game_info->return_to_title_screen_selected && load_game_info->timer < 20)
            al_draw_rectangle(X_SCREEN/4, Y_SCREEN/2, X_SCREEN*0.75, Y_SCREEN/6, al_map_rgb(184, 134, 11), 8);
    

        arquivo = fopen("save_data/slot_2.sav","rb");
        if (arquivo) {
            al_draw_scaled_bitmap(default_slot_image,0, 0,default_slot_width,default_slot_height, X_SCREEN/4, Y_SCREEN/6, X_SCREEN/2, Y_SCREEN/3, 0);    
            fclose(arquivo);
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
        
        if (load_game_info->slot_3_selected && !load_game_info->return_to_title_screen_selected && load_game_info->timer < 20)
            al_draw_rectangle(X_SCREEN/4, Y_SCREEN/2, X_SCREEN*0.75, Y_SCREEN/6, al_map_rgb(184, 134, 11), 8);
    

        arquivo = fopen("save_data/slot_3.sav","rb");
        if (arquivo) {
            al_draw_scaled_bitmap(default_slot_image,0, 0,default_slot_width,default_slot_height, X_SCREEN/4, Y_SCREEN/6, X_SCREEN/2, Y_SCREEN/3, 0);    
            fclose(arquivo);
        }
        else {
            al_draw_filled_rectangle(X_SCREEN/4, Y_SCREEN/2, X_SCREEN*0.75, Y_SCREEN/6, al_map_rgb(36, 36, 36));
            al_draw_text(font, al_map_rgb(255,255,255),X_SCREEN/2, Y_SCREEN/3, ALLEGRO_ALIGN_CENTER, "EMPTY");
        }
    }


    if (load_game_info->timer == 30)
        load_game_info->timer = 0;
} 

void exit_load_game(game_state *state, load_game *load_game_info,ALLEGRO_BITMAP *load_game_image) {
    state->load_game = 0;
    state->load_game_started = 0;
    al_destroy_bitmap(load_game_image);
    free(load_game_info);
}
