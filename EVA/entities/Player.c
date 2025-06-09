#include "Player.h"
#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

// Função para criar o jogador

Player* create_player(int Y_SCREEN, float FLOOR_height) {
    Player *player = malloc(sizeof(Player));
    if (!player) return NULL;

    player->x = 0; // começa no começo da tela

    // Posiciona o jogador exatamente sobre o chão
    player->y = Y_SCREEN - FLOOR_height - FRAME_HEIGHT;
    player->hit_box_x = FRAME_WIDTH*0.98/2; //o player não é um retangulo perfeito por isso esse fator de ajuste
    player->hit_boy_y = FRAME_HEIGHT*0.98/2;
    player->center_x = FRAME_WIDTH/2;
    player->center_y = FRAME_HEIGHT/2;
    player->vx = 0;
    player->vy = 0;
    player->direction = 1;
    player->is_stopped = 1;
    player->is_on_ground = 1;
    player->is_moving = 0;
    player->is_squat = 0;
    player->is_charging_shot = 0;
    player->charge_shot = 0;
    player->shot = 0;

    player->life = 100;

    player->current_frame = 0;
    player->frame_timer = 0;


    return player;
}

// Esta é a função mais importante.
// Ela é a única que deve mudar o estado da animação.
void player_set_animation_state(Player *player, PlayerAnimState new_state) {
    // Se a nova animação já for a que está ativa, não fazemos nada.
    // Isso impede que a animação seja resetada a cada quadro.
    if (player->current_anim_state == new_state) {
        return;
    }

    // A animação mudou!
    player->current_anim_state = new_state;
    player->current_frame = 0; // Resetamos o frame para o início da nova animação
    player->frame_timer = 0;   // Resetamos o timer também
}

// Esta função avança os frames da animação que está ativa.
void player_update_animation(Player *player) {
    player->frame_timer++;

    // Baseado na animação ATUAL, definimos a velocidade e o número de frames.
    switch (player->current_anim_state) {
        
        case ANIM_IDLE:
            if (player->frame_timer >= 20) { // Animação mais lenta para o idle
                player->current_frame = (player->current_frame + 1) % 2; // Loop entre 2 frames
                player->frame_timer = 0;
            }
            break;

        case ANIM_WALKING:
        case ANIM_WALKING_SHOOT: // Usa a mesma animação de andar
            if (player->frame_timer >= ANIMATION_SPEED) {
                player->current_frame = (player->current_frame + 1) % 6; // Loop entre 6 frames
                player->frame_timer = 0;
            }
            break;

        case ANIM_JUMPING:
            // Para o pulo, geralmente ficamos em um frame só.
            // Aqui poderíamos ter uma lógica para frame de subida e de queda.
            // Por enquanto, vamos deixar no primeiro frame.
            player->current_frame = 0; 
            break;

        case ANIM_CROUCHING:
        case ANIM_STAND_SHOOT:
             // Animações de um frame só, não precisam de update.
            player->current_frame = 0;
            break;
    }
}

void update_player_sprite(Player *player) {
    PlayerAnimState desired_state;
    if (!player->is_on_ground) {
        desired_state = ANIM_JUMPING;
    } else if (player->is_squat) {
        desired_state = ANIM_CROUCHING;
    } else if (player->is_moving) {
        desired_state = player->is_charging_shot ? ANIM_WALKING_SHOOT : ANIM_WALKING;
    } else {
        desired_state = player->is_charging_shot ? ANIM_STAND_SHOOT : ANIM_IDLE;
    }

    // <<< NOVO: A função "cérebro" que vai gerenciar a troca de animações >>>
    player_set_animation_state(player, desired_state);

    // <<< NOVO: A função que vai avançar os frames da animação ativa >>>
    player_update_animation(player);
}

void player_update_position (Player *player, int num_platforms, Platform *platforms) {

    // --- LÓGICA DE FÍSICA HORIZONTAL ---
    if (player->is_moving && !player->is_squat) {
        if (player->direction == 1) { // Direita
            // Se a velocidade ainda não atingiu o máximo, acelera.
            if (player->vx < PLAYER_SPEED) {
                player->vx += PLAYER_SPEED / 3;
            } 
            // Senão, limita a velocidade ao máximo.
            else {
                player->vx = PLAYER_SPEED;
            }
        } else { // Esquerda
            // Se a velocidade ainda não atingiu o máximo (negativo), acelera.
            if (player->vx > -PLAYER_SPEED) {
                player->vx -= PLAYER_SPEED / 3;
            }
            // Senão, limita a velocidade ao máximo (negativo).
            else {
                player->vx = -PLAYER_SPEED;
            }
        }
    } 
    
    else {
        // Desaceleração (fricção)
        player->vx *= 0.85; // Use um valor constante para a fricção
        if (fabs(player->vx) < 0.5) 
            player->vx = 0; // Para completamente
        
    }


    // --- LÓGICA DE FÍSICA VERTICAL ---
    player->vy += GRAVITY;


    // --- ATUALIZAÇÃO FINAL DA POSIÇÃO ---
    player->x += player->vx;
    player->y += player->vy;

    // Antes de checar, assumimos que o jogador está no ar.
    // Se encontrarmos uma colisão, mudaremos isso.
    player->is_on_ground = 0;
    // Itera por cada plataforma definida na fase.
    for (int i = 0; i < num_platforms; i++) {
        Platform current_platform = platforms[i];
        // Se uma colisão de pouso for detectada...
        if (check_collision_with_platform(player, current_platform)) {
            // ...resolvemos a colisão.
            resolve_collision_with_platform(player, current_platform);
            break; 
        }
    }

}

void update_camera(Player *player, float *camera_x, int X_SCREEN) {

    // Define os limites da "zona morta" como porcentagens da tela
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


/// COLISOES

unsigned char check_collision_with_platform(Player *player, Platform platform) {


    // --- CONDIÇÃO 2: CHECAGEM VERTICAL (PARA POUSO) ---
    // A base do jogador (player->y + FRAME_HEIGHT) deve estar abaixo ou na mesma linha
    // da superfície da plataforma (platform.y).
    unsigned char vertical_position = (player->y + FRAME_HEIGHT >= platform.y);

    // --- CONDIÇÃO 3: DIREÇÃO DO MOVIMENTO ---
    // O jogador deve estar se movendo para baixo (ou estar parado verticalmente).
    // Isso impede que a colisão seja detectada quando ele está pulando POR BAIXO da plataforma.
    unsigned char is_falling = (player->vy >= 0);

    // --- CONDIÇÃO BÔNUS: Evitar "grudar" na plataforma pelo lado ---
    // Verificamos se, no *quadro anterior*, a base do jogador estava ACIMA da plataforma.
    // Isso garante que a colisão só seja detectada no exato momento do pouso.
    // (player->y - player->vy) nos dá a posição Y aproximada do quadro anterior.
    unsigned char was_above = ((player->y - player->vy) + FRAME_HEIGHT <= platform.y);
    

    return  vertical_position && is_falling && was_above;

}


// só resolve verticalmente, se colar horizontalmente o personagem vai para cima da plataforma
void resolve_collision_with_platform(Player *player, Platform platform) {
    
    player->y = platform.y - FRAME_HEIGHT;

    player->vy = 0;
    player->is_on_ground = 1;
}
