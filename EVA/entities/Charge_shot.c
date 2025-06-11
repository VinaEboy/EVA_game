#include "Charge_shot.h"
#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

bullet_1* bullet_1_create(unsigned short x, unsigned short y, unsigned char trajectory, bullet_1 *next) {
	if ((trajectory < 0) || (trajectory > 1)) return NULL;

	bullet_1 *new_bullet = (bullet_1*) malloc(sizeof(bullet_1));
	if (!new_bullet) return NULL;
	new_bullet->x = x;										
	new_bullet->y = y;	
	new_bullet->hit_box_x = BULLET_1_HEIGHT;
	new_bullet->hit_boy_y = BULLET_1_WEIGHT;																														
	new_bullet->trajectory = trajectory;																											
	new_bullet->next = next; 	
	return new_bullet;
}

bullet_2* bullet_2_create(unsigned short x, unsigned short y, unsigned char trajectory, bullet_2 *next) {
	if ((trajectory < 0) || (trajectory > 1)) return NULL;

	bullet_2 *new_bullet = (bullet_2*) malloc(sizeof(bullet_2));
	if (!new_bullet) return NULL;
	new_bullet->x = x;										
	new_bullet->y = y;	
	new_bullet->hit_box_x = BULLET_2_HEIGHT;
	new_bullet->hit_boy_y = BULLET_2_WEIGHT;																														
	new_bullet->trajectory = trajectory;																											
	new_bullet->next = next; 	
	return new_bullet;
}

bullet_3* bullet_3_create(unsigned short x, unsigned short y, unsigned char trajectory, bullet_3 *next) {
	if ((trajectory < 0) || (trajectory > 1)) return NULL;

	bullet_3 *new_bullet = (bullet_3*) malloc(sizeof(bullet_3));
	if (!new_bullet) return NULL;
	new_bullet->x = x;										
	new_bullet->y = y;	
	new_bullet->hit_box_x = BULLET_3_HEIGHT;
	new_bullet->hit_boy_y = BULLET_3_WEIGHT;																														
	new_bullet->trajectory = trajectory;																											
	new_bullet->next = next; 	
	return new_bullet;
}

void bullet_1_move(bullet_1 *elements) {
	for (bullet_1 *index = elements; index != NULL; index = (bullet_1*) index->next){					
		if (!index->trajectory) index->x = index->x - BULLET_MOVE;										
		else index->x = index->x + BULLET_MOVE;															
	}
}

void bullet_2_move(bullet_2 *elements) {
	for (bullet_2 *index = elements; index != NULL; index = (bullet_2*) index->next){							
		if (!index->trajectory) index->x = index->x - BULLET_MOVE;								
		else index->x = index->x + BULLET_MOVE;															
	}
}

void bullet_3_move(bullet_3 *elements) {
	for (bullet_3 *index = elements; index != NULL; index = (bullet_3*) index->next){					
		if (!index->trajectory) index->x = index->x - BULLET_MOVE;									
		else index->x = index->x + BULLET_MOVE;								
	}
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