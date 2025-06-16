#ifndef __JET_ALONE__
#define __JET_ALONE__

#include "Buster.h" //para atirar
#include <allegro5/allegro_image.h>
#include "Player.h"
#include "../gameflow/Assets.h"
#include "../mechanics/Collisions.h" 

#define JA_SPEED 3
#define JA_WIDTH 356
#define JA_HEIGHT 356
#define JA_SHOT_COOLDOWN 45
#define JA_STATE_TIMER 45
#define JA_FLIP_DISTANCE 200
#define JA_WALK_ANIMATION 30
#define JA_SQUAT_ANIMATION 10
#define ARM_UP_TIME 15
#define JA_SQUAT_HEIGHT 200
#define JA_CONTACT_DAMAGE 20

// Forward declare para a struct do jogador
struct Player;

// O enum de estados continua o mesmo
typedef enum {
    JA_WALK,
    JA_SQUAT,
    JA_STOP
} JetAloneState;


// --- Estrutura de Dados do Inimigo (Modificada) ---
// Note que os ponteiros de ALLEGRO_BITMAP* foram removidos daqui.
typedef struct Jet_alone {
    float life;
    float damage;
    unsigned char dead;
    float distance_to_player; //significa que quanto maior, maior vai ser a distancia do player em que ele vai "parar" e atirar

    float x, y;
    float vx,vy;
    float center_x, center_y;
    float hit_box_x, hit_box_y;
    int direction;
    unsigned char is_platform_left_edge; //sinal de controle para ele n se jogar da beirada
    unsigned char is_platform_right_edge;
    unsigned char is_on_ground;
    char is_taking_damage;
    
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

Jet_alone *ja_create(float dificulty, float squat_probability, float x, float y, int direction, float distance_to_player);

void ja_sprite (Jet_alone *ja, ALLEGRO_BITMAP **sprite_sheet, entities_sprites *sprites);

void update_ja_position (Jet_alone *ja, int num_platforms, Platform **platforms, int level_width);

void update_ja(Jet_alone *ja, float camera_x, Player *player, int X_SCREEN);

void update_state_ja(Jet_alone *ja, float camera_x, Player *player, int X_SCREEN);

void action_ja(Jet_alone *ja, Player *player) ;
void move_ja(Jet_alone *ja) ;
void squat_ja(Jet_alone *ja) ;
void stop_ja(Jet_alone *ja) ;

void ja_buster_fire(Jet_alone *ja);

void ja_destroy(struct Jet_alone *ja);

// aux
int ja_check_for_ledge(struct Jet_alone *ja, Platform **platforms, int num_platforms);
#endif