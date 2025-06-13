#ifndef __JET_ALONE__
#define __JET_ALONE__

#include "Buster.h" //para atirar
#include <allegro5/allegro_image.h>
#include "Player.h"
#include "../gameflow/Assets.h"

#define JA_SPEED 2
#define JA_WIDTH 330
#define JA_HEIGHT 330
#define JA_SHOT_COOLDOWN 30
#define JA_STATE_TIMER 90
#define JA_MIN_DISTANCE X_SCREEN/3
#define JA_FLIP_DISTANCE 200
#define JA_SQUAT_CHANCE 50
#define JA_WALK_ANIMATION 45
#define JA_SQUAT_ANIMATION 10

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
typedef struct {
    float life;
    float damage;
    unsigned char dead;

    float x, y;
    float vx,vy;
    float center_x, center_y;
    float hit_box_x, hit_box_y;
    int direction;

    JetAloneState state;
    float state_timer;

    int current_frame;
    float frame_timer;

    unsigned char hit_take;
    int hit_take_timer;

    ja_buster_t *ja_buster;
    float shot_timer;
    float squat_probability;
    unsigned char is_squat;
    unsigned char is_shooting;
} Jet_alone;

Jet_alone *ja_create(float dificulty, float squat_probability, float x, float y, int direction);

void ja_sprite (Jet_alone *ja, ALLEGRO_BITMAP **sprite_sheet, entities_sprites *sprites);

void update_ja(Jet_alone *ja, float camera_x, Player *player, int X_SCREEN);

void update_state_ja(Jet_alone *ja, float camera_x, Player *player, int X_SCREEN);

void action_ja(Jet_alone *ja, Player *player) ;
void move_ja(Jet_alone *ja) ;
void squat_ja(Jet_alone *ja) ;
void stop_ja(Jet_alone *ja) ;

void ja_buster_fire(Jet_alone *ja);

#endif