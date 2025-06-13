#include "Jet_alone.h"
#include <stdlib.h> // Para rand() e srand()
#include <time.h>   // Para time()
#include <math.h>

Jet_alone *ja_create(float dificulty, float squat_probability, float x, float y, int direction) {
    Jet_alone *ja = (Jet_alone *)malloc(sizeof(Jet_alone));
    if (!ja) return NULL;
  
    ja->life = 100;
    ja->damage = 20;
    ja->dead = 0;

    ja->x = x, 
    ja->y = y;
    ja->center_x = x + JA_WIDTH/2;
    ja->center_y = y + JA_HEIGHT/2;
    ja->hit_box_x = 0.5*JA_WIDTH;
    ja->hit_box_y = 0.98*JA_HEIGHT;

    ja->direction = direction;

    ja->hit_take = 0;
    ja->hit_take_timer = 0;

    ja->state = JA_STOP;
    ja->state_timer = 0;
    ja->current_frame = 0;
    ja->frame_timer = 0;
    ja->squat_probability = squat_probability;

    ja->ja_buster = ja_buster_create(dificulty);
    ja->shot_timer = 0;
    ja->is_shooting = 0;

    return ja;
}

void update_ja(Jet_alone *ja, float camera_x, Player *player, int X_SCREEN) {

    update_state_ja(ja, camera_x, player, X_SCREEN);
    action_ja(ja,player);

    //fazer lógica de gravidade
    //fazer uma lógica para ver se algum tiro do jogador colidiu nele e reduzir a vida dele
    //fazer lógica de morte

}

void ja_sprite (Jet_alone *ja, ALLEGRO_BITMAP **sprite_sheet, entities_sprites *sprites) {

    switch (ja->state) {
        case JA_WALK:
            *sprite_sheet = sprites->jet_alone_walk;
            break; 

        case JA_SQUAT:
            *sprite_sheet = sprites->jet_alone_squat;
            break;

        case JA_STOP:
            *sprite_sheet = sprites->jet_alone_stop;
            break;

        default:
            *sprite_sheet = sprites->jet_alone_stop;
            break;        
    }

}

//atualiza o estado do jet alone e caso necessário faz ele virar a direção
void update_state_ja(Jet_alone *ja, float camera_x, Player *player, int X_SCREEN) {
    ja->state_timer++;
    ja->hit_box_y = 0.98*JA_HEIGHT; //definir a priori

    //lógica para caso o player passe pelo inimigo, o inimigo virar de direção
    if (ja->direction == -1 && (ja->x + JA_FLIP_DISTANCE < player->x))
        ja->direction = 1;
    else if (ja->direction == 1 && (player->x + JA_FLIP_DISTANCE < ja->x))
        ja->direction = -1;

    // Lógica corrigida para o inimigo perseguir
    unsigned char is_visible = (ja->x + JA_WIDTH > camera_x) && (ja->x < camera_x + X_SCREEN);
    float ja_distance = abs(ja->x - player->x); 

    if (!is_visible || ja_distance > JA_MIN_DISTANCE) { 
        ja->state = JA_WALK; 
        return; 
    }

    if(ja->state == JA_WALK) //significa que estava andando e chegou perto o suficiente, já pode tomar uma escolha
        ja->state_timer = JA_STATE_TIMER + 1;

    //tomada de escolha
    if (ja->state_timer > JA_STATE_TIMER) {
        ja->state_timer = 0;

        //o player estar agachado aumenta a probabilidade do JA agachar
        if(player->is_squat)
            ja->squat_probability *= 2;

        if (( (rand() % 100) + 1)*100*ja->squat_probability > JA_SQUAT_CHANCE ) 
            ja->state = JA_SQUAT;
        else
            ja->state = JA_STOP;
    }

    if (ja->state == JA_SQUAT)
        ja->hit_box_y = 0.7*JA_HEIGHT; //a hitbox diminui

}

void action_ja(Jet_alone *ja, Player *player) {
    switch (ja->state) {
        case JA_WALK:
            move_ja(ja);
            break; 

        case JA_SQUAT:
            squat_ja(ja);
            break;

        case JA_STOP:
            stop_ja(ja);
            break;

        default:
            stop_ja(ja);
            break;
    }
}

//estados em que o ja pode estar
void move_ja(Jet_alone *ja) {
    ja->frame_timer++;
    if (ja->frame_timer > JA_WALK_ANIMATION)
        ja->current_frame = (ja->current_frame + 1)%2;

    if (ja->direction == -1) { // Direita
        if (ja->vx < JA_SPEED) 
            ja->vx += JA_SPEED / 3; // acelera
        else 
            ja->vx = JA_SPEED; //limita a velocidade ao máximo (negativo).
            
    } else { // Esquerda
        if (ja->vx > -JA_SPEED) 
            ja->vx -= JA_SPEED / 3; // acelera
        else 
            ja->vx = -JA_SPEED; //limita a velocidade ao máximo (negativo).
    }    

    ja->x += ja->vx;

    ja->shot_timer++;
    if (ja->shot_timer > JA_SHOT_COOLDOWN)
        ja_buster_fire(ja);
    else
        ja->is_shooting = 0;

}

void squat_ja(Jet_alone *ja) {
    ja->frame_timer++;
    if (ja->frame_timer > JA_SQUAT_ANIMATION && ja->current_frame == 0)
        ja->current_frame = 1;

    ja->shot_timer++;
    if (ja->shot_timer > JA_SHOT_COOLDOWN)
        ja_buster_fire(ja);
    else
        ja->is_shooting = 0;

}

void stop_ja(Jet_alone *ja) {
    ja->shot_timer++;
    if (ja->shot_timer > JA_SHOT_COOLDOWN)
        ja_buster_fire(ja);
    else
        ja->is_shooting = 0;
}

// TIRO
void ja_buster_fire(Jet_alone *ja) {
    ja_bullet *shot = NULL;
    ja->is_shooting = 1;
    //olhando para direita
    if (ja->direction == 1) shot = ja_bullet_create(ja->ja_buster->dificulty, ja->center_x + 0.4*JA_WIDTH, ja->center_y ,ja->direction, ja->ja_buster->shots);
    else if (ja->direction == -1) shot = ja_bullet_create(ja->ja_buster->dificulty, ja->center_x - JA_WIDTH/2, ja->center_y , ja->direction, ja->ja_buster->shots);
    if (shot) ja->ja_buster->shots = shot;

    ja->shot_timer = 0;
}


