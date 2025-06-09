// Player.h
#ifndef __PLAYER_H__
#define __PLAYER_H__

// Constantes da física e movimento do jogador
// FAZER PROPORCIONAL A TELA ??
#define PLAYER_SPEED 10.0
#define PLAYER_JUMP_STRENGTH 40.0
#define GRAVITY 2.0
#define ANIMATION_SPEED 5 // Mude para acelerar/desacelerar a animação (maior = mais lento)

// Dimensões de cada frame do sprite
#define FRAME_WIDTH 256
#define FRAME_HEIGHT 256

#include "../mechanics/Objects.h"
#include <math.h>

// <<< NOVO: Definimos todos os possíveis estados de animação do jogador >>>
typedef enum {
    ANIM_IDLE,          // Parado, balançando
    ANIM_WALKING,       // Andando
    ANIM_WALKING_SHOOT, // Andando e atirando
    ANIM_JUMPING,       // Pulando ou caindo
    ANIM_CROUCHING,     // Agachado
    ANIM_STAND_SHOOT    // Parado e atirando
} PlayerAnimState;


typedef struct Player {
    float x, y;             // Posição na tela/mundo
    float hit_box_x, hit_boy_y; //hitbox muda se estiver de pé ou agachado
    float center_x, center_y; //centro do personagem
    float vx, vy;           // Velocidade nos eixos x e y
    int direction;          // Direção que está olhando (-1 para esquerda, 1 para direita)
    unsigned char is_stopped; // saber se está parado para fazer redução de velocidade
    unsigned char is_on_ground;        // Flag para saber se está no ar
    unsigned char is_moving;         // Flag para saber se está se movendo
    unsigned char is_squat;
    unsigned char is_charging_shot;
    unsigned char shot; //fala se ele atirou, ou seja, se precisar criar uma entidade tiro
    int charge_shot; //o quão carregado o tiro está

    //status 
    float life;

    // Animação
    PlayerAnimState current_anim_state; // <<< NOVO: Guarda a animação ativa
    int current_frame;      // O frame atual da animação (0 a 5)
    int frame_timer;        // Um contador para controlar a velocidade da animação
} Player;

Player* create_player(int Y_SCREEN, float FLOOR);

// <<< NOVO: A função "cérebro" que vai gerenciar a troca de animações >>>
void player_set_animation_state(Player *player, PlayerAnimState new_state);

// <<< NOVO: A função que vai avançar os frames da animação ativa >>>
void player_update_animation(Player *player);

void update_player_sprite(Player *player);


void player_update_position (Player *player, int num_platforms, Platform *platforms);

void update_camera(Player *player, float *camera_x, int X_SCREEN);


// colisoes

void resolve_collision_with_platform(Player *player, Platform platform);
unsigned char check_collision_with_platform(Player *player, Platform platform);

#endif