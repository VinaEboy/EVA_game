#include "Bullet.h"
#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include "../gameflow/Assets.h"


bullet* bullet_create(float dificulty, unsigned short x, unsigned short y, int trajectory, bullet *next, int type) {

	bullet *new_bullet = (bullet*) malloc(sizeof(bullet));
	if (!new_bullet) return NULL;
	new_bullet->type = type;
	new_bullet->x = x; //porque atira do braço										
	new_bullet->y = y;	

	switch (type) {
		case 1:
			new_bullet->hit_box_x = 0.55*BULLET_1_WIDTH;
			new_bullet->hit_box_y = BULLET_1_HEIGHT;
			new_bullet->damage = BULLET_1_DAMAGE/dificulty;
			new_bullet->speed = BULLET_1_MOVE;
			new_bullet->animation_speed = BULLET_1_ANIMATION_SPEED;
			new_bullet->frames = BULLET_1_FRAMES;
			new_bullet->height = BULLET_1_HEIGHT;
			new_bullet->width = BULLET_1_WIDTH;
			break;
		case 2:
			new_bullet->hit_box_x = 0.75*BULLET_2_WIDTH;
			new_bullet->hit_box_y = BULLET_2_HEIGHT;
			new_bullet->damage = BULLET_2_DAMAGE/dificulty;
			new_bullet->speed = BULLET_2_MOVE;
			new_bullet->animation_speed = BULLET_2_ANIMATION_SPEED;
			new_bullet->frames = BULLET_2_FRAMES;
			new_bullet->height = BULLET_2_HEIGHT;
			new_bullet->width = BULLET_2_WIDTH;
			break;
		case 3:
			new_bullet->hit_box_x = 0.75*BULLET_3_WIDTH;
			new_bullet->hit_box_y = BULLET_3_HEIGHT;
			new_bullet->damage = BULLET_2_DAMAGE/dificulty;
			new_bullet->speed = BULLET_3_MOVE;
			new_bullet->animation_speed = BULLET_3_ANIMATION_SPEED;	
			new_bullet->frames = BULLET_3_FRAMES;	
			new_bullet->height = BULLET_3_HEIGHT;
			new_bullet->width = BULLET_3_WIDTH;			
			break;
	}
	
																														
	new_bullet->trajectory = trajectory;																											
	new_bullet->next = next; 	
	new_bullet->frame_timer = 0;
	new_bullet->current_frame = 0;

	return new_bullet;
}


void bullet_destroy(bullet *element){					
	free(element);					
}

//ja

ja_bullet* ja_bullet_create(float dificulty, unsigned short x, unsigned short y, int trajectory, ja_bullet *next) {

	ja_bullet *new_bullet = (ja_bullet*) malloc(sizeof(ja_bullet));
	if (!new_bullet) return NULL;
	new_bullet->x = x; //porque atira do braço										
	new_bullet->y = y;	
	new_bullet->hit_box_x = JA_BULLET_HEIGHT;
	new_bullet->hit_box_y = JA_BULLET_WIDTH;																														
	new_bullet->trajectory = trajectory;																											
	new_bullet->next = (struct ja_bullet*) next; 	
	new_bullet->frame_timer = 0;
	new_bullet->current_frame = 0;

	new_bullet->damage = JA_BULLET_DAMAGE/dificulty;
	return new_bullet;
}

void ja_bullet_destroy(ja_bullet *element) {					
	free(element);					
}

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