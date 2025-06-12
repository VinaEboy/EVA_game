#include "Charge_shot.h"
#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

bullet_1* bullet_1_create(unsigned short x, unsigned short y, int trajectory, bullet_1 *next) {

	bullet_1 *new_bullet = (bullet_1*) malloc(sizeof(bullet_1));
	if (!new_bullet) return NULL;
	new_bullet->x = x; //porque atira do braço										
	new_bullet->y = y;	
	new_bullet->hit_box_x = BULLET_1_HEIGHT;
	new_bullet->hit_boy_y = BULLET_1_WEIGHT;																														
	new_bullet->trajectory = trajectory;																											
	new_bullet->next = next; 	
	new_bullet->frame_timer = 0;
	new_bullet->current_frame = 0;
	return new_bullet;
}

bullet_2* bullet_2_create(unsigned short x, unsigned short y, int trajectory, bullet_2 *next) {

	bullet_2 *new_bullet = (bullet_2*) malloc(sizeof(bullet_2));
	if (!new_bullet) return NULL;
	new_bullet->x = x; //porque atira do braço											
	new_bullet->y = y;	
	new_bullet->hit_box_x = BULLET_2_HEIGHT;
	new_bullet->hit_boy_y = BULLET_2_WEIGHT;																														
	new_bullet->trajectory = trajectory;																											
	new_bullet->next = next; 	
	new_bullet->frame_timer = 0;
	new_bullet->current_frame = 0;
	return new_bullet;
}

bullet_3* bullet_3_create(unsigned short x, unsigned short y, int trajectory, bullet_3 *next) {

	bullet_3 *new_bullet = (bullet_3*) malloc(sizeof(bullet_3));
	if (!new_bullet) return NULL;
	new_bullet->x = x; //porque atira do braço										
	new_bullet->y = y;	
	new_bullet->hit_box_x = BULLET_3_HEIGHT;
	new_bullet->hit_boy_y = BULLET_3_WEIGHT;																														
	new_bullet->trajectory = trajectory;																											
	new_bullet->next = next; 	
	new_bullet->frame_timer = 0;
	new_bullet->current_frame = 0;
	return new_bullet;
}

void bullet_1_destroy(bullet_1 *element){					
	free(element);					
}

void bullet_2_destroy(bullet_2 *element){					
	free(element);					
}

void bullet_3_destroy(bullet_3 *element){					
	free(element);					
}