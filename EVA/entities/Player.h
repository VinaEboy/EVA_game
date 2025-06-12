// Player.h
#ifndef __PLAYER_H__
#define __PLAYER_H__

// Constantes da física e movimento do jogador
// FAZER PROPORCIONAL A TELA ??
#define PLAYER_SPEED 10.0
#define PLAYER_JUMP_STRENGTH 40.0
#define GRAVITY 2.0
#define ANIMATION_RUN_SPEED 5 
#define ANIMATION_BLINK_SPEED 40
#define ANIMATION_SQUAT_SPEED 2
#define ANIMATION_DAMAGE_SPEED 10

#define CHARGE_BLINK_SPEED 9
// Dimensões do frame do player
#define EVA_WIDTH 256
#define EVA_HEIGHT 256

#include "../mechanics/Objects.h"
#include <allegro5/allegro_image.h>
#include <allegro5/allegro5.h>																																												
#include "../gameflow/Assets.h"
#include "Buster.h"

typedef enum {
    ANIM_STOPPED_GUN,          // Parado (usa o sprite player_stopped)
    ANIM_STOPPED_NO_GUN, //parado com a mão apontando
    ANIM_RUN_GUN,       // Andando
    ANIM_RUN_NO_GUN, // Andando e atirando
    ANIM_JUMP,       // Pulando ou caindo
    ANIM_SQUAT,     // Agachado (usa o sprite player_squat)
    ANIM_DAMAGE,         // Recebendo dano (usa o sprite player_damage)
} PlayerAnimState;


typedef struct Player {
    buster_t *buster; // é a "pistol"

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
    unsigned char is_taking_damage; //jogador sofre recall e não pode atirar se levar dano
    unsigned char shot; //fala se ele atirou, ou seja, se precisar criar uma entidade tiro
    int charge_shot; //o quão carregado o tiro está
    int timer_charge_shot;

    //status 
    float life;

    // Animação
    PlayerAnimState current_anim_state; // <<< NOVO: Guarda a animação ativa
    int current_frame;      // O frame atual da animação (0 a 5)
    int frame_timer;        // Um contador para controlar a velocidade da animação
} Player;

Player* create_player(int Y_SCREEN, float FLOOR);

// ANIMATION

// A função que vai gerenciar a troca de animações 
void player_set_animation_state(Player *player, PlayerAnimState new_state);

// A função que vai avançar os frames da animação ativa 
void player_update_animation(Player *player);

void update_player_sprite(Player *player);

void player_sprite(Player *player, ALLEGRO_BITMAP **sprite_sheet, entities_sprites *sprites, int *frames_per_row);

// POSITION

void player_update_position (Player *player, int num_platforms, Platform *platforms);

void update_camera(Player *player, float *camera_x, int X_SCREEN);


// tiro
void buster_fire(Player *player);
void buster_fire_1(Player *player);
void buster_fire_2(Player *player);
void buster_fire_3(Player *player);

// colisoes
void resolve_collision_with_platform(Player *player, Platform platform, int status);
int check_collision_with_platform(Player *player, Platform platform);

// aux math
int abs(int x);


#endif