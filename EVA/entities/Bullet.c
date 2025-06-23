#include "Bullet.h"
#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include "../gameflow/Assets.h"

// cria a bala do jogador com base no tipo de tiro (o quão carregado está)
bullet* bullet_create(float dificulty, unsigned short x, unsigned short y, int trajectory, bullet *next, int type, int X_SCREEN, int Y_SCREEN) {

	bullet *new_bullet = (bullet*) malloc(sizeof(bullet));
	if (!new_bullet) return NULL;
	new_bullet->type = type;
	new_bullet->x = x; 									
	new_bullet->y = y;	

	switch (type) {
		case 1:
			new_bullet->height = Y_SCREEN*0.15;
			new_bullet->width = X_SCREEN*0.06;
			new_bullet->hit_box_x = 0.55*new_bullet->width;
			new_bullet->hit_box_y = new_bullet->height;
			new_bullet->damage = BULLET_1_DAMAGE/dificulty;
			new_bullet->speed = X_SCREEN*0.025;
			new_bullet->animation_speed = BULLET_1_ANIMATION_SPEED;
			new_bullet->frames = BULLET_1_FRAMES;
			break;
		case 2:
			new_bullet->height = Y_SCREEN*0.195;
			new_bullet->width = X_SCREEN*0.09;
			new_bullet->hit_box_x = 0.75*new_bullet->width;
			new_bullet->hit_box_y = new_bullet->height;
			new_bullet->damage = BULLET_2_DAMAGE/dificulty;
			new_bullet->speed = X_SCREEN*0.02;
			new_bullet->animation_speed = BULLET_2_ANIMATION_SPEED;
			new_bullet->frames = BULLET_2_FRAMES;
			break;
		case 3:
			new_bullet->height = Y_SCREEN*0.195;
			new_bullet->width = X_SCREEN*0.175;
			new_bullet->hit_box_x = 0.75*new_bullet->width;
			new_bullet->hit_box_y = new_bullet->height ;
			new_bullet->damage = BULLET_3_DAMAGE/dificulty;
			new_bullet->speed = X_SCREEN*0.015;
			new_bullet->animation_speed = BULLET_3_ANIMATION_SPEED;	
			new_bullet->frames = BULLET_3_FRAMES;	
			break;
	}
	
																														
	new_bullet->trajectory = trajectory;																											
	new_bullet->next = next; 	
	new_bullet->frame_timer = 0;
	new_bullet->current_frame = 0;

	return new_bullet;
}

// libera memória
void bullet_destroy(bullet *element){					
	free(element);					
}

// fala qual sprite da bala
void bullet_sprite (bullet *shot, ALLEGRO_BITMAP **sprite_sheet, struct entities_sprites *sprites ) {
	switch (shot->type) {
        case 1:
            *sprite_sheet = sprites->bullet_1_image;
            break;
        case 2:
            *sprite_sheet = sprites->bullet_2_image;
            break;
        case 3:
            *sprite_sheet = sprites->bullet_3_image;
            break;
    }
}

/////////////////////// JA

//cria a bullet do ja
ja_bullet* ja_bullet_create(float dificulty, float speed, unsigned short x, unsigned short y, int trajectory, ja_bullet *next, int X_SCREEN, int Y_SCREEN) {

	ja_bullet *new_bullet = (ja_bullet*) malloc(sizeof(ja_bullet));
	if (!new_bullet) return NULL;
	new_bullet->height = Y_SCREEN*0.1;
	new_bullet->width = X_SCREEN*0.06;
	new_bullet->speed = speed;
	new_bullet->x = x; //porque atira do braço										
	new_bullet->y = y;	
	new_bullet->hit_box_x = new_bullet->width;
	new_bullet->hit_box_y = 0.8*new_bullet->height;																														
	new_bullet->trajectory = trajectory;																											
	new_bullet->next = (struct ja_bullet*) next; 	
	new_bullet->frame_timer = 0;
	new_bullet->current_frame = 0;

	new_bullet->damage = JA_BULLET_DAMAGE/dificulty;
	return new_bullet;
}

//libera memória
void ja_bullet_destroy(ja_bullet *element) {					
	free(element);					
}

////////// SACHIEL

//a diferença do tipo 1 ,2 e 3 é só o comprimento e velocidade
// cria a bala do chefão da 1 fase, o Sachiel
sa_bullet* sa_bullet_create(float dificulty, float speed, unsigned short x, unsigned short y, int trajectory, sa_bullet *next, int X_SCREEN, int Y_SCREEN, int type) {

	sa_bullet *new_bullet = (sa_bullet*) malloc(sizeof(sa_bullet));
	if (!new_bullet) return NULL;
	new_bullet->height = Y_SCREEN*0.25;
	if (type == 1) new_bullet->width = Y_SCREEN*0.25;	
	else if (type == 2) new_bullet->width = Y_SCREEN*0.4;
	else if (type == 3) {
		new_bullet->width = Y_SCREEN*0.6;
		new_bullet->height = Y_SCREEN*0.15;
	}
	new_bullet->x = x; //porque atira do braço										
	new_bullet->y = y;	
	if (type != 3) new_bullet->hit_box_x = 0.7*new_bullet->width ;
	else new_bullet->hit_box_x = 0.4*new_bullet->width;
	new_bullet->hit_box_y = 0.7*new_bullet->height;																														
	new_bullet->trajectory = trajectory;																											
	new_bullet->next = (struct sa_bullet*) next; 	
	new_bullet->frame_timer = 0;
	new_bullet->current_frame = 0;
	if (type == 1 || type == 2)
		new_bullet->speed = speed;
	else
		new_bullet->speed = speed*0.4;

	new_bullet->damage = SA_BULLET_DAMAGE/dificulty;
	return new_bullet;
}

// libera memória
void sa_bullet_destroy(sa_bullet *element) {					
	free(element);					
}

