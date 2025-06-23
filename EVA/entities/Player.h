// Player.h
#ifndef __PLAYER_H__
#define __PLAYER_H__


#define ANIMATION_RUN_SPEED 5 
#define ANIMATION_BLINK_SPEED 40
#define ANIMATION_SQUAT_SPEED 2
#define ANIMATION_DAMAGE_SPEED 10
#define ANIMATION_DEATH_SPEED 3

#define CHARGE_BLINK_SPEED 9
// Dimensões do frame do player
#define PLAYER_PUSHBACK 20
#define DAMAGE_TIME 10
#define INVINCIBLE_TIME 75
#define PLAYER_DEATH_FRAME_WIDTH 256
#define PLAYER_DEATH_FRAME_HEIGHT 256
#define PLAYER_DEATH_TIME 60

#include "../mechanics/Objects.h"
#include <allegro5/allegro_image.h>
#include <allegro5/allegro5.h>																																												
#include "../gameflow/Assets.h"
#include "Buster.h"
#include "../mechanics/Collisions.h" 
#include <math.h>

typedef enum {
    ANIM_STOPPED_GUN,          
    ANIM_STOPPED_NO_GUN, 
    ANIM_RUN_GUN,       
    ANIM_RUN_NO_GUN, 
    ANIM_JUMP,       
    ANIM_SQUAT,     
    ANIM_DAMAGE,       
    ANIM_JUMP_DAMAGE, 
    ANIM_DEATH,
    ANIM_RUN_GUN_UP,
} PlayerAnimState;


typedef struct Player {
    buster_t *buster; // é a "pistol"

    float jump_strenght;
    float gravity;
    float speed, bullet_speed;
    float height, width;
    float squat_height;
    float x, y;            
    float hit_box_x, hit_box_y; //hitbox muda se estiver de pé ou agachado
    float center_x, center_y; //centro 
    float vx, vy;           
    int direction;          // Direção que está olhando (-1 para esquerda, 1 para direita)
    unsigned char is_stopped; // saber se está parado para fazer redução de velocidade
    unsigned char is_on_ground;        // Flag para saber se está no ar
    unsigned char is_moving;         // Flag para saber se está se movendo
    unsigned char is_squat;
    unsigned char is_charging_shot;
    unsigned char is_taking_damage; //jogador sofre recall e não pode atirar se levar dano
    int damage_direction; //se ele sofreu dano esse dano tem alguma direção de onde veio, o jogador vai ser jogado para essa direção
    int damage_timer;
    unsigned char is_invincible; //quando ele toma dano ele fica invencivel por alguns segundos pro jogador se reposicionar
    int invincible_timer;
    unsigned char shot; //fala se ele atirou, ou seja, se precisar criar uma entidade tiro
    int charge_shot; //o quão carregado o tiro está
    int timer_charge_shot;
    unsigned char is_dead;
    unsigned char is_looking_up;

    float dificulty;
    //status 
    float life;
    float max_life;
    int death_timer;

    // Animação
    PlayerAnimState current_anim_state; // Guarda a animação ativa
    int current_frame;      // O frame atual da animação 
    int frame_timer;        
} Player;

// Função para criar o jogador
Player* create_player(float dificulty, int x, int y, int X_SCREEN, int Y_SCREEN);

//atualiza o estado do jogador
void player_update_state(Player *player, int Y_SCREEN);


//////////////////////////////////////// Posição e camera ///////////////////////////////////////////

// atualiza posição do jogador
void player_update_position (Player *player, int num_platforms, Platform **platforms, int level_width);

//atualiza camera do jogador
void update_camera(Player *player, float *camera_x, int X_SCREEN, float level_width);


// tiro
void buster_fire(Player *player, int X_SCREEN, int Y_SCREEN);


// colisoes
void resolve_collision_with_platform(Player *player, Platform *platform, int status);
int check_collision_with_platform(Player *player, Platform *platform);

void player_destroy(Player *player);


///////////////////////////////////////// Animação ////////////////////////////////////////////////

// função que muda o estado de animação
void player_set_animation_state(Player *player, PlayerAnimState new_state);

// Atualiza/avança os frames da animação
void player_update_animation(Player *player);

// atualiza sprite do jogador definitivamente, ela chama as outras duas funções de sprite
// como auxiliares
void update_player_sprite(Player *player);

// retorna o sprite do player, a função de desenhar usa ela
void player_sprite(Player *player, ALLEGRO_BITMAP **sprite_sheet, entities_sprites *sprites, int *frames_per_row);

#endif