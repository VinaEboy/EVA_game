#include "Player.h"
#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
// Função para criar o jogador

Player* create_player(float dificulty, int Y_SCREEN, float FLOOR_height) {
    Player *player = malloc(sizeof(Player));
    if (!player) return NULL;

    player->buster = buster_create(dificulty);
    player->x = 0; // começa no começo da tela

    // Posiciona o jogador exatamente sobre o chão
    player->y = Y_SCREEN - FLOOR_height - EVA_HEIGHT;
    player->hit_box_x = EVA_WIDTH*0.98; //o player não é um retangulo perfeito por isso esse fator de ajuste
    player->hit_boy_y = EVA_HEIGHT*0.98;
    player->center_x = player->x + EVA_WIDTH/2;
    player->center_y = player->y + EVA_HEIGHT/2;
    player->vx = 0;
    player->vy = 0;
    player->direction = 1;
    player->is_stopped = 1;
    player->is_on_ground = 1;
    player->is_moving = 0;
    player->is_squat = 0;
    player->is_charging_shot = 0;
    player->is_taking_damage = 0;
    player->charge_shot = 0;
    player->timer_charge_shot = 0;
    player->shot = 0;

    player->dificulty = dificulty;
    player->life = 100*(1/dificulty);

    player->current_frame = 0;
    player->frame_timer = 0;


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

// Atualiza/avança os frames da animação
void player_update_animation(Player *player) {
    player->frame_timer++;

    // Baseado na animação ATUAL, definimos a velocidade e o número de frames.
    switch (player->current_anim_state) {
        
        case ANIM_STOPPED_GUN:
        case ANIM_STOPPED_NO_GUN:
            if (player->frame_timer >= ANIMATION_BLINK_SPEED) { // Animação mais lenta para se mexer parado
                player->current_frame = (player->current_frame + 1) % 2; // Loop entre 2 frames
                player->frame_timer = 0;
            }
            break;

        case ANIM_RUN_GUN:
        case ANIM_RUN_NO_GUN: // Usa a mesma animação de andar
            if (player->frame_timer >= ANIMATION_RUN_SPEED) {
                player->current_frame = (player->current_frame + 1) % 6; // Loop entre 6 frames
                player->frame_timer = 0;
            }
            break;

        case ANIM_JUMP:
            if (player->is_charging_shot)
                player->current_frame = 1; 
            else 
                player->current_frame = 0;    
            break;

        case ANIM_SQUAT:
           if (player->frame_timer >= ANIMATION_SQUAT_SPEED) { // agachar numa velocidade até que rápido
                if (player->current_frame < 1) player->current_frame++; 
                else if (player->is_charging_shot) player->current_frame = 3; //se estiver atirando
                else player->current_frame = 2; //se não estiver atirando
                player->frame_timer = 0;
            }            
            break;
        case ANIM_DAMAGE:
           if (player->frame_timer >= ANIMATION_DAMAGE_SPEED) { // Animação mais lenta para levar dano
                player->current_frame = (player->current_frame + 1) % 2; // Loop entre 2 frames
                player->frame_timer = 0;
            }            
            break;
    }
}

//também muda hitbox e centro do personagem caso se agache
void update_player_sprite(Player *player) {
    player->hit_boy_y = EVA_HEIGHT*0.98;
    player->center_y = player->y + EVA_HEIGHT/2;

    PlayerAnimState desired_state;
    if (!player->is_on_ground) {
        desired_state = ANIM_JUMP;
    } else if (player->is_squat) {
        player->hit_boy_y = EVA_HEIGHT*0.7;
        player->center_y = player->y + 0.65*EVA_HEIGHT;
        desired_state = ANIM_SQUAT;
    } else if (player->is_moving && player->is_charging_shot) {
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
            *frames_per_row = 2; // "2 sprites 1 linha"
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

        case ANIM_JUMP:
            *sprite_sheet = sprites->player_jump;
            *frames_per_row = 2; // "2 sprites 1 linha"
            break;
            
        case ANIM_SQUAT: // Agachado
            *sprite_sheet = sprites->player_squat;
            *frames_per_row = 4; // "3 sprites 1 linha"
            break;

        case ANIM_DAMAGE: // Recebendo dano
            *sprite_sheet = sprites->player_damage;
            *frames_per_row = 2; // "2 sprites 1 linha"
            break;

        // Caso padrão para evitar erros se um estado inesperado for definido.
        // Geralmente é bom definir para a animação de 'parado'.
        default:
            *sprite_sheet = sprites->player_stopped_no_gun;
            *frames_per_row = 2;
            break;
    }

}


//////////////////////////////////////// POSITION ///////////////////////////////////////////
void player_update_position (Player *player, int num_platforms, Platform *platforms) {

    // movimento horizontal é travado se estiver agachado
    if (player->is_moving && !player->is_squat) {
        if (player->direction == 1) { // Direita
            if (player->vx < PLAYER_SPEED) 
                player->vx += PLAYER_SPEED / 3; // acelera
            else 
                player->vx = PLAYER_SPEED; //limita a velocidade ao máximo (negativo).
            
        } else { // Esquerda
            if (player->vx > -PLAYER_SPEED) 
                player->vx -= PLAYER_SPEED / 3; // acelera
            else 
                player->vx = -PLAYER_SPEED; //limita a velocidade ao máximo (negativo).
        }
    } 
    
    else {
        // Desaceleração gradual
        player->vx *= 0.85; 
        if (abs(player->vx) < 0.5) 
            player->vx = 0; // Para completamente
        
    }


    // gravidade é uma aceleração
    player->vy += GRAVITY;


    // definir a priori a nova posição e se necessário corrigir
    player->x += player->vx;
    player->y += player->vy;

    if(player->x < 0) player->x = 0;
    if (player->x + EVA_WIDTH > 8000) player->x = 8000 - EVA_WIDTH;

    // definir a priori que está no ar
    player->is_on_ground = 0;

    for (int i = 0; i < num_platforms; i++) {
        Platform current_platform = platforms[i];
        int status = check_collision_with_platform(player, current_platform);
        
        //significa que deu alguma colisão
        if (status != 0) {
            //corrige a posição do jogar se colidir
            resolve_collision_with_platform(player, current_platform, status);
            break; 
        }
    }

    player->center_x = player->x + EVA_WIDTH/2;
    if (!player->is_squat)
        player->center_y = player->y + EVA_WIDTH/2;
    else
        player->center_y = player->y + 1.05*EVA_WIDTH/2; //ainda não decidi o valor que multiplica aqui

}

void update_camera(Player *player, float *camera_x, int X_SCREEN) {

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
    
    // Opcional: Trava a câmera nos limites da fase
    int level_width = 8000; // Largura total da sua fase
    if (*camera_x < 0) {
        *camera_x = 0;
    }
    if (*camera_x > level_width - X_SCREEN) {
        *camera_x = level_width - X_SCREEN;
    }
}



// TIRO
void buster_fire(Player *player) {
    player->shot = 0;
    if (player->charge_shot == 0)
        buster_fire_1(player);
    else if (player->charge_shot == 1)
        buster_fire_2(player);
    else if (player->charge_shot == 2)
        buster_fire_3(player);
    player->charge_shot = 0;
    player->timer_charge_shot = 0;
}

void buster_fire_1(Player *player) {
    bullet_1 *shot = NULL;

    //olhando para direita
    if (player->direction == 1) shot = bullet_1_create(player->buster->dificulty, player->center_x + 0.4*EVA_WIDTH, player->center_y ,player->direction, player->buster->shots_1);
    else if (player->direction == -1) shot = bullet_1_create(player->buster->dificulty,player->center_x - EVA_WIDTH/2, player->center_y , player->direction, player->buster->shots_1);
    if (shot) player->buster->shots_1 = shot;
}

void buster_fire_2(Player *player) {
    bullet_2 *shot = NULL;

    //olhando para direita
    if (player->direction == 1) shot = bullet_2_create(player->buster->dificulty,player->center_x + 0.4*EVA_WIDTH, player->center_y, player->direction, player->buster->shots_2);
    else if (player->direction == -1) shot = bullet_2_create(player->buster->dificulty,player->center_x - EVA_WIDTH/2, player->center_y, player->direction, player->buster->shots_2);
    if (shot) player->buster->shots_2 = shot;
}

void buster_fire_3(Player *player) {
    bullet_3 *shot = NULL;

    //olhando para direita
    if (player->direction == 1) shot = bullet_3_create(player->buster->dificulty,player->center_x + 0.4*EVA_WIDTH, player->center_y, player->direction, player->buster->shots_3);
    else if (player->direction == -1) shot = bullet_3_create(player->buster->dificulty,player->center_x - EVA_WIDTH/2, player->center_y, player->direction, player->buster->shots_3);
    if (shot) player->buster->shots_3 = shot;

}


/// COLISOES

int check_collision_with_platform(Player *player, Platform platform) {
    //a priori não colidiu
    int status = 0;

    // colisão vertical com plataforma
    if (player->y + EVA_HEIGHT >= platform.y)
        status = 1;
    
    return status;
}


// só resolve uma colisão por enquanto
void resolve_collision_with_platform(Player *player, Platform platform, int status) {
    
    //colidiu com a plataforma verticalmente
    if (status == 1) {
        player->y = platform.y - EVA_HEIGHT;
        player->vy = 0;
        player->is_on_ground = 1;
    }
}



