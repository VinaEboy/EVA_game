#ifndef __BULLET__
#define __BULLET__

// Implementação dos tiros, análogo aos do vídeo do ALLEGRO
// são os "nós" da fila encadeada em que o Buster é o sentinela

// BULLETS do PLAYER

#define BULLET_1_ANIMATION_SPEED 1
#define BULLET_1_FRAMES 9
#define BULLET_1_DAMAGE 8

#define BULLET_2_ANIMATION_SPEED 3
#define BULLET_2_FRAMES 6
#define BULLET_2_DAMAGE 25

#define BULLET_3_ANIMATION_SPEED 3
#define BULLET_3_FRAMES 5
#define BULLET_3_DAMAGE 50

#include <allegro5/allegro_image.h>
#include <allegro5/allegro.h>

struct Player;
struct entities_sprites;

// bullet do player
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
	int trajectory;	// -1 é esquerda, 1 é direita e 2 é cima																								
	struct bullet *next; 
	int type; // de 1 a 3 é o tiro normal, carregado e super carregado.	
	
    int current_frame;      // O frame atual da animação (0 a 8)
    int frame_timer;        // Um contador para controlar a velocidade da animação

	float damage;
} bullet;


// cria a bala do jogador
bullet *bullet_create(float dificulty, unsigned short x, unsigned short y,int trajectory, bullet *next, int type, int X_SCREEN, int Y_SCREEN);																								

// libera memoria
void bullet_destroy(bullet *element);	

// altera o valor de qual sprite é do jogador
void bullet_sprite (bullet *shot, ALLEGRO_BITMAP **sprite_sheet, struct entities_sprites *sprites );

//////////////////////////////// BULLETS do JA

#define JA_BULLET_ANIMATION_SPEED 4
#define JA_BULLET_DAMAGE 16

typedef struct ja_bullet {
	int height;
	int width;	
	float x;																														
	float y;
	float speed;		
	float hit_box_x;
	float hit_box_y;											
	int trajectory;																													
	struct ja_bullet *next; 		
	
	int current_frame;      // O frame atual da animação (0 a 3)
    int frame_timer;        // Um contador para controlar a velocidade da animação

	float damage;	
} ja_bullet;

//cria a bullet do ja
ja_bullet* ja_bullet_create(float dificulty, float speed, unsigned short x, unsigned short y, int trajectory, ja_bullet *next, int X_SCREEN, int Y_SCREEN);

//libera memória
void ja_bullet_destroy(ja_bullet *element);

////////////////////// Bullets do Sachiel

#define SA_BULLET_ANIMATION_SPEED 2
#define SA_BULLET_DAMAGE 20

typedef struct sa_bullet {
	int height;
	int width;	
	float x;																														
	float y;		
	float hit_box_x;
	float hit_box_y;											
	int trajectory;
	float speed; //vai aumentar a velocidade dos tiros depois																													
	struct sa_bullet *next; 		
	
	int current_frame;      // O frame atual da animação (0 a 1)
    int frame_timer;        // Um contador para controlar a velocidade da animação

	float damage;	
} sa_bullet;

//a diferença do tipo 1 ,2 e 3 é só o comprimento e velocidade
// cria a bala do chefão da 1 fase, o Sachiel
sa_bullet* sa_bullet_create(float dificulty, float speed, unsigned short x, unsigned short y, int trajectory, sa_bullet *next, int X_SCREEN, int Y_SCREEN, int type);

// libera memória
void sa_bullet_destroy(sa_bullet *element);
#endif