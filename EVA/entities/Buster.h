#ifndef __BUSTER__
#define __BUSTER__

#include "Bullet.h"

#define BUSTER_COOLDOWN 2							

typedef struct  {																											
	int timer;	
    float dificulty;					
	bullet *shots;
} buster_t;														

buster_t* buster_create(float dificulty);																								
bullet* buster_shot(unsigned short x, unsigned short y, unsigned char trajectory, buster_t *buster, int type);
void buster_destroy(buster_t *buster);						

void update_player_bullets(float camera_x, buster_t *buster, int X_SCREEN, int level_width);

//////////// JA
 
typedef struct {
    int timer;
    float dificulty;
    ja_bullet *shots;
}  ja_buster_t;

ja_buster_t *ja_buster_create(float dificulty);
void update_ja_bullets(float camera_x, ja_buster_t *ja_buster, int X_SCREEN);
ja_bullet* ja_buster_shot(unsigned short x, unsigned short y, unsigned char trajectory, ja_buster_t *ja_buster);
void ja_buster_destroy(ja_buster_t *ja_buster);

#endif						