#ifndef __JET_ALONE__
#define __JET_ALONE__

// Inimigo da fase 1 : Jet Alone, ou sua sigla JA

#include "Buster.h" //para atirar
#include <allegro5/allegro_image.h>
#include "Player.h"
#include "../gameflow/Assets.h"
#include "../mechanics/Collisions.h" 

#define JA_SHOT_COOLDOWN 45
#define JA_STATE_TIMER 45
#define JA_FLIP_DISTANCE 200
#define JA_WALK_ANIMATION 30
#define JA_SQUAT_ANIMATION 10
#define JA_ARM_UP_TIME 25
#define JA_CONTACT_DAMAGE 20

struct Player;

// O enum de estados 
typedef enum {
    JA_WALK,
    JA_SQUAT,
    JA_STOP
} JetAloneState;


typedef struct Jet_alone {
    float life;
    float damage; //dano em caso de contato do player com jet alone
    unsigned char dead;
    float distance_to_player; //significa que quanto maior, maior vai ser a distancia do player em que ele vai "parar" e atirar

    float gravity;
    float speed;
    float bullet_speed;

    float height, width;
    float squat_height;
    float x, y;
    float vx,vy;
    float center_x, center_y;
    float hit_box_x, hit_box_y;
    int direction;
    unsigned char is_platform_left_edge; //sinal de controle para ele n se jogar da beirada
    unsigned char is_platform_right_edge;
    unsigned char is_on_ground;
    unsigned char is_taking_damage;
    
    JetAloneState state;
    float state_timer;

    int current_frame;
    float frame_timer;

    unsigned char hit_take;
    int hit_take_timer;

    int arm_up_timer;
    ja_buster_t *ja_buster;
    float shot_timer;
    float squat_probability;
    unsigned char is_squat;
    unsigned char is_shooting;
} Jet_alone;

//aloca memória para o personagem
Jet_alone *ja_create(float dificulty, float squat_probability, float x, float y, int direction, float distance_to_player, int X_SCREEN, int Y_SCREEN);

//com base no estado retorna o sprite
void ja_sprite (Jet_alone *ja, ALLEGRO_BITMAP **sprite_sheet, entities_sprites *sprites);

// atualiza posição
void update_ja_position (Jet_alone *ja, int num_platforms, Platform **platforms, int level_width);

//faz os updates necessários do ja (de estado e de ação)
void update_ja(Jet_alone *ja, float camera_x, Player *player, int X_SCREEN, int Y_SCREEN);

//atualiza o estado do jet alone e caso necessário faz ele virar a direção
void update_state_ja(Jet_alone *ja, float camera_x, Player *player, int X_SCREEN);

//chama a função correspondente a ação dele no estado
void action_ja(Jet_alone *ja, Player *player, int X_SCREEN, int Y_SCREEN) ;

////////////// Ações de Estado ///////////////////////////////////////

//ele se movendo atrás do player
void move_ja(Jet_alone *ja, int X_SCREEN, int Y_SCREEN) ;

// ele se agachando
void squat_ja(Jet_alone *ja, int X_SCREEN, int Y_SCREEN) ;

// ele parado atirando
void stop_ja(Jet_alone *ja, int X_SCREEN, int Y_SCREEN) ;

// TIRO
void ja_buster_fire(Jet_alone *ja, int X_SCREEN, int Y_SCREEN);

//libera memória
void ja_destroy(struct Jet_alone *ja);

//retorna 0 se não estiver em beirada
//retorna 1 se estiver na beirada esquerda
//retorna 2 se estiver na beirada da direita
// Nao trata dos casos em que ele está na beirada das duas ao mesmo tempo, ou seja,
// uma plataforma muito pequena de largura ficaria ambíguo
int ja_check_for_ledge(struct Jet_alone *ja, Platform **platforms, int num_platforms);
#endif