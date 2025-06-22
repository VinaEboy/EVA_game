#ifndef __SACHIEL__
#define __SACHIEL__


#include "Buster.h" //para atirar
#include <allegro5/allegro_image.h>
#include "Player.h"
#include "../gameflow/Assets.h"
#include "../mechanics/Collisions.h" 

#define UP_DOWN_MODE 0
#define TRANSITION_MODE 1

#define INVENCIBLE_TIME 20
#define SA_ARM_UP_TIME 25
#define FIRE_TIME 40
#define POSITION_TIME 510
#define SHOT_UP_PROBABILITY 0.5
#define MINOR_ANIMATION 10
#define SACHIEL_DEATH_TIME 60 //o tempo que o jogo vai ficar rodando depois do chefão ser derrotado


typedef enum {
    SA_DEFAULT,
    SA_PLAYER_BELOW,
    SA_UP_SHOT,
    SA_DOWN_SHOT,
    SA_SWITCHING_SIDE,
} SachielState;

typedef struct Sachiel {
    float life;
    float max_life;
    float damage; //dano em caso de contato do player com o heart do sachiel
    unsigned char is_dead;
    int death_timer;

    float top_margin_default ;
    float ground_margin_default;
    float top_margin_transition ;
    float left_margin;
    float right_margin;
    unsigned char minor_step_1; //no switching side ele fica pequeno (step 1)
    unsigned char minor_step_2; // e depois volta ao normal (step 2);

    float height, width;
    float heart_height, heart_width;
    float x, y;
    float vx,vy;
    float center_x, center_y;
    float hit_box_x, hit_box_y;
    int heart_direction; // -1 é para cima, 1 é para baixo
    
    SachielState state;
    float position_timer; //timer para o coração trocar de posição na tela ou não
    float fire_timer; //timer para ele atirar
    int frame_minor_part; //o sprites do Sachiel são grandes demais e uma animação tive que colocar em 3 pngs

    int current_frame;
    int frame_timer;

    unsigned char bersek_mode; //quando o vilão está com pouca vida ele fica desesperado e mais frenético
    unsigned char is_invencible;
    int invencible_timer;
    unsigned char hit_take;
    unsigned char is_left;
    unsigned char is_right;

    unsigned char is_minor; //se ele está encolhido ou nao
    unsigned char side_switched; //se já terminou de trocar de lado

    float heart_speed;
    float fire_speed;
    float frequency_fire; //ao decorrer da luta, o tiro do chefão fica mais frequente
    int arm_up_timer;
    sa_buster_t *sa_buster;
    float shot_timer;

    int level_width; //metadado
} Sachiel;

Sachiel *create_sa(float dificulty, int X_SCREEN, int Y_SCREEN);
void update_sa(Sachiel *sa, Player *player, int X_SCREEN, int Y_SCREEN);
void update_state_sa (Sachiel *sa, Player *player, int X_SCREEN, int Y_SCREEN);
void update_heart_position (Sachiel *sa, int level_width, int X_SCREEN, int Y_SCREEN);
void action_sa(Sachiel *sa, int X_SCREEN, int Y_SCREEN );
void heart_default_move(Sachiel *sa, int X_SCREEN, int Y_SCREEN);
void switching_side_sa(Sachiel *sa, int X_SCREEN) ;
void going_cel_sa(Sachiel *sa);
void ceiling_sa(Sachiel *sa);
void sa_sprite (Sachiel *sa, ALLEGRO_BITMAP **sprite_sheet, entities_sprites *sprites) ;
void sa_buster_fire(Sachiel *sa, int X_SCREEN, int Y_SCREEN);
void sa_destroy(struct Sachiel *sa);

#endif