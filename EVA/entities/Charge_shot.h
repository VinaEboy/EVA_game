#ifndef __CHARGE_SHOT__
#define __CHARGE_SHOT__

#define BULLET_MOVE 15 //a velocidade é a mesma para todos por enquanto
#define BULLET_1_HEIGHT 36
#define BULLET_1_WEIGHT 24
#define BULLET_2_HEIGHT 30
#define BULLET_2_WEIGHT 24
#define BULLET_3_HEIGHT 64
#define BULLET_3_WEIGHT 24

struct Player;


typedef struct bullet_1 {							
	float x;							
	float y;		
	float hit_box_x;
	float hit_boy_y;																											
	unsigned char trajectory;																									
	struct bullet_1 *next; 	
	
    int current_frame;      // O frame atual da animação (0 a 8)
    int frame_timer;        // Um contador para controlar a velocidade da animação
} bullet_1;

typedef struct bullet_2{																													
	float x;																														
	float y;		
	float hit_box_x;
	float hit_boy_y;											
	unsigned char trajectory;																													
	struct bullet_2 *next; 		
	
	int current_frame;      // O frame atual da animação (0 a 5)
    int frame_timer;        // Um contador para controlar a velocidade da animação
} bullet_2;

typedef struct bullet_3 {																													
	float x;										
	float y;		
	float hit_box_x;
	float hit_boy_y;																														
	unsigned char trajectory;																											
	struct bullet_3 *next; 	
	
	int current_frame;      // O frame atual da animação (0 a 4)
    int frame_timer;        // Um contador para controlar a velocidade da animação
} bullet_3;


bullet_1* bullet_1_create(unsigned short x, unsigned short y, unsigned char trajectory, bullet_1 *next);										
void bullet_1_move(bullet_1 *elements);																	
void bullet_1_destroy(bullet_1 *element);	

bullet_2* bullet_2_create(unsigned short x, unsigned short y, unsigned char trajectory, bullet_2 *next);										
void bullet_2_move(bullet_2 *elements);																	
void bullet_2_destroy(bullet_2 *element);	

bullet_3* bullet_3_create(unsigned short x, unsigned short y, unsigned char trajectory, bullet_3 *next);										
void bullet_3_move(bullet_3 *elements);																	
void bullet_3_destroy(bullet_3 *element);	



#endif