#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro5.h>																																												
#include <allegro5/allegro_font.h>																																											
#include <allegro5/allegro_primitives.h>	
#include <allegro5/allegro_ttf.h>
#include <string.h>

#include "Title_screen.h"
#include "../levels/Level_1.h"
#include "../levels/Level_2.h"
#include "../levels/Level_3.h"
#include "../levels/Level_4.h"
#include "../levels/Level_5.h"
#include "../levels/Level_6.h"
#include "../levels/Level_7.h"
#include "../levels/Level_8.h" 
#include "Game_over.h"
#include "Pause.h"
#include "Game_state.h"

// cria info
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
    options_info->DIFFICULTY_selected = 0;
    options_info->DIFFICULTY_color = al_map_rgb(255, 255, 255); 
    options_info->SOUND_selected = 0;
    options_info->SOUND_color = al_map_rgb(255, 255, 255);  
    options_info->APPLY_selected = 0;
    options_info->APPLY_color = al_map_rgb(255, 255, 255); 
    options_info->BACK_selected = 1;
    options_info->BACK_color = al_map_rgb(184, 134, 11);   

    options_info->key_to_switch = 0; // vai falar se está na etapa de trocar o valor de uma chave
    options_info->timer = 0;
    return options_info;
}

// inicializa
void start_options(game_state *state, options **options_info ) {
    *options_info = options_create();
    if(!*options_info) {
        fprintf(stderr, "Falha ao criar informações para opções\n");
        exit(1);
    }
    state->options_started = 1;
}

//mostra na tela
void show_options(ALLEGRO_EVENT *event, game_state *state, ALLEGRO_FONT *font, ALLEGRO_DISPLAY *disp, game_assets *assets, int X_SCREEN, int Y_SCREEN) {
    options *options_info = assets->options_info;
    al_clear_to_color(al_map_rgb(0, 0, 0));
    
    if (event->type == ALLEGRO_EVENT_TIMER && options_info->key_to_switch) options_info->timer++;

    if (event->type == ALLEGRO_EVENT_KEY_DOWN) {
        if (options_info->key_to_switch) 
            options_key_switch (event, state, options_info);
        else {
            if (event->keyboard.keycode == state->controls->DOWN)
                options_down_move(options_info);
            if (event->keyboard.keycode == state->controls->UP)
                options_up_move(options_info);
            if (event->keyboard.keycode == state->controls->CONFIRM) 
                options_key_select(state,assets);
            if (event->keyboard.keycode == state->controls->LEFT)
                options_left_move(state,options_info);
            if (event->keyboard.keycode == state->controls->RIGHT)
                options_right_move(state,options_info);
        }
        
    }


    options_draw_text(state, font, options_info, X_SCREEN, Y_SCREEN);

    if(!state->options) free(options_info);
    al_flip_display();

}

/////////////////////// FUNÇÕES DE INTERAÇÕES NO MENU ////////////////////////

// para baixo
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
        options_info->DIFFICULTY_selected = 1;
        options_info->DIFFICULTY_color = al_map_rgb(184, 134, 11);
    } else if (options_info->DIFFICULTY_selected) {
        options_info->DIFFICULTY_selected  = 0;
        options_info->DIFFICULTY_color = al_map_rgb(255, 255, 255);
        options_info->SOUND_selected = 1;
        options_info->SOUND_color = al_map_rgb(184, 134, 11);
    } else if (options_info->SOUND_selected) {
        options_info->SOUND_selected = 0;       
        options_info->SOUND_color = al_map_rgb(255, 255, 255);
        options_info->APPLY_selected = 1;
        options_info->APPLY_color = al_map_rgb(184, 134, 11);
    } else if (options_info->APPLY_selected) {
        options_info->APPLY_selected = 0;
        options_info->APPLY_color = al_map_rgb(255, 255, 255); 
        options_info->BACK_selected  = 1;
        options_info->BACK_color = al_map_rgb(184, 134, 11);    
    } 
}

// para cima
void options_up_move(options *options_info ) {
    if(options_info->BACK_selected) {
        options_info->BACK_selected = 0;
        options_info->BACK_color = al_map_rgb(255, 255, 255);  
        options_info->APPLY_selected = 1;
        options_info->APPLY_color = al_map_rgb(184, 134, 11);
    } else if (options_info->APPLY_selected) {
        options_info->APPLY_selected = 0;
        options_info->APPLY_color =al_map_rgb(255, 255, 255); 
        options_info->SOUND_selected = 1;
        options_info->SOUND_color = al_map_rgb(184, 134, 11); 
    } else if (options_info->SOUND_selected) {
        options_info->SOUND_selected = 0;
        options_info->SOUND_color = al_map_rgb(255, 255, 255); 
        options_info->DIFFICULTY_selected = 1;
        options_info->DIFFICULTY_color = al_map_rgb(184, 134, 11);   
    } else if (options_info->DIFFICULTY_selected) {
        options_info->DIFFICULTY_selected = 0;
        options_info->DIFFICULTY_color = al_map_rgb(255, 255, 255);  
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

// é o botão de confirmar
// PARA O APLICAR, ele reinicia a fase com as mudanças aplicadas ou volta para a tela principal
void options_key_select(game_state *state, game_assets *assets) {
    options *options_info = assets->options_info;   

    if (options_info->BACK_selected ) {
        state->options = 0;
        state->options_started = 0;
        return;
    }

    if (options_info->APPLY_selected) {
        state->options = 0;
        state->options_started = 0;
        
        //se estava pausado porque estava em um level
        // vai liberar a memória desse pause
        if (state->pause) 
            exit_pause(state,assets->pause_info, assets->pause_image);

        if (state->title_screen) {
            exit_title_screen(state, assets->title_screen_info, assets->title_screen_image);
            state->title_screen = 1;
        }
        else if (state->game_over) {
            exit_game_over(state,assets->game_over_info,assets->game_over_image);
            state->game_over = 1;
        }
        else if (state->level_1) {
            exit_level_1(state,assets->level_1_info,assets->sprites);
            state->level_1 = 1;
        }
        else if (state->level_2) {
            exit_level_2(state, assets->level_2_info, assets->sprites);
            state->level_2 = 1;
        }
        else if (state->level_3) {
            exit_level_3(state, assets->level_3_info, assets->sprites);
            state->level_3 = 1;
        }
        else if (state->level_4) {
            exit_level_4(state, assets->level_4_info, assets->sprites);
            state->level_4 = 1;
        }
        else if (state->level_5) {
            exit_level_5(state, assets->level_5_info, assets->sprites);
            state->level_5 = 1;
        }
        else if (state->level_6) {
            exit_level_6(state, assets->level_6_info, assets->sprites);
            state->level_6 = 1;
        }
        else if (state->level_7) {
            exit_level_7(state, assets->level_7_info, assets->sprites);
            state->level_7 = 1;
        }
        else if (state->level_8) {
            exit_level_8(state, assets->level_8_info, assets->sprites);
            state->level_8 = 1;
        }
        return;
    }

    options_info->key_to_switch = 1;
}

// é quando uma tecla está selecionada para mudar o mapeamento e está esperando
// a nova tecla que vai ser configurada. Não permite mudar para uma tecla que já está
// sendo usada ou que não está prevista no dicionário (exemplo: F7)
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
    
    //Não é um valor previsto para a chave (uma tecla estranha)
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

// para esquerda
void options_left_move(game_state *state, options *options_info) {

    if (options_info->DIFFICULTY_selected) {
        if (state->player_progress->dificulty == DIFFICULTY_EASY)
            state->player_progress->dificulty = DIFFICULTY_HARD;
        else if (state->player_progress->dificulty == DIFFICULTY_MEDIUM)
            state->player_progress->dificulty = DIFFICULTY_EASY;
        else if (state->player_progress->dificulty == DIFFICULTY_HARD)
            state->player_progress->dificulty = DIFFICULTY_MEDIUM;
    }
    else if (options_info->SOUND_selected) {
        state->sound_volume -= 0.1;
        if (state->sound_volume < 0) state->sound_volume = 1; //ele vai pro 1
    }

}

// para direita
void options_right_move(game_state *state, options *options_info) {

    if (options_info->DIFFICULTY_selected) {
        if (state->player_progress->dificulty == DIFFICULTY_EASY)
            state->player_progress->dificulty = DIFFICULTY_MEDIUM;
        else if (state->player_progress->dificulty == DIFFICULTY_MEDIUM)
            state->player_progress->dificulty = DIFFICULTY_HARD;
        else if (state->player_progress->dificulty == DIFFICULTY_HARD)
            state->player_progress->dificulty = DIFFICULTY_EASY;
    }
    else if (options_info->SOUND_selected) {
        state->sound_volume += 0.1;
        if (state->sound_volume >= 1.1) state->sound_volume = 0; //ele vai pro 0
    }

}

/////////////////////////////////////////////////////////////

//////////////////////////// Auxiliares /////////////////////

//desenha o texto
void options_draw_text (game_state *state, ALLEGRO_FONT *font, options *options_info, int X_SCREEN,int  Y_SCREEN) {

    int margin_top = Y_SCREEN*0.08;
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

    al_draw_text(font, options_info->DIFFICULTY_color,margin_side, margin_top + 8.5*padding_Y, ALLEGRO_ALIGN_CENTER, "DIFFICULTY");
    if (state->player_progress->dificulty == DIFFICULTY_EASY)
        al_draw_text(font, options_info->DIFFICULTY_color,X_SCREEN - margin_side, margin_top + 8.5*padding_Y, ALLEGRO_ALIGN_CENTER, "<- EASY ->");
    else if (state->player_progress->dificulty == DIFFICULTY_MEDIUM)
        al_draw_text(font, options_info->DIFFICULTY_color,X_SCREEN - margin_side, margin_top + 8.5*padding_Y, ALLEGRO_ALIGN_CENTER, "<- MEDIUM ->");
    else if (state->player_progress->dificulty == DIFFICULTY_HARD)
        al_draw_text(font, options_info->DIFFICULTY_color,X_SCREEN - margin_side, margin_top + 8.5*padding_Y, ALLEGRO_ALIGN_CENTER, "<- HARD ->");

    al_draw_text(font, options_info->SOUND_color,margin_side, margin_top + 9.5*padding_Y, ALLEGRO_ALIGN_CENTER, "SONG VOLUME");
    al_draw_text(font, options_info->SOUND_color, X_SCREEN - margin_side, margin_top + 9.5*padding_Y, ALLEGRO_ALIGN_CENTER, float_to_string(state->sound_volume));


    al_draw_text(font, options_info->APPLY_color,X_SCREEN/2, Y_SCREEN - margin_top - 1.5*padding_Y, ALLEGRO_ALIGN_CENTER, "APPLY");


    al_draw_text(font, options_info->BACK_color, X_SCREEN/2, Y_SCREEN - margin_top, ALLEGRO_ALIGN_CENTER, "BACK");

    if (options_info->timer > 0 && options_info->timer < 11) //fica 1/3 de segundo ofuscado
        options_blind(state, font, options_info, X_SCREEN, Y_SCREEN, margin_top, margin_side, padding_Y);

    if (options_info->timer == 31) options_info->timer = 0; //reseta a piscagem a cada 1segundo
}


// pisca o menu de opções (feedback visual de que está aguardando input)
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

// é a função que usa o dicionário que está em game_state para traduzir o valor chave da tecla (do Allegro)
// para a string que descreve a tecla
const char *get_key_name(int keycode) {

    int key_map_size = sizeof(key_map) / sizeof(key_map_t);

    for (int i = 0; i < key_map_size; i++) {
        if (key_map[i].keycode == keycode) {
            return key_map[i].name;
        }
    }
    return "UNKNOWN"; //Não é uma tecla com suporte para o jogo
}

// função que recebe um float e formata para string, usado no ajustador de volume
const char* float_to_string(float value) {

    static char float_buffer[30];

    snprintf(float_buffer, sizeof(float_buffer), "<- %.1f ->", value);

    return float_buffer;
}