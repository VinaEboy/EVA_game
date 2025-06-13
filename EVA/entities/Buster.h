#ifndef __BUSTER__
#define __BUSTER__

#include "Charge_shot.h"

#define BUSTER_COOLDOWN 2							

typedef struct {																											
	int timer;	
    float dificulty;					
	bullet_1 *shots_1;
    bullet_2 *shots_2;
    bullet_3 *shots_3;							
} buster_t;														

buster_t* buster_create(float dificulty);																								
bullet_1* buster_shot_1(unsigned short x, unsigned short y, unsigned char trajectory, buster_t *buster);
bullet_2* buster_shot_2(unsigned short x, unsigned short y, unsigned char trajectory, buster_t *buster);
bullet_2* buster_shot_2(unsigned short x, unsigned short y, unsigned char trajectory, buster_t *buster);									
void buster_destroy(buster_t *buster);						

void update_bullets_1(float camera_x, buster_t *buster, int X_SCREEN);
void update_bullets_2(float camera_x, buster_t *buster, int X_SCREEN);
void update_bullets_3(float camera_x, buster_t *buster, int X_SCREEN);
 
typedef struct {
    int timer;
    float dificulty;
    ja_bullet *shots;
}  ja_buster_t;

ja_buster_t *ja_buster_create(float dificulty);
#endif						