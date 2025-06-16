#ifndef __BULLET__
#define __BULLET__

#define BULLET_1_MOVE 30 //a velocidade é a mesma para todos por enquanto
#define BULLET_1_HEIGHT 120
#define BULLET_1_WIDTH 80
#define BULLET_1_ANIMATION_SPEED 1
#define BULLET_1_FRAMES 9
#define BULLET_1_DAMAGE 5

#define BULLET_2_MOVE 30
#define BULLET_2_HEIGHT 150
#define BULLET_2_WIDTH 120
#define BULLET_2_ANIMATION_SPEED 3
#define BULLET_2_FRAMES 6
#define BULLET_2_DAMAGE 15

#define BULLET_3_MOVE 30
#define BULLET_3_HEIGHT 150
#define BULLET_3_WIDTH 240
#define BULLET_3_ANIMATION_SPEED 3
#define BULLET_3_FRAMES 5
#define BULLET_3_DAMAGE 35

#include <allegro5/allegro_image.h>
#include <allegro5/allegro.h>

struct Player;
struct entities_sprites;

typedef struct bullet {		
	int height;
	int width;			
	float speed;		
	int animation_speed;
	int frames;
	float x;							
	float y;		
	float hit_box_x;
	float hit_box_y;																											
	int trajectory;																									
	struct bullet *next; 
	int type; // de 1 a 3 é o tiro normal, carregado e super carregado.	
	
    int current_frame;      // O frame atual da animação (0 a 8)
    int frame_timer;        // Um contador para controlar a velocidade da animação

	float damage;
} bullet;


bullet *bullet_create(float dificulty, unsigned short x, unsigned short y,int trajectory, bullet *next, int type);																								
void bullet_destroy(bullet *element);	
void bullet_sprite (bullet *shot, ALLEGRO_BITMAP **sprite_sheet, struct entities_sprites *sprites );

//ja

#define JA_BULLET_MOVE 20 //a velocidade é a mesma para todos por enquanto
#define JA_BULLET_HEIGHT 80
#define JA_BULLET_WIDTH 80
#define JA_BULLET_ANIMATION_SPEED 2
#define JA_BULLET_DAMAGE 50

typedef struct ja_bullet {
	float x;																														
	float y;		
	float hit_box_x;
	float hit_box_y;											
	int trajectory;																													
	struct ja_bullet *next; 		
	
	int current_frame;      // O frame atual da animação (0 a 3)
    int frame_timer;        // Um contador para controlar a velocidade da animação

	float damage;	
} ja_bullet;

ja_bullet* ja_bullet_create(float dificulty, unsigned short x, unsigned short y, int trajectory, ja_bullet *next);

void ja_bullet_destroy(ja_bullet *element);


#endif