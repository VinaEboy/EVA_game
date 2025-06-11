#ifndef __BUSTER__
#define __BUSTER__

#include "Charge_shot.h"

#define BUSTER_COOLDOWN 10							

typedef struct {																											
	unsigned char timer;						
	bullet_1 *shots_1;
    bullet_2 *shots_2;
    bullet_3 *shots_3;							
} buster_t;														

buster_t* buster_create();																								
bullet_1* buster_shot_1(unsigned short x, unsigned short y, unsigned char trajectory, buster_t *buster);
bullet_2* buster_shot_2(unsigned short x, unsigned short y, unsigned char trajectory, buster_t *buster);
bullet_2* buster_shot_2(unsigned short x, unsigned short y, unsigned char trajectory, buster_t *buster);									
void buster_destroy(buster_t *buster);						

void update_bullets_1(buster_t *buster);
void update_bullets_2(buster_t *buster);
void update_bullets_3(buster_t *buster);

#endif						