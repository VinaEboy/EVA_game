#include "Jet_alone.h"
#include <stdlib.h> // Para rand() e srand()
#include <time.h>   // Para time()
#include <math.h>

Jet_alone *ja_create(float dificulty, float squat_probability, float x, float y, int direction, float distance_to_player, int X_SCREEN, int Y_SCREEN) {
    Jet_alone *ja = (Jet_alone *)malloc(sizeof(Jet_alone));
    if (!ja) return NULL;
  
    ja->speed = X_SCREEN*0.005;
    ja->bullet_speed = X_SCREEN*0.02;
    ja->gravity = Y_SCREEN*0.005;

    ja->life = 100*dificulty;
    ja->damage = 20*dificulty;
    ja->dead = 0;
    ja->distance_to_player = distance_to_player;
    ja->is_platform_left_edge = 0;
    ja->is_platform_right_edge = 0;
    ja->is_on_ground = 1;
    ja->is_taking_damage = 0;
    
    ja->height = Y_SCREEN/2;
    ja->width = Y_SCREEN/2;
    ja->squat_height = ja->height*0.56;

    ja->x = x, 
    ja->y = y;
    ja->center_x = x + ja->width/2;
    ja->center_y = y + ja->height/2;
    ja->hit_box_x = 0.4*ja->width;
    ja->hit_box_y = 0.98*ja->height;

    ja->direction = direction;

    ja->hit_take = 0;
    ja->hit_take_timer = 0;

    ja->state = JA_STOP;
    ja->state_timer = 0;
    ja->current_frame = 0;
    ja->frame_timer = 0;
    ja->squat_probability = squat_probability;

    ja->arm_up_timer = 0;
    ja->ja_buster = ja_buster_create(dificulty, ja->bullet_speed);
    ja->shot_timer = 0;
    ja->is_shooting = 0;

    return ja;
}

void update_ja(Jet_alone *ja, float camera_x, Player *player, int X_SCREEN, int Y_SCREEN) {

    update_state_ja(ja, camera_x, player, X_SCREEN);
    action_ja(ja,player, X_SCREEN, Y_SCREEN);

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

void update_ja_position (Jet_alone *ja, int num_platforms, Platform **platforms, int level_width) {

    
    int ja_ledge_status = ja_check_for_ledge(ja, platforms, num_platforms);
    if (ja_ledge_status == 0) {
        ja->is_platform_left_edge = 0;
        ja->is_platform_right_edge = 0; 
    } else if (ja_ledge_status == 1) {
        ja->is_platform_left_edge = 1;
        ja->is_platform_right_edge = 0; 
    } else {
        ja->is_platform_left_edge = 0;
        ja->is_platform_right_edge = 1;
    }


    if ( (ja->is_platform_left_edge && ja->direction == 1) || (ja->is_platform_right_edge && ja->direction == -1))
        ja->vx = 0;


    ja->vy += ja->gravity;


    // definir a priori a nova posição e se necessário corrigir
    ja->x += ja->vx;
    ja->y += ja->vy;

    if(ja->x < 0) ja->x = 0;
    if (ja->x + ja->width > level_width) ja->x = level_width - ja->width;

    // definir a priori que está no ar
    ja->is_on_ground = 0;

    
    for (int i = 0; i < num_platforms; i++) {
        Platform *current_platform = platforms[i];
        int status = ja_check_collision_with_platform(ja, current_platform);
        
        //significa que deu alguma colisão
        if (status != 0) {
            //corrige a posição do jogar se colidir
            ja_resolve_collision_with_platform(ja, current_platform, status);
        }
    }


    ja->center_x = ja->x + ja->width/2;
    if (!ja->is_squat)
        ja->center_y = ja->y + ja->width/2;
    else
        ja->center_y = ja->y + (ja->width - ja->squat_height) + (ja->squat_height/2); 
}

//atualiza o estado do jet alone e caso necessário faz ele virar a direção
void update_state_ja(Jet_alone *ja, float camera_x, Player *player, int X_SCREEN) {
    ja->state_timer++;

    //lógica para caso o player passe pelo inimigo, o inimigo virar de direção
    if (ja->direction == -1 && (ja->x + JA_FLIP_DISTANCE < player->x))
        ja->direction = 1;
    else if (ja->direction == 1 && (player->x + JA_FLIP_DISTANCE < ja->x))
        ja->direction = -1;

    // Lógica corrigida para o inimigo perseguir
    unsigned char is_visible = (ja->x + ja->width > camera_x) && (ja->x < camera_x + X_SCREEN);
    float ja_distance = abs(ja->x - player->x); 
    unsigned char abys_fall = ( (ja->is_platform_left_edge && ja->direction == 1) || (ja->is_platform_right_edge && ja->direction == -1));

    if ( (!is_visible || ja_distance > ja->distance_to_player ) && !abys_fall) { 
        ja->state = JA_WALK; 
        ja->center_x = ja->x + ja->width/2;
        ja->hit_box_y = 0.98*ja->height;
        ja->center_y = ja->y + ja->width/2;
        return; 
    }

    ja->vx = 0; //porque não está andando

    if(ja->state == JA_WALK) //significa que estava andando e chegou perto o suficiente, já pode tomar uma escolha
        ja->state_timer = JA_STATE_TIMER + 1;

    //tomada de escolha
    if (ja->state_timer > JA_STATE_TIMER) {
        ja->state_timer = 0;

        //se o jogador estiver agachado aumenta a chance do bot agachar
        float squat_prob = ja->squat_probability;
        if (player->is_squat)
            squat_prob *= 2;

        if ( (float)(rand() % 101) / 100 < squat_prob )
            ja->state = JA_SQUAT;
        else
            ja->state = JA_STOP;
    }

    ja->center_x = ja->x + ja->width/2;
    if (ja->state == JA_SQUAT) {
        ja->hit_box_y = 0.7*ja->height; //a hitbox diminui
        ja->center_y = ja->y + 1.5*ja->width/2;
    } else {
        ja->hit_box_y = 0.98*ja->height;
        ja->center_y = ja->y + ja->width/2;
    }

}

void action_ja(Jet_alone *ja, Player *player, int X_SCREEN, int Y_SCREEN) {
    switch (ja->state) {
        case JA_WALK:
            move_ja(ja, X_SCREEN, Y_SCREEN);
            break; 

        case JA_SQUAT:
            squat_ja(ja, X_SCREEN, Y_SCREEN);
            break;

        case JA_STOP:
            stop_ja(ja, X_SCREEN, Y_SCREEN);
            break;

        default:
            stop_ja(ja, X_SCREEN, Y_SCREEN);
            break;
    }
}

//estados em que o ja pode estar
void move_ja(Jet_alone *ja, int X_SCREEN, int Y_SCREEN) {
    ja->frame_timer++;
    if (ja->frame_timer > JA_WALK_ANIMATION) {
        ja->current_frame = (ja->current_frame + 1)%2;
        ja->frame_timer = 0;
    }

    if (ja->direction == 1) { // Direita
        if (ja->vx < ja->speed) 
            ja->vx += ja->speed / 3; // acelera
        else 
            ja->vx = ja->speed; //limita a velocidade ao máximo (negativo).
            
    } else { // Esquerda
        if (ja->vx > -ja->speed) 
            ja->vx -= ja->speed / 3; // acelera
        else 
            ja->vx = -ja->speed; //limita a velocidade ao máximo (negativo).
    }    

    ja->shot_timer++;
    if (ja->shot_timer > JA_SHOT_COOLDOWN)
        ja_buster_fire(ja, X_SCREEN, Y_SCREEN);
    else {
        ja->arm_up_timer++;
        if (ja->arm_up_timer > JA_ARM_UP_TIME) {
            ja->is_shooting = 0;
            ja->arm_up_timer = 0;
        }
    }

}

void squat_ja(Jet_alone *ja, int X_SCREEN, int Y_SCREEN) {
    ja->frame_timer++;
    if (ja->frame_timer > JA_SQUAT_ANIMATION && ja->current_frame == 0)
        ja->current_frame = 1;

    ja->shot_timer++;
    if (ja->shot_timer > JA_SHOT_COOLDOWN)
        ja_buster_fire(ja, X_SCREEN, Y_SCREEN);
    else
        ja->is_shooting = 0;

}

void stop_ja(Jet_alone *ja, int X_SCREEN, int Y_SCREEN) {
    ja->shot_timer++;
    if (ja->shot_timer > JA_SHOT_COOLDOWN) 
        ja_buster_fire(ja, X_SCREEN, Y_SCREEN);
    else {
        ja->arm_up_timer++;
        if (ja->arm_up_timer > JA_ARM_UP_TIME) {
            ja->is_shooting = 0;
            ja->arm_up_timer = 0;
        }
    }

    if (ja->is_shooting) ja->current_frame = 1;
    else ja->current_frame = 0;
}

// TIRO
void ja_buster_fire(Jet_alone *ja, int X_SCREEN, int Y_SCREEN) {
    ja_bullet *shot = NULL;
    ja->is_shooting = 1;
    //olhando para direita
    if (ja->direction == 1) shot = ja_bullet_create(ja->ja_buster->dificulty, ja->bullet_speed, ja->center_x + ja->width/2.7, ja->center_y - ja->height/5,ja->direction, ja->ja_buster->shots, X_SCREEN, Y_SCREEN);
    else if (ja->direction == -1) shot = ja_bullet_create(ja->ja_buster->dificulty, ja->bullet_speed, ja->center_x - ja->width/2.7, ja->center_y - ja->height/5 , ja->direction, ja->ja_buster->shots, X_SCREEN, Y_SCREEN);
    if (shot) ja->ja_buster->shots = shot;

    ja->shot_timer = 0;
}

// AUX
//retorna 0 se não estiver em beirada
//retorna 1 se estiver na beirada esquerda
//retorna 2 se estiver na beirada da direita
// Nao trata dos casos em que ele está na beirada das duas ao mesmo tempo, ou seja,
// uma plataforma muito pequena de largura
int ja_check_for_ledge(struct Jet_alone *ja, Platform **platforms, int num_platforms) {
    // Se o inimigo não está no chão, ele não pode estar na beirada (já está caindo).
    if (!ja->is_on_ground) {
        return 0;
    }

    // Ponto Y da sonda: um pixel abaixo dos pés do inimigo.
    float probe_y = ja->y + ja->height + 1;

    // Ponto X da sonda: depende da direção que o inimigo está se movendo.
    float probe_x;
    if (ja->vx > 0) { // Movendo para a direita
        // Sonda fica um pixel à frente da borda direita do inimigo.
        probe_x = ja->center_x + ja->hit_box_x/2 + 1;
    } else if (ja->vx < 0) { // Movendo para a esquerda
        // Sonda fica um pixel à frente da borda esquerda do inimigo.
        probe_x = ja->center_x - ja->hit_box_x/2 - 1;
    } else {
        // Se está parado a informação que eu já tenho está certo
        if (ja->is_platform_left_edge) return 1;
        if (ja->is_platform_right_edge) return 2;
        return 0;
    }

    // Agora, verificamos se o ponto (probe_x, probe_y) está dentro de ALGUMA plataforma.
    for (int i = 0; i < num_platforms; i++) {
        Platform *p = platforms[i];
        // Checa se o ponto da sonda está dentro dos limites da plataforma atual.
        if (probe_x >= p->x && probe_x <= (p->x + p->width) &&
            probe_y >= p->y && probe_y <= (p->y + p->height))
        {
            // Encontramos chão à frente! Não é uma beirada.
            return 0;
        }
    }

    // Se o loop terminou e não encontrou nenhuma plataforma sob a sonda,
    // significa que há um abismo à frente.
    if (ja->vx > 0) return 1;
    return 2;
}

void ja_destroy(struct Jet_alone *ja) {
    ja_buster_destroy(ja->ja_buster);
    free(ja);
}


