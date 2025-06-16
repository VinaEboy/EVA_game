#include "Joystick.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>

#define BULLET_2_TIME 25
#define BULLET_3_TIME 25

// Protótipos para as funções auxiliares internas
void joystick_jump(Player *player);
void joystick_down(Player *player);
void joystick_stand_up(Player *player);



//  FUNÇÃO DE UPDATE (Contínuo) - Chamada DENTRO do timer
void joystick_update(game_state *state, Player *player) {
    if (!player) return;
    if(player->is_taking_damage) return; //o jogador não pode fazer interação com o personagem se estiver levando dano
    if(player->life <= 0) return;

    ALLEGRO_KEYBOARD_STATE key_state;
    al_get_keyboard_state(&key_state);

    // --- LÓGICA DE MOVIMENTO HORIZONTAL ---
    // Esta seção agora é a ÚNICA fonte de verdade para o estado de movimento.
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
        // CORREÇÃO CRÍTICA: Se nenhuma tecla de movimento está pressionada, o jogador para,
        // mas a sua DIREÇÃO é MANTIDA. Não mexemos em player->direction aqui.
        // Isso resolve o bug de ele virar para a direita sozinho.
        player->is_moving = 0;
        player->is_stopped = 1;
    }

    // --- LÓGICA DE AGACHAR (CONTÍNUA) ---
    // Faz mais sentido tratar o agachar como um estado contínuo (enquanto segura a tecla)
    if (al_key_down(&key_state, state->controls->DOWN)) {
        joystick_down(player);
    } else {
        // Se a tecla não está pressionada, ele levanta.
        joystick_stand_up(player);
    }

    // --- LÓGICA DE CARREGAR O TIRO (CONTÍNUA) ---
    if (al_key_down(&key_state, state->controls->SHOT)) {
        player->is_charging_shot = 1;
    } else {
        player->is_charging_shot = 0;
    }

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


//  FUNÇÃO DE HANDLE (Eventos Pontuais) - Chamada a CADA evento
void joystick_handle(ALLEGRO_EVENT *event, game_state *state, Player *player) {
    if (!player || !event) return;

    if (event->type == ALLEGRO_EVENT_KEY_DOWN && event->keyboard.keycode == state->controls->PAUSE) state->pause = 1;
    
    
    if(player->is_taking_damage) return; //o jogador não pode fazer interação com o personagem se estiver levando dano
    if(player->life <= 0) return;
    
    if (event->type == ALLEGRO_EVENT_KEY_DOWN && event->keyboard.keycode == state->controls->JUMP) 
            joystick_jump(player);

    
    else if (event->type == ALLEGRO_EVENT_KEY_UP) {
        if (event->keyboard.keycode == state->controls->SHOT) {
            buster_fire(player);
        }
        
    }
}


// --- Funções Auxiliares ---

void joystick_jump(Player *player) {
    if (!player->is_on_ground || player->is_squat) return;

    player->vy = -PLAYER_JUMP_STRENGTH;
    player->is_on_ground = 0;    
}

void joystick_down(Player *player) {
    if (!player->is_on_ground || player->is_squat) return;
    player->is_squat = 1;
} 

void joystick_stand_up(Player *player) {
    if (!player->is_squat) return;
    player->is_squat = 0;
}