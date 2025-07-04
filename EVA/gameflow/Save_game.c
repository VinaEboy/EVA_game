#include "Save_game.h"

#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro5.h>																																												
#include <allegro5/allegro_font.h>																																											
#include <allegro5/allegro_primitives.h>	
#include "Game_state.h"

// cria info
save_game *save_game_info_create( ) {
    save_game *save_game_info = (save_game *) malloc(sizeof(save_game));
    if (!save_game_info) return NULL;

    save_game_info->slot_1_selected = 1; 
    save_game_info->choose_slot_1_selected = 0; 
    save_game_info->slot_2_selected = 0; 
    save_game_info->choose_slot_2_selected = 0; 
    save_game_info->slot_3_selected = 0; 
    save_game_info->choose_slot_3_selected = 0; 
    save_game_info->return_to_stage_select_selected = 1;
    save_game_info->return_to_stage_select = 0;
    save_game_info->choose_slot_1_color = al_map_rgb(255,255,255);
    save_game_info->choose_slot_2_color = al_map_rgb(255,255,255);
    save_game_info->choose_slot_3_color = al_map_rgb(255,255,255);
    save_game_info->timer = 0;

    FILE *arquivo = NULL;
    arquivo = fopen("save_data/slot_1.sav","rb");
    if (arquivo) {
        save_game_info->player_progress_slot_1 = malloc(sizeof(player_data));
        fread(save_game_info->player_progress_slot_1, sizeof(player_data), 1, arquivo);
        fclose(arquivo);
    } else
        save_game_info->player_progress_slot_1 = NULL;


    arquivo = fopen("save_data/slot_2.sav","rb");
    if (arquivo) {
        save_game_info->player_progress_slot_2 = malloc(sizeof(player_data));
        fread(save_game_info->player_progress_slot_2, sizeof(player_data), 1, arquivo);
        fclose(arquivo);
    } else
        save_game_info->player_progress_slot_2 = NULL;


    arquivo = fopen("save_data/slot_3.sav","rb");
    if (arquivo) {
        save_game_info->player_progress_slot_3 = malloc(sizeof(player_data));
        fread(save_game_info->player_progress_slot_3, sizeof(player_data), 1, arquivo);
        fclose(arquivo);
    } else
        save_game_info->player_progress_slot_3 = NULL;


    return save_game_info;
}

// inicializa
void start_save_game (game_state *state, save_game **save_game_info, ALLEGRO_BITMAP **save_game_image, ALLEGRO_BITMAP **default_slot_image) {
    *save_game_image = al_load_bitmap("images/backscreen/save_or_load_screen.png");
    if (!*save_game_image) {
        fprintf(stderr, "Falha ao carregar imagem da tela de salvar jogo \n");
        exit(1);
    }
    *default_slot_image = al_load_bitmap("images/backscreen/default_slot.png");
    if (!*default_slot_image) {
        fprintf(stderr, "Falha ao carregar imagem da tela de salvar jogo \n");
        exit(1);
    }    
    *save_game_info = save_game_info_create();
    if (!*save_game_info) {
        fprintf(stderr, "Falha ao criar informações da tela de salvar jogo \n");
        exit(1);
    }

    state->save_game_started = 1;
}

// mostra na tela
void show_save_game (ALLEGRO_EVENT *event, game_state *state, ALLEGRO_FONT *font, ALLEGRO_DISPLAY *disp, ALLEGRO_BITMAP *save_game_image, ALLEGRO_BITMAP *default_slot_image,
                        save_game *save_game_info, int X_SCREEN, int Y_SCREEN)  {
    
    al_clear_to_color(al_map_rgb(0, 0, 0));


    int img_width = al_get_bitmap_width(save_game_image);
    int img_height = al_get_bitmap_height(save_game_image);

    // desenha a imagem escalada para preencher a tela inteira
    al_draw_scaled_bitmap(save_game_image,0, 0,img_width, img_height,0, 0,X_SCREEN, Y_SCREEN,0);

    if (event->type == ALLEGRO_EVENT_TIMER) save_game_info->timer++;

    if (event->type == ALLEGRO_EVENT_KEY_DOWN) {
        save_game_info->timer = 0; // para resetar o tempo que pisca
        if (event->keyboard.keycode == state->controls->DOWN)
            save_game_down_move(save_game_info);
        if (event->keyboard.keycode == state->controls->UP)
            save_game_up_move(save_game_info);
        if (event->keyboard.keycode == state->controls->LEFT)
            save_game_left_move(save_game_info);
        if (event->keyboard.keycode == state->controls->RIGHT)
            save_game_right_move(save_game_info);
        if (event->keyboard.keycode == state->controls->CONFIRM)
            save_game_confirm(state,save_game_info,save_game_image);
    }

    save_game_draw_text(default_slot_image, save_game_info, font, X_SCREEN, Y_SCREEN);

    al_flip_display();

    if (save_game_info->return_to_stage_select) exit_save_game(state,save_game_info,save_game_image);

}

/////////////////////// FUNÇÕES DE INTERAÇÕES NO MENU ////////////////////////

// para baixo
void save_game_down_move (save_game *save_game_info ) {
    if (save_game_info->choose_slot_1_selected) {
        save_game_info->choose_slot_1_selected = 0;
        save_game_info->choose_slot_1_color = al_map_rgb(255,255,255);
        save_game_info->slot_1_selected = 1;
    } else if (save_game_info->choose_slot_2_selected) {
        save_game_info->choose_slot_2_selected = 0;
        save_game_info->choose_slot_2_color = al_map_rgb(255,255,255);
        save_game_info->slot_2_selected = 1;
    } else if (save_game_info->choose_slot_3_selected) {
        save_game_info->choose_slot_3_selected = 0;
        save_game_info->choose_slot_3_color = al_map_rgb(255,255,255);
        save_game_info->slot_3_selected = 1;
    } 
    //não reseta o slot selecionado pq precisa lembrar dessa info para retornar depois
    else if (save_game_info->slot_1_selected || save_game_info->slot_2_selected || save_game_info->slot_3_selected) {
        save_game_info->return_to_stage_select_selected = 1;
    } 
}

// para cima
void save_game_up_move(save_game *save_game_info ) {
    if (save_game_info->slot_1_selected && !save_game_info->return_to_stage_select_selected) {
        save_game_info->slot_1_selected = 0;
        save_game_info->choose_slot_1_selected = 1;
        save_game_info->choose_slot_1_color = al_map_rgb(184, 134, 11);
    } else if (save_game_info->slot_2_selected && !save_game_info->return_to_stage_select_selected) {
        save_game_info->slot_2_selected = 0;
        save_game_info->choose_slot_2_selected = 1;
        save_game_info->choose_slot_2_color = al_map_rgb(184, 134, 11);
    } else if (save_game_info->slot_3_selected && !save_game_info->return_to_stage_select_selected) {
        save_game_info->slot_3_selected = 0;
        save_game_info->choose_slot_3_selected = 1;
        save_game_info->choose_slot_3_color = al_map_rgb(184, 134, 11);
    } else if (save_game_info->return_to_stage_select_selected) {
        save_game_info->return_to_stage_select_selected = 0;
    }
}

// para esquerda
void save_game_left_move(save_game *save_game_info ) {
    if (save_game_info->choose_slot_1_selected) {
        save_game_info->choose_slot_1_selected = 0;
        save_game_info->choose_slot_1_color = al_map_rgb(255,255,255);
        save_game_info->choose_slot_3_selected = 1;
        save_game_info->choose_slot_3_color = al_map_rgb(184, 134, 11);
    } else if (save_game_info->choose_slot_2_selected) {
        save_game_info->choose_slot_2_selected = 0;
        save_game_info->choose_slot_2_color = al_map_rgb(255,255,255);
        save_game_info->choose_slot_1_selected = 1;
        save_game_info->choose_slot_1_color = al_map_rgb(184, 134, 11);
    } else if (save_game_info->choose_slot_3_selected) {
        save_game_info->choose_slot_3_selected = 0;
        save_game_info->choose_slot_3_color = al_map_rgb(255,255,255);
        save_game_info->choose_slot_2_selected = 1;
        save_game_info->choose_slot_2_color = al_map_rgb(184, 134, 11);
    }
}

// para direita
void save_game_right_move(save_game *save_game_info ) {
    if (save_game_info->choose_slot_1_selected) {
        save_game_info->choose_slot_1_selected = 0;
        save_game_info->choose_slot_1_color = al_map_rgb(255,255,255);
        save_game_info->choose_slot_2_selected = 1;
        save_game_info->choose_slot_2_color = al_map_rgb(184, 134, 11);
    } else if (save_game_info->choose_slot_2_selected) {
        save_game_info->choose_slot_2_selected = 0;
        save_game_info->choose_slot_2_color = al_map_rgb(255,255,255);
        save_game_info->choose_slot_3_selected = 1;
        save_game_info->choose_slot_3_color = al_map_rgb(184, 134, 11);
    } else if (save_game_info->choose_slot_3_selected) {
        save_game_info->choose_slot_3_selected = 0;
        save_game_info->choose_slot_3_color = al_map_rgb(255,255,255);
        save_game_info->choose_slot_1_selected = 1;
        save_game_info->choose_slot_1_color = al_map_rgb(184, 134, 11);
    }
}

// confirmar
void save_game_confirm(game_state *state, save_game *save_game_info, ALLEGRO_BITMAP *save_game_image) {
    if (save_game_info->slot_1_selected && !save_game_info->return_to_stage_select_selected) {
        save_game_slot(state, save_game_info, 1);
    } else if (save_game_info->slot_2_selected && !save_game_info->return_to_stage_select_selected) {
        save_game_slot(state, save_game_info, 2);
    } else if (save_game_info->slot_3_selected && !save_game_info->return_to_stage_select_selected) {
        save_game_slot(state, save_game_info, 3);
    } else if (save_game_info->return_to_stage_select_selected) {
        save_game_info->return_to_stage_select = 1;
    }
}
///////////////////////////////////////////////////////////////////////////////////

///////////////////////////// Auxiliares /////////////////////////////////////////

// escreve o arquivo binário com o progresso e mapeamento de teclas do jogador, atualiza que aquele slot agora não tem info NULL
void save_game_slot(game_state *state, save_game *save_game_info, int slot) {
    FILE *arquivo;
    if (slot == 1) 
        arquivo = fopen("save_data/slot_1.sav","wb");
    else if (slot == 2) 
        arquivo = fopen("save_data/slot_2.sav","wb");
    else
        arquivo = fopen("save_data/slot_3.sav","wb");
    if (!arquivo) return ;

    state->player_progress->total_play_time += al_get_time() - state->player_progress->start_time;
    state->player_progress->start_time = al_get_time();

    fwrite(state->player_progress, sizeof(player_data), 1, arquivo);
    fwrite(state->controls, sizeof(buttom_map), 1, arquivo);

    // atualize a struct do slot na memória com uma cópia segura
    player_data **target_slot_ptr = NULL;
    if (slot == 1) target_slot_ptr = &save_game_info->player_progress_slot_1;
    else if (slot == 2) target_slot_ptr = &save_game_info->player_progress_slot_2;
    else target_slot_ptr = &save_game_info->player_progress_slot_3;

    // Libera os dados antigos do slot
    if (*target_slot_ptr) 
        free(*target_slot_ptr);
    
    // Aloca nova memória para o slot e copia os dados atuais do jogo para ele
    *target_slot_ptr = malloc(sizeof(player_data));
    if (*target_slot_ptr) 
        memcpy(*target_slot_ptr, state->player_progress, sizeof(player_data));
    
    fclose(arquivo);
}


// desenha o texto
void save_game_draw_text(ALLEGRO_BITMAP *default_slot_image, save_game *save_game_info, ALLEGRO_FONT *font, int X_SCREEN, int Y_SCREEN) {
    int default_slot_width = al_get_bitmap_width(default_slot_image);
    int default_slot_height = al_get_bitmap_height(default_slot_image);
    

    if (save_game_info->return_to_stage_select_selected) {
        al_draw_text(font,al_map_rgb(184, 134, 11), X_SCREEN/2, Y_SCREEN*0.55, ALLEGRO_ALIGN_CENTER, "Return to");
        al_draw_text(font,al_map_rgb(184, 134, 11), X_SCREEN/2, Y_SCREEN*0.6, ALLEGRO_ALIGN_CENTER, "Stage Select");
    } else {
        al_draw_text(font,al_map_rgb(255, 255, 255), X_SCREEN/2, Y_SCREEN*0.55, ALLEGRO_ALIGN_CENTER, "Return to");
        al_draw_text(font,al_map_rgb(255, 255, 255), X_SCREEN/2, Y_SCREEN*0.6, ALLEGRO_ALIGN_CENTER, "Stage Select");        
    }

    if (save_game_info->slot_1_selected || save_game_info->choose_slot_1_selected) {
        al_draw_text(font,save_game_info->choose_slot_1_color, X_SCREEN/2, Y_SCREEN/20, ALLEGRO_ALIGN_CENTER, "<- SLOT 1 ->");
        
        if (save_game_info->choose_slot_1_selected && save_game_info->timer > 20) 
            al_draw_text(font,al_map_rgb(0,0,0), X_SCREEN/2, Y_SCREEN/20, ALLEGRO_ALIGN_CENTER, "<- SLOT 1 ->");
        
        if (save_game_info->slot_1_selected && !save_game_info->return_to_stage_select_selected && save_game_info->timer < 20) 
            al_draw_rectangle(X_SCREEN/4, Y_SCREEN/2, X_SCREEN*0.75, Y_SCREEN/6, al_map_rgb(184, 134, 11), 8);
            
        
        if (save_game_info->player_progress_slot_1) {
            al_draw_scaled_bitmap(default_slot_image,0, 0,default_slot_width,default_slot_height, X_SCREEN/4, Y_SCREEN/6, X_SCREEN/2, Y_SCREEN/3, 0);    
            al_draw_text(font,al_map_rgb(255,255,255), X_SCREEN*0.4, Y_SCREEN*0.25, ALLEGRO_ALIGN_CENTER, get_progress_string(save_game_info->player_progress_slot_1));
            al_draw_text(font,al_map_rgb(255,255,255), X_SCREEN*0.4, Y_SCREEN*0.35, ALLEGRO_ALIGN_CENTER, get_time_string(save_game_info->player_progress_slot_1));        
        }
        else {
            al_draw_filled_rectangle(X_SCREEN/4, Y_SCREEN/2, X_SCREEN*0.75, Y_SCREEN/6, al_map_rgb(36, 36, 36));
            al_draw_text(font, al_map_rgb(255,255,255),X_SCREEN/2, Y_SCREEN/3, ALLEGRO_ALIGN_CENTER, "EMPTY");
        }
    }

    if (save_game_info->slot_2_selected || save_game_info->choose_slot_2_selected) {
        al_draw_text(font,save_game_info->choose_slot_2_color, X_SCREEN/2, Y_SCREEN/20, ALLEGRO_ALIGN_CENTER, "<- SLOT 2 ->");

        if (save_game_info->choose_slot_2_selected && save_game_info->timer > 20) 
                al_draw_text(font,al_map_rgb(0,0,0), X_SCREEN/2, Y_SCREEN/20, ALLEGRO_ALIGN_CENTER, "<- SLOT 2 ->");
        
        if (save_game_info->slot_2_selected && !save_game_info->return_to_stage_select_selected && save_game_info->timer < 20)
            al_draw_rectangle(X_SCREEN/4, Y_SCREEN/2, X_SCREEN*0.75, Y_SCREEN/6, al_map_rgb(184, 134, 11), 8);
    

        if (save_game_info->player_progress_slot_2) {
            al_draw_scaled_bitmap(default_slot_image,0, 0,default_slot_width,default_slot_height, X_SCREEN/4, Y_SCREEN/6, X_SCREEN/2, Y_SCREEN/3, 0);    
            al_draw_text(font,al_map_rgb(255,255,255), X_SCREEN*0.4, Y_SCREEN*0.25, ALLEGRO_ALIGN_CENTER, get_progress_string(save_game_info->player_progress_slot_2));
            al_draw_text(font,al_map_rgb(255,255,255), X_SCREEN*0.4, Y_SCREEN*0.35, ALLEGRO_ALIGN_CENTER, get_time_string(save_game_info->player_progress_slot_2));        
        }
        else {
            al_draw_filled_rectangle(X_SCREEN/4, Y_SCREEN/2, X_SCREEN*0.75, Y_SCREEN/6, al_map_rgb(36, 36, 36));
            al_draw_text(font, al_map_rgb(255,255,255),X_SCREEN/2, Y_SCREEN/3, ALLEGRO_ALIGN_CENTER, "EMPTY");
        }  
    }

    if (save_game_info->slot_3_selected || save_game_info->choose_slot_3_selected) {
        al_draw_text(font,save_game_info->choose_slot_3_color, X_SCREEN/2, Y_SCREEN/20, ALLEGRO_ALIGN_CENTER, "<- SLOT 3 ->");

        if (save_game_info->choose_slot_3_selected && save_game_info->timer > 20) 
            al_draw_text(font,al_map_rgb(0,0,0), X_SCREEN/2, Y_SCREEN/20, ALLEGRO_ALIGN_CENTER, "<- SLOT 3 ->");
        
        if (save_game_info->slot_3_selected && !save_game_info->return_to_stage_select_selected && save_game_info->timer < 20)
            al_draw_rectangle(X_SCREEN/4, Y_SCREEN/2, X_SCREEN*0.75, Y_SCREEN/6, al_map_rgb(184, 134, 11), 8);
    

        if (save_game_info->player_progress_slot_3) {
            al_draw_scaled_bitmap(default_slot_image,0, 0,default_slot_width,default_slot_height, X_SCREEN/4, Y_SCREEN/6, X_SCREEN/2, Y_SCREEN/3, 0);    
            al_draw_text(font,al_map_rgb(255,255,255), X_SCREEN*0.4, Y_SCREEN*0.25, ALLEGRO_ALIGN_CENTER, get_progress_string(save_game_info->player_progress_slot_3));
            al_draw_text(font,al_map_rgb(255,255,255), X_SCREEN*0.4, Y_SCREEN*0.35, ALLEGRO_ALIGN_CENTER, get_time_string(save_game_info->player_progress_slot_3));        
        }
        else {
            al_draw_filled_rectangle(X_SCREEN/4, Y_SCREEN/2, X_SCREEN*0.75, Y_SCREEN/6, al_map_rgb(36, 36, 36));
            al_draw_text(font, al_map_rgb(255,255,255),X_SCREEN/2, Y_SCREEN/3, ALLEGRO_ALIGN_CENTER, "EMPTY");
        }
    }


    if (save_game_info->timer == 30)
        save_game_info->timer = 0;
} 

// libera memoria
void exit_save_game(game_state *state, save_game *save_game_info,ALLEGRO_BITMAP *save_game_image) {
    state->save_game = 0;
    state->save_game_started = 0;
    al_destroy_bitmap(save_game_image);
    free(save_game_info->player_progress_slot_1);
    free(save_game_info->player_progress_slot_2);
    free(save_game_info->player_progress_slot_3);
    free(save_game_info);
}
