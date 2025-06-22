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
bullet* buster_shot(unsigned short x, unsigned short y, unsigned char trajectory, buster_t *buster, int type, int X_SCREEN, int Y_SCREEN);
void buster_destroy(buster_t *buster);						

void update_player_bullets(float camera_x, buster_t *buster, int X_SCREEN, int level_width);

//////////// JA
 
typedef struct {
    int timer;
    float dificulty;
    float bullet_speed;
    ja_bullet *shots;
}  ja_buster_t;

ja_buster_t *ja_buster_create(float dificulty, float speed);
void update_ja_bullets(float camera_x, ja_buster_t *ja_buster, int X_SCREEN);
ja_bullet* ja_buster_shot(unsigned short x, unsigned short y, unsigned char trajectory, ja_buster_t *ja_buster, int X_SCREEN, int Y_SCREEN);
void ja_buster_destroy(ja_buster_t *ja_buster);

///////////////// SACHIEL

typedef struct {
    int timer;
    float dificulty;
    sa_bullet *shots;
} sa_buster_t;

sa_buster_t *sa_buster_create(float dificulty);
sa_bullet *sa_buster_shot(int speed,unsigned short x, unsigned short y, unsigned char trajectory, sa_buster_t *sa_buster, int X_SCREEN, int Y_SCREEN, int type);
void sa_buster_destroy(sa_buster_t *sa_buster);
void update_sa_bullets(float camera_x, sa_buster_t *sa_buster, int X_SCREEN, int level_width);

#endif						