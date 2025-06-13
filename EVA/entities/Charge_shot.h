#ifndef __CHARGE_SHOT__
#define __CHARGE_SHOT__

#define BULLET_MOVE 30 //a velocidade é a mesma para todos por enquanto
#define BULLET_1_HEIGHT 120
#define BULLET_1_WIDTH 80
#define BULLET_1_ANIMATION_SPEED 1

#define BULLET_2_HEIGHT 150
#define BULLET_2_WIDTH 120
#define BULLET_2_ANIMATION_SPEED 3

#define BULLET_3_HEIGHT 150
#define BULLET_3_WIDTH 240
#define BULLET_3_ANIMATION_SPEED 3

struct Player;


typedef struct bullet_1 {							
	float x;							
	float y;		
	float hit_box_x;
	float hit_boy_y;																											
	int trajectory;																									
	struct bullet_1 *next; 	
	
    int current_frame;      // O frame atual da animação (0 a 8)
    int frame_timer;        // Um contador para controlar a velocidade da animação

	float damage;
} bullet_1;

typedef struct bullet_2{																													
	float x;																														
	float y;		
	float hit_box_x;
	float hit_boy_y;											
	int trajectory;																													
	struct bullet_2 *next; 		
	
	int current_frame;      // O frame atual da animação (0 a 5)
    int frame_timer;        // Um contador para controlar a velocidade da animação

	float damage;
} bullet_2;

typedef struct bullet_3 {																													
	float x;										
	float y;		
	float hit_box_x;
	float hit_boy_y;																														
	int trajectory;																											
	struct bullet_3 *next; 	
	
	int current_frame;      // O frame atual da animação (0 a 4)
    int frame_timer;        // Um contador para controlar a velocidade da animação

	float damage;
} bullet_3;


bullet_1* bullet_1_create(float dificulty, unsigned short x, unsigned short y,int trajectory, bullet_1 *next);																								
void bullet_1_destroy(bullet_1 *element);	

bullet_2* bullet_2_create(float dificulty, unsigned short x, unsigned short y, int trajectory, bullet_2 *next);																										
void bullet_2_destroy(bullet_2 *element);	

bullet_3* bullet_3_create(float dificulty, unsigned short x, unsigned short y, int trajectory, bullet_3 *next);																									
void bullet_3_destroy(bullet_3 *element);	

//ja

#define JA_BULLET_MOVE 40 //a velocidade é a mesma para todos por enquanto
#define JA_BULLET_HEIGHT 36
#define JA_BULLET_WIDTH 36
#define JA_BULLET_ANIMATION_SPEED 1

typedef struct {
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