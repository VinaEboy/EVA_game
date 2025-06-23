#ifndef __BUSTER__
#define __BUSTER__

// É o sentinela da fila encadeada que são os tiros
// implementação analoga aos da video aula

#include "Bullet.h"

#define BUSTER_COOLDOWN 2							

//jogador
typedef struct  {																											
	int timer;	
    float dificulty;					
	bullet *shots;
} buster_t;			

// buster do jogador
buster_t* buster_create(float dificulty);	

// enfileira o tiro na fila encadeada
bullet* buster_shot(unsigned short x, unsigned short y, unsigned char trajectory, buster_t *buster, int type, int X_SCREEN, int Y_SCREEN);

// libera memória
void buster_destroy(buster_t *buster);						

// atualiza as posições do tiro 
void update_player_bullets(float camera_x, buster_t *buster, int X_SCREEN, int level_width);

//////////// JA
 
typedef struct {
    int timer;
    float dificulty;
    float bullet_speed;
    ja_bullet *shots;
}  ja_buster_t;

// cria o sentinela
ja_buster_t *ja_buster_create(float dificulty, float speed);

// atualiza posições
void update_ja_bullets(float camera_x, ja_buster_t *ja_buster, int X_SCREEN);

// enfileira tiro
ja_bullet* ja_buster_shot(unsigned short x, unsigned short y, unsigned char trajectory, ja_buster_t *ja_buster, int X_SCREEN, int Y_SCREEN);

// libera memória
void ja_buster_destroy(ja_buster_t *ja_buster);

///////////////// SACHIEL

typedef struct {
    int timer;
    float dificulty;
    sa_bullet *shots;
} sa_buster_t;

// cria buster do sachiel
sa_buster_t *sa_buster_create(float dificulty);

// enfileira tiro
sa_bullet *sa_buster_shot(int speed,unsigned short x, unsigned short y, unsigned char trajectory, sa_buster_t *sa_buster, int X_SCREEN, int Y_SCREEN, int type);

// libera memória
void sa_buster_destroy(sa_buster_t *sa_buster);

// atualiza posições
void update_sa_bullets(float camera_x, sa_buster_t *sa_buster, int X_SCREEN, int level_width);

#endif						