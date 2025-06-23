#include "Joystick.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>

#define BULLET_2_TIME 25
#define BULLET_3_TIME 25

// verifica as teclas pressionadas de forma contínua
// é chamado no evento de tempo
void joystick_update(game_state *state, Player *player) {
    if (!player) return;
    if(player->is_taking_damage) return; //o jogador não pode fazer interação com o personagem se estiver levando dano
    if(player->life <= 0) return;

    ALLEGRO_KEYBOARD_STATE key_state;
    al_get_keyboard_state(&key_state);

    // estado de movimento com base nas teclas pressionadas (horizontal)
    if (al_key_down(&key_state, state->controls->LEFT) && al_key_down(&key_state, state->controls->RIGHT)) {
        player->is_moving = 0;
        player->is_stopped = 1;
    }
    else if (al_key_down(&key_state, state->controls->LEFT)) {
        player->is_moving = 1;
        player->is_stopped = 0;
        player->direction = -1;
    } 
    else if (al_key_down(&key_state, state->controls->RIGHT)) {
        player->is_moving = 1;
        player->is_stopped = 0;
        player->direction = 1;
    }
    else {
        player->is_moving = 0;
        player->is_stopped = 1;
    }

    // lógica de agachamento
    if (al_key_down(&key_state, state->controls->DOWN)) {
        joystick_down(player);
    } else {
        // Se a tecla não está pressionada, ele levanta.
        joystick_stand_up(player);
    }   

    // lógica de carregar tiro
    if (al_key_down(&key_state, state->controls->SHOT)) {
        player->is_charging_shot = 1;
    } else {
        player->is_charging_shot = 0;
    }

    // lógica de mirar para cima
    if (al_key_down(&key_state, state->controls->UP)) {
        player->is_looking_up = 1;
    } else {
        player->is_looking_up = 0;
    }

    //atualiza o tiro, deixando ele mais carregado
    if (player->is_charging_shot) {
        player->timer_charge_shot++;
        if (player->charge_shot == 1 && player->timer_charge_shot > BULLET_2_TIME) {
            player->charge_shot = 2;
            player->timer_charge_shot = 0;
        } else if (player->charge_shot == 2 && player->timer_charge_shot > BULLET_3_TIME) {
            player->charge_shot = 3;
            player->timer_charge_shot = 0;
        }
    }

}


// Verifica chamadas pontuais (apertos de teclas)
void joystick_handle(ALLEGRO_EVENT *event, game_state *state, Player *player, int X_SCREEN, int Y_SCREEN) {
    if (!player || !event) return;

    //clicou para pausar
    if (event->type == ALLEGRO_EVENT_KEY_DOWN && event->keyboard.keycode == state->controls->PAUSE) state->pause = 1;
    
    //o jogador não pode fazer interação com o personagem se estiver levando dano ou estiver morto
    if(player->is_taking_damage || player->life <= 0) return; 
    
    //o player pular
    if (event->type == ALLEGRO_EVENT_KEY_DOWN && event->keyboard.keycode == state->controls->JUMP) 
            joystick_jump(player);

    // se o jogador largou o botão de atirar então atira
    else if (event->type == ALLEGRO_EVENT_KEY_UP) {
        if (event->keyboard.keycode == state->controls->SHOT) {
            buster_fire(player, X_SCREEN, Y_SCREEN);
        }
        
    }
}


//////////////////////////////////// AUXILIARES ////////////////////////////////////////////

// lógica do pulo
void joystick_jump(Player *player) {
    if (!player->is_on_ground ) return; //não tem pulo duplo 

    player->vy = -player->jump_strenght;
    player->is_on_ground = 0;    
    player->is_squat = 0; // se tava agachado não está mais
}

// lógica de agachar
void joystick_down(Player *player) {
    if (!player->is_on_ground || player->is_squat) return; //tem que estar no chão para agachar
    player->is_squat = 1;
} 

// lógica de levantaar
void joystick_stand_up(Player *player) {
    if (!player->is_squat) return;
    player->is_squat = 0;
}