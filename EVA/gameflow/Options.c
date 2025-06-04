#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro5.h>																																												
#include <allegro5/allegro_font.h>																																											
#include <allegro5/allegro_primitives.h>	
#include <allegro5/allegro_ttf.h>
#include <string.h>

#include "Title_screen.h"
#include "Game_state.h"

options *options_create() {
    options *options_info = (options *) malloc(sizeof(options));
    if (!options_info) return NULL;
    options_info->SHOT_selected = 0;
    options_info->SHOT_color = al_map_rgb(255, 255, 255);
    options_info->JUMP_selected = 0;
    options_info->JUMP_color = al_map_rgb(255, 255, 255);
    options_info->LEFT_selected = 0;
    options_info->LEFT_color = al_map_rgb(255, 255, 255);
    options_info->RIGHT_selected = 0;
    options_info->RIGHT_color = al_map_rgb(255, 255, 255);    
    options_info->UP_selected = 0;
    options_info->UP_color = al_map_rgb(255, 255, 255);    
    options_info->DOWN_selected = 0;
    options_info->DOWN_color = al_map_rgb(255, 255, 255);    
    options_info->CONFIRM_selected = 0;
    options_info->CONFIRM_color = al_map_rgb(255, 255, 255);    
    options_info->PAUSE_selected = 0;   
    options_info->PAUSE_color = al_map_rgb(255, 255, 255);    
    options_info->BACK_selected = 1;
    options_info->BACK_color = al_map_rgb(184, 134, 11);    
    options_info->key_to_switch = 0; // vai falar se está na etapa de trocar o valor de uma chave
    options_info->timer = 0;
    return options_info;
}


void start_options(game_state *state, options **options_info ) {
    *options_info = options_create();
    if(!*options_info) {
        fprintf(stderr, "Falha ao criar informações para opções\n");
        exit(1);
    }
    state->options_started = 1;
}

void show_options(ALLEGRO_EVENT *event, game_state *state, ALLEGRO_FONT *font, ALLEGRO_DISPLAY *disp, options *options_info, int X_SCREEN, int Y_SCREEN) {

    al_clear_to_color(al_map_rgb(0, 0, 0));
    

    if (event->type == ALLEGRO_EVENT_KEY_UP) {
        if (options_info->key_to_switch) 
            options_key_switch (event, state, options_info);
        else {
            if (event->keyboard.keycode == state->controls->DOWN)
                options_down_move(options_info);
            if (event->keyboard.keycode == state->controls->UP)
                options_up_move(options_info);
            if (event->keyboard.keycode == state->controls->CONFIRM) 
                options_key_select(state,options_info);
        }
        
    }

    if (options_info->key_to_switch) options_info->timer++;

    options_draw_text(state, font, options_info, X_SCREEN, Y_SCREEN);

    if(!state->options) free(options_info);
    al_flip_display();

}

//////////////////////////////// Auxiliares /////////////////////////////////////////////

const char *get_key_name(int keycode) {

    int key_map_size = sizeof(key_map) / sizeof(key_map_t);

    for (int i = 0; i < key_map_size; i++) {
        if (key_map[i].keycode == keycode) {
            return key_map[i].name;
        }
    }
    return "UNKNOWN"; //Não é uma tecla com suporte para o jogo
}


void options_draw_text (game_state *state, ALLEGRO_FONT *font, options *options_info, int X_SCREEN,int  Y_SCREEN) {

    int margin_top = Y_SCREEN/6;
    int margin_side = X_SCREEN/3;
    int padding_Y = Y_SCREEN/15;

    al_draw_text(font, options_info->SHOT_color,margin_side, margin_top, ALLEGRO_ALIGN_CENTER, "SHOT");
    al_draw_text(font, options_info->SHOT_color,X_SCREEN - margin_side, margin_top, ALLEGRO_ALIGN_CENTER, get_key_name(state->controls->SHOT));

    al_draw_text(font, options_info->JUMP_color,margin_side, margin_top + padding_Y, ALLEGRO_ALIGN_CENTER, "JUMP");
    al_draw_text(font, options_info->JUMP_color,X_SCREEN - margin_side, margin_top + padding_Y, ALLEGRO_ALIGN_CENTER, get_key_name(state->controls->JUMP));

    al_draw_text(font, options_info->LEFT_color,margin_side, margin_top + 2*padding_Y, ALLEGRO_ALIGN_CENTER, "LEFT");
    al_draw_text(font, options_info->LEFT_color,X_SCREEN - margin_side, margin_top + 2*padding_Y, ALLEGRO_ALIGN_CENTER, get_key_name(state->controls->LEFT));

    al_draw_text(font, options_info->RIGHT_color,margin_side, margin_top + 3*padding_Y, ALLEGRO_ALIGN_CENTER, "RIGHT");
    al_draw_text(font, options_info->RIGHT_color,X_SCREEN - margin_side, margin_top + 3*padding_Y, ALLEGRO_ALIGN_CENTER, get_key_name(state->controls->RIGHT));

    al_draw_text(font, options_info->UP_color,margin_side, margin_top + 4*padding_Y, ALLEGRO_ALIGN_CENTER, "UP");
    al_draw_text(font, options_info->UP_color,X_SCREEN - margin_side, margin_top + 4*padding_Y, ALLEGRO_ALIGN_CENTER, get_key_name(state->controls->UP));

    al_draw_text(font, options_info->DOWN_color,margin_side, margin_top + 5*padding_Y, ALLEGRO_ALIGN_CENTER, "DOWN");
    al_draw_text(font, options_info->DOWN_color,X_SCREEN - margin_side, margin_top + 5*padding_Y, ALLEGRO_ALIGN_CENTER, get_key_name(state->controls->DOWN));

    al_draw_text(font, options_info->CONFIRM_color,margin_side, margin_top + 6*padding_Y, ALLEGRO_ALIGN_CENTER, "CONFIRM");
    al_draw_text(font, options_info->CONFIRM_color,X_SCREEN - margin_side, margin_top + 6*padding_Y, ALLEGRO_ALIGN_CENTER, get_key_name(state->controls->CONFIRM));

    al_draw_text(font, options_info->PAUSE_color,margin_side, margin_top + 7*padding_Y, ALLEGRO_ALIGN_CENTER, "PAUSE");
    al_draw_text(font, options_info->PAUSE_color,X_SCREEN - margin_side, margin_top + 7*padding_Y, ALLEGRO_ALIGN_CENTER, get_key_name(state->controls->PAUSE));

    al_draw_text(font, options_info->BACK_color, X_SCREEN/2, Y_SCREEN - margin_top, ALLEGRO_ALIGN_CENTER, "BACK");

    if (options_info->timer > 0 && options_info->timer < 11) //fica 1/3 de segundo ofuscado
        options_blind(state, font, options_info, X_SCREEN, Y_SCREEN, margin_top, margin_side, padding_Y);

    if (options_info->timer == 31) options_info->timer = 0; //reseta a piscagem a cada 1segundo
}


void options_blind (game_state *state, ALLEGRO_FONT *font, options *options_info, int X_SCREEN, int Y_SCREEN, int margin_top, int margin_side, int padding_Y) {

    if (options_info->SHOT_selected) {
        al_draw_text(font, al_map_rgb(0, 0, 0),margin_side, margin_top, ALLEGRO_ALIGN_CENTER, "SHOT");
        al_draw_text(font, al_map_rgb(0, 0, 0),X_SCREEN - margin_side, margin_top, ALLEGRO_ALIGN_CENTER, get_key_name(state->controls->SHOT));           
    }
    else if (options_info->JUMP_selected) {
        al_draw_text(font, al_map_rgb(0, 0, 0),margin_side, margin_top + padding_Y, ALLEGRO_ALIGN_CENTER, "JUMP");
        al_draw_text(font, al_map_rgb(0, 0, 0),X_SCREEN - margin_side, margin_top + padding_Y, ALLEGRO_ALIGN_CENTER, get_key_name(state->controls->JUMP));
    }
    else if (options_info->LEFT_selected) {
        al_draw_text(font, al_map_rgb(0, 0, 0),margin_side, margin_top + 2*padding_Y, ALLEGRO_ALIGN_CENTER, "LEFT");
        al_draw_text(font, al_map_rgb(0, 0, 0),X_SCREEN - margin_side, margin_top + 2*padding_Y, ALLEGRO_ALIGN_CENTER, get_key_name(state->controls->LEFT));
    }
    else if (options_info->RIGHT_selected) {
        al_draw_text(font, al_map_rgb(0, 0, 0),margin_side, margin_top + 3*padding_Y, ALLEGRO_ALIGN_CENTER, "RIGHT");
        al_draw_text(font, al_map_rgb(0, 0, 0),X_SCREEN - margin_side, margin_top + 3*padding_Y, ALLEGRO_ALIGN_CENTER, get_key_name(state->controls->RIGHT));
    }
    else if (options_info->UP_selected) {
        al_draw_text(font, al_map_rgb(0, 0, 0),margin_side, margin_top + 4*padding_Y, ALLEGRO_ALIGN_CENTER, "UP");
        al_draw_text(font, al_map_rgb(0, 0, 0),X_SCREEN - margin_side, margin_top + 4*padding_Y, ALLEGRO_ALIGN_CENTER, get_key_name(state->controls->UP));
    }
    else if (options_info->DOWN_selected) {
        al_draw_text(font, al_map_rgb(0, 0, 0),margin_side, margin_top + 5*padding_Y, ALLEGRO_ALIGN_CENTER, "DOWN");
        al_draw_text(font, al_map_rgb(0, 0, 0),X_SCREEN - margin_side, margin_top + 5*padding_Y, ALLEGRO_ALIGN_CENTER, get_key_name(state->controls->DOWN));
    }
    else if (options_info->CONFIRM_selected) {
        al_draw_text(font, al_map_rgb(0, 0, 0),margin_side, margin_top + 6*padding_Y, ALLEGRO_ALIGN_CENTER, "CONFIRM");
        al_draw_text(font, al_map_rgb(0, 0, 0),X_SCREEN - margin_side, margin_top + 6*padding_Y, ALLEGRO_ALIGN_CENTER, get_key_name(state->controls->CONFIRM));
    }
    else if (options_info->PAUSE_selected) {
        al_draw_text(font, al_map_rgb(0, 0, 0),margin_side, margin_top + 7*padding_Y, ALLEGRO_ALIGN_CENTER, "PAUSE");
        al_draw_text(font, al_map_rgb(0, 0, 0),X_SCREEN - margin_side, margin_top + 7*padding_Y, ALLEGRO_ALIGN_CENTER, get_key_name(state->controls->PAUSE));
    }

}


void options_down_move(options *options_info ) {
    if(options_info->SHOT_selected ) {
        options_info->SHOT_selected  = 0;
        options_info->SHOT_color = al_map_rgb(255, 255, 255);          
        options_info->JUMP_selected  = 1;
        options_info->JUMP_color = al_map_rgb(184, 134, 11);    
    } else if(options_info->JUMP_selected ) {
        options_info->JUMP_selected  = 0;
        options_info->JUMP_color = al_map_rgb(255, 255, 255);          
        options_info->LEFT_selected  = 1;
        options_info->LEFT_color = al_map_rgb(184, 134, 11);    
    } else if(options_info->LEFT_selected ) {
        options_info->LEFT_selected  = 0;
        options_info->LEFT_color = al_map_rgb(255, 255, 255);          
        options_info->RIGHT_selected  = 1;
        options_info->RIGHT_color = al_map_rgb(184, 134, 11);    
    } else if(options_info->RIGHT_selected ) {
        options_info->RIGHT_selected  = 0;
        options_info->RIGHT_color = al_map_rgb(255, 255, 255);          
        options_info->UP_selected  = 1;
        options_info->UP_color = al_map_rgb(184, 134, 11);    
    } else if(options_info->UP_selected ) {
        options_info->UP_selected  = 0;
        options_info->UP_color = al_map_rgb(255, 255, 255);          
        options_info->DOWN_selected  = 1;
        options_info->DOWN_color = al_map_rgb(184, 134, 11);    
    } else if(options_info->DOWN_selected ) {
        options_info->DOWN_selected  = 0;
        options_info->DOWN_color = al_map_rgb(255, 255, 255);          
        options_info->CONFIRM_selected  = 1;
        options_info->CONFIRM_color = al_map_rgb(184, 134, 11);    
    } else if(options_info->CONFIRM_selected ) {
        options_info->CONFIRM_selected  = 0;
        options_info->CONFIRM_color = al_map_rgb(255, 255, 255);          
        options_info->PAUSE_selected  = 1;
        options_info->PAUSE_color = al_map_rgb(184, 134, 11);    
    } else if(options_info->PAUSE_selected ) {
        options_info->PAUSE_selected  = 0;
        options_info->PAUSE_color = al_map_rgb(255, 255, 255);          
        options_info->BACK_selected  = 1;
        options_info->BACK_color = al_map_rgb(184, 134, 11);    
    } 
}


void options_up_move(options *options_info ) {
    if(options_info->BACK_selected) {
        options_info->BACK_selected = 0;
        options_info->BACK_color = al_map_rgb(255, 255, 255);  
        options_info->PAUSE_selected = 1;
        options_info->PAUSE_color = al_map_rgb(184, 134, 11);       
    } else if (options_info->PAUSE_selected) {
        options_info->PAUSE_selected = 0;
        options_info->PAUSE_color = al_map_rgb(255, 255, 255);  
        options_info->CONFIRM_selected = 1;
        options_info->CONFIRM_color = al_map_rgb(184, 134, 11);    
    } else if (options_info->CONFIRM_selected) {
        options_info->CONFIRM_selected = 0;
        options_info->CONFIRM_color = al_map_rgb(255, 255, 255);  
        options_info->DOWN_selected = 1;
        options_info->DOWN_color = al_map_rgb(184, 134, 11);    
    } else if (options_info->DOWN_selected) {
        options_info->DOWN_selected = 0;
        options_info->DOWN_color = al_map_rgb(255, 255, 255);  
        options_info->UP_selected = 1;
        options_info->UP_color = al_map_rgb(184, 134, 11);    
    } else if (options_info->UP_selected) {
        options_info->UP_selected = 0;
        options_info->UP_color = al_map_rgb(255, 255, 255);  
        options_info->RIGHT_selected = 1;
        options_info->RIGHT_color = al_map_rgb(184, 134, 11);    
    } else if (options_info->RIGHT_selected) {
        options_info->RIGHT_selected = 0;
        options_info->RIGHT_color = al_map_rgb(255, 255, 255);  
        options_info->LEFT_selected = 1;
        options_info->LEFT_color = al_map_rgb(184, 134, 11);    
    } else if (options_info->LEFT_selected) {
        options_info->LEFT_selected = 0;
        options_info->LEFT_color = al_map_rgb(255, 255, 255);  
        options_info->JUMP_selected = 1;
        options_info->JUMP_color = al_map_rgb(184, 134, 11);    
    } else if (options_info->JUMP_selected) {
        options_info->JUMP_selected = 0;
        options_info->JUMP_color = al_map_rgb(255, 255, 255);  
        options_info->SHOT_selected = 1;
        options_info->SHOT_color = al_map_rgb(184, 134, 11);    
    }
}

void options_key_select(game_state *state, options *options_info) {
    if (options_info->BACK_selected) {
        state->options = 0;
        state->options_started = 0;
        return;
    }
    options_info->key_to_switch = 1;
}

// não deixa trocar para botoes como F1
void options_key_switch(ALLEGRO_EVENT *event, game_state *state, options *options_info) {
    options_info->key_to_switch = 0;
    options_info->timer = 0;
    int new_key = event->keyboard.keycode;

    //não é possível trocar o valor da chave para um valor que já está em uso
    if ((new_key == state->controls->SHOT && !options_info->SHOT_selected)       || 
        (new_key == state->controls->JUMP && !options_info->JUMP_selected)       ||
        (new_key == state->controls->LEFT && !options_info->LEFT_selected)       ||
        (new_key == state->controls->RIGHT && !options_info->RIGHT_selected)     ||
        (new_key == state->controls->UP && !options_info->UP_selected)           ||
        (new_key == state->controls->DOWN && !options_info->DOWN_selected)       ||
        (new_key == state->controls->CONFIRM && !options_info->CONFIRM_selected) ||
        (new_key == state->controls->PAUSE && !options_info->PAUSE_selected)) 
        return;
    
    //Não é um valor previsto para a chave
    if (strcmp("UNKNOWN",get_key_name(new_key)) == 0)   return;

    if (options_info->SHOT_selected) state->controls->SHOT = new_key;
    else if (options_info->JUMP_selected) state->controls->JUMP = new_key;
    else if (options_info->LEFT_selected) state->controls->LEFT = new_key;
    else if (options_info->RIGHT_selected) state->controls->RIGHT = new_key;
    else if (options_info->UP_selected) state->controls->UP = new_key;
    else if (options_info->DOWN_selected) state->controls->DOWN = new_key;
    else if (options_info->CONFIRM_selected) state->controls->CONFIRM = new_key;
    else if (options_info->PAUSE_selected) state->controls->PAUSE = new_key;
    
}
