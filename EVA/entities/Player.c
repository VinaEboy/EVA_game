#include "Player.h"
#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
// Função para criar o jogador

Player* create_player(float dificulty, int x, int y, int X_SCREEN, int Y_SCREEN) {
    Player *player = malloc(sizeof(Player));
    if (!player) return NULL;

    player->speed = X_SCREEN*0.012; //0.012 é bom
    player->bullet_speed = X_SCREEN*0.02;
    player->jump_strenght = Y_SCREEN*0.07;
    player->gravity = Y_SCREEN*0.005;

    player->height = Y_SCREEN/3; //tem a mesma altura e largura
    player->width = Y_SCREEN/3; 
    player->squat_height = player->height*0.625;
    player->buster = buster_create(dificulty);
    player->x = x; // começa no começo da tela

    // Posiciona o jogador exatamente sobre o chão
    player->y = y;
    player->hit_box_x = player->width*0.98; //o player não é um retangulo perfeito por isso esse fator de ajuste
    player->hit_box_y = player->height*0.98;
    player->center_x = player->x + player->width/2;
    player->center_y = player->y + player->height/2;
    player->vx = 0;
    player->vy = 0;
    player->direction = 1;
    player->is_stopped = 1;
    player->is_on_ground = 1;
    player->is_moving = 0;
    player->is_squat = 0;
    player->is_charging_shot = 0;
    player->is_taking_damage = 0;
    player->damage_timer = 0;
    player->damage_direction = 0;
    player->is_invincible = 0;
    player->charge_shot = 1; // primeiro nivel de carregar o tiro é o nivel 1
    player->timer_charge_shot = 0;
    player->shot = 0;
    player->is_looking_up = 0;

    player->dificulty = dificulty;
    player->life = 100/dificulty;
    player->max_life = 100/dificulty;
    player->death_timer = 0;

    player->current_frame = 0;
    player->frame_timer = 0;
    player->is_dead = 0;

    return player;
}

////////////////////////////////////////////// ANIMATION //////////////////////////////////////////////

// função que muda o estado de animação
void player_set_animation_state(Player *player, PlayerAnimState new_state) {
    // Se a nova animação já for a que está ativa, não precisa mudar
    if (player->current_anim_state == new_state) {
        return;
    }

    player->current_anim_state = new_state;
    player->current_frame = 0; // Resetamos o frame para o início da nova animação

    //caso em que o frame não é por tempo e sim por estar atirando ou não no ar
    if(!player->is_on_ground && player->is_charging_shot) 
        player->current_frame = 1;

    player->frame_timer = 0;   // Reseta o timer 
}

void player_update_state(Player *player, int Y_SCREEN) {
    if (player->y >= Y_SCREEN) player->life = 0;

    if (player->life <= 0) {
        player->death_timer++;
        if (player->death_timer > PLAYER_DEATH_TIME) 
            player->is_dead = 1;
        return;
    } 

    if (player->is_taking_damage) {
        player->damage_timer++;
        if (player->damage_timer == 1) {
            player->vx = PLAYER_PUSHBACK*player->damage_direction;
            player->vy = -15; //para parecer que ele caiu para trás
            player->is_charging_shot = 0; //reseta o carregamento do tiro
            player->charge_shot = 1;
            player->is_moving = 0;
            player->is_squat = 0;
            player->is_stopped = 1;
            player->invincible_timer = 0;
            player->is_invincible = 1; //fica imune a dano por um tempinho
        } else {
            player->vx *= 0.85;
            if (player->damage_timer > DAMAGE_TIME) {
                player->is_taking_damage = 0;
                player->damage_timer = 0;
                player->vx = 0;
            }
        }
    } 

    if (player->is_invincible) {
        player->invincible_timer++;
        if (player->invincible_timer > INVINCIBLE_TIME) {
            player->invincible_timer = 0;
            player->is_invincible = 0;
        }
    }
}

// Atualiza/avança os frames da animação
void player_update_animation(Player *player) {
    player->frame_timer++;

    // Baseado na animação ATUAL, definimos a velocidade e o número de frames.
    switch (player->current_anim_state) {
        
        case ANIM_STOPPED_NO_GUN:
            if (player->frame_timer >= ANIMATION_BLINK_SPEED) { // Animação mais lenta para se mexer parado
                player->current_frame = (player->current_frame + 1) % 2; // Loop entre 2 frames
                player->frame_timer = 0;
            }
            break;
        case ANIM_STOPPED_GUN:
            if (player->is_looking_up) {
                player->current_frame = 2;
                player->frame_timer = ANIMATION_BLINK_SPEED;
            }
            else if (player->frame_timer >= ANIMATION_BLINK_SPEED) { // Animação mais lenta para se mexer parado
                player->current_frame = (player->current_frame + 1) % 2; // Loop entre 2 frames
                player->frame_timer = 0;
            }
            break;

        case ANIM_RUN_GUN:
        case ANIM_RUN_GUN_UP:
        case ANIM_RUN_NO_GUN: // Usa a mesma animação de andar
            if (player->frame_timer >= ANIMATION_RUN_SPEED) {
                player->current_frame = (player->current_frame + 1) % 6; // Loop entre 6 frames
                player->frame_timer = 0;
            }
            break;

        case ANIM_JUMP:
            if (player->is_charging_shot && player->is_looking_up)
                player->current_frame = 2; 
            else if (player->is_charging_shot)
                player->current_frame = 1;    
            else 
                player->current_frame = 0;
            break;

        case ANIM_SQUAT:
           if (player->frame_timer >= ANIMATION_SQUAT_SPEED) { // agachar numa velocidade até que rápido
                if (player->current_frame < 1) player->current_frame = 1; 
                else if (player->is_charging_shot && player->is_looking_up) player->current_frame = 3; //se estiver atirando
                else if (player->is_charging_shot) player->current_frame = 2;
                else player->current_frame = 1; //se não estiver atirando
                player->frame_timer = 0;
            }            
            break;
        case ANIM_JUMP_DAMAGE:
        case ANIM_DAMAGE:
           if (player->frame_timer >= ANIMATION_DAMAGE_SPEED) { // Animação mais lenta para levar dano
                player->current_frame = (player->current_frame + 1) % 2; // Loop entre 2 frames
                player->frame_timer = 0;
            }            
            break;
        case ANIM_DEATH:    
            if (player->frame_timer >= ANIMATION_DEATH_SPEED) {
                player->current_frame = (player->current_frame + 1) % 5;
                player->frame_timer = 0;
            }
    }
}

//também muda hitbox e centro do personagem caso se agache
void update_player_sprite(Player *player) {

    PlayerAnimState desired_state;
    if (player->life <= 0)
        desired_state = ANIM_DEATH;
    else if (!player->is_on_ground) {
        if (player->is_taking_damage)
            desired_state = ANIM_JUMP_DAMAGE;
        else
            desired_state = ANIM_JUMP;
    } else if (player->is_squat) {
        desired_state = ANIM_SQUAT;
    } else if (player->is_moving && player->is_charging_shot) {
        if (player->is_looking_up) 
            desired_state = ANIM_RUN_GUN_UP;
        else
            desired_state = ANIM_RUN_GUN;    
    } else if (player->is_moving && !player->is_charging_shot) {
        desired_state = ANIM_RUN_NO_GUN;
    } else if ( player->is_taking_damage) {
        desired_state = ANIM_DAMAGE;
    } else if (player->is_stopped && player->is_charging_shot) {
        desired_state = ANIM_STOPPED_GUN;
    } else {
        desired_state = ANIM_STOPPED_NO_GUN;
    }

    // muda o estado de frame para o desejado, setando corre
    player_set_animation_state(player, desired_state);

    // atualiza/avança os frames
    player_update_animation(player);
}

void player_sprite(Player *player, ALLEGRO_BITMAP **sprite_sheet, entities_sprites *sprites, int *frames_per_row) {

    switch (player->current_anim_state) {
        
        case ANIM_STOPPED_GUN: // Animação para quando o jogador está parado
            *sprite_sheet = sprites->player_stopped_gun;
            *frames_per_row = 3; // "3 sprites 1 linha"
            break;

        case ANIM_STOPPED_NO_GUN: // Animação para quando o jogador está parado
            *sprite_sheet = sprites->player_stopped_no_gun;
            *frames_per_row = 2; // "2 sprites 1 linha"
            break;


        case ANIM_RUN_NO_GUN: // Andando sem atirar
            *sprite_sheet = sprites->player_run_no_gun;
            *frames_per_row = 3; // "3 sprites em cada uma das 2 linhas"
            break;

        case ANIM_RUN_GUN: // Andando e atirando
            *sprite_sheet = sprites->player_run_gun;
            *frames_per_row = 3; // "3 sprites em cada uma das 2 linhas"
            break;

        case ANIM_RUN_GUN_UP: // Andando e atirando
            *sprite_sheet = sprites->player_run_gun_up;
            *frames_per_row = 3; // "3 sprites em cada uma das 2 linhas"
            break;

        case ANIM_JUMP:
            *sprite_sheet = sprites->player_jump;
            *frames_per_row = 3; // "3 sprites 1 linha"
            break;
            
        case ANIM_SQUAT: // Agachado
            *sprite_sheet = sprites->player_squat;
            *frames_per_row = 4; // "4 sprites 1 linha"
            break;

        case ANIM_DAMAGE: // Recebendo dano
            *sprite_sheet = sprites->player_damage;
            *frames_per_row = 2; // "2 sprites 1 linha"
            break;

        case ANIM_JUMP_DAMAGE:
            *sprite_sheet = sprites->player_jump_damage;
            *frames_per_row = 2;
            break;

        default:
            *sprite_sheet = sprites->player_stopped_no_gun;
            *frames_per_row = 2;
            break;
    }

}


//////////////////////////////////////// POSITION ///////////////////////////////////////////
void player_update_position (Player *player, int num_platforms, Platform **platforms, int level_width) {
    if (player->life <= 0) return;
    // movimento horizontal é travado se estiver agachado
    if (player->is_moving && !player->is_squat) {
        if (player->direction == 1) { // Direita
            if (player->vx < player->speed) 
                player->vx += player->speed / 3; // acelera
            else 
                player->vx = player->speed; //limita a velocidade ao máximo (negativo).
            
        } else { // Esquerda
            if (player->vx > -player->speed) 
                player->vx -= player->speed / 3; // acelera
            else 
                player->vx = -player->speed; //limita a velocidade ao máximo (negativo).
        }
    } 
    
    else {
        // Desaceleração gradual
        player->vx *= 0.85; 
        if (abs(player->vx) < 0.5) 
            player->vx = 0; // Para completamente
        
    }


    // gravidade é uma aceleração
    player->vy += player->gravity;


    // definir a priori a nova posição e se necessário corrigir
    player->x += player->vx;
    player->y += player->vy;

    if(player->x < 0) player->x = 0;
    if (player->x + player->width > level_width) player->x = level_width - player->width;

    // definir a priori que está no ar
    player->is_on_ground = 0;

    
    for (int i = 0; i < num_platforms; i++) {
        Platform *current_platform = platforms[i];
        int status = player_check_collision_with_platform(player, current_platform);
        
        //significa que deu alguma colisão
        if (status != 0) {
            //corrige a posição do jogar se colidir
            player_resolve_collision_with_platform(player, current_platform, status);
        }
    }

    player->center_x = player->x + player->width/2;
    if (!player->is_squat) {
        player->center_y = player->y + player->width/2;
        player->hit_box_y = player->width*0.98;
    }
    else {
        player->center_y = player->y + (player->height - player->squat_height) + (player->squat_height/2); 
        player->hit_box_y = player->squat_height;
    }

}

void update_camera(Player *player, float *camera_x, int X_SCREEN, float level_width) {

    // "zona morta" 
    float dead_zone_left_boundary = *camera_x + X_SCREEN * 0.25;
    float dead_zone_right_boundary = *camera_x + X_SCREEN * 0.50;

    // Calcula o centro da hitbox do jogador no mundo
    float player_center_x = player->x + (player->hit_box_x / 2.0f);

    // Se o jogador ultrapassar a fronteira DIREITA da zona morta
    if (player_center_x > dead_zone_right_boundary) {
        // A câmera se move para manter o jogador na fronteira direita
        *camera_x = player_center_x - (X_SCREEN * 0.50);
    }
    // Se o jogador ultrapassar a fronteira ESQUERDA da zona morta
    else if (player_center_x < dead_zone_left_boundary) {
        // A câmera se move para manter o jogador na fronteira esquerda
        *camera_x = player_center_x - (X_SCREEN * 0.25);
    }
    
    if (*camera_x < 0) {
        *camera_x = 0;
    }
    if (*camera_x > level_width - X_SCREEN) {
        *camera_x = level_width - X_SCREEN;
    }
}



// TIRO
void buster_fire(Player *player, int X_SCREEN, int Y_SCREEN) {
    player->shot = 0;
    
    bullet *shot = NULL;

    if (player->is_looking_up) shot = bullet_create(player->buster->dificulty, player->center_x + player->direction*0.4*player->width, player->center_y - player->width*0.2 , 2, player->buster->shots, player->charge_shot, X_SCREEN, Y_SCREEN);
    else if (player->direction == 1) shot = bullet_create(player->buster->dificulty, player->center_x + 0.4*player->width, player->center_y ,player->direction, player->buster->shots, player->charge_shot, X_SCREEN, Y_SCREEN);
    else if (player->direction == -1) shot = bullet_create(player->buster->dificulty,player->center_x - player->width/2, player->center_y , player->direction, player->buster->shots, player->charge_shot, X_SCREEN, Y_SCREEN);
    if (shot) player->buster->shots = shot;

    player->charge_shot = 1;
    player->timer_charge_shot = 0;
}

void player_destroy(Player *player) {
    buster_destroy(player->buster);
    free(player);
}


