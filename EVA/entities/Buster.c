#include "Buster.h"
#include <stdlib.h>


buster_t *buster_create(float dificulty) {
    buster_t *buster = (buster_t *) malloc (sizeof(buster_t));
    if (!buster) return NULL;
	buster->dificulty = dificulty;
    buster->timer = 0;
    buster->shots = NULL;
    return buster;
}


bullet *buster_shot(unsigned short x, unsigned short y, unsigned char trajectory, buster_t *buster, int type) {
    bullet *new_bullet = bullet_create(buster->dificulty, x,y,trajectory, buster->shots, type);
    if (!new_bullet) return NULL;
    return new_bullet;
}

void buster_destroy(buster_t *buster) {
    bullet *sentinel;
    for (bullet *index = buster->shots; index != NULL; index = sentinel) {
        sentinel = (bullet*) index->next;
        bullet_destroy(index);
    }
    free(buster);
}




void update_player_bullets(float camera_x, buster_t *buster, int X_SCREEN, int level_width) {
	bullet *previous = NULL;
	for (bullet *index = buster->shots; index != NULL;) {
		if (index->trajectory == -1) index->x -= index->speed;
		else if (index->trajectory == 1) index->x += index->speed;

		index->frame_timer++;
		if (index->frame_timer > index->animation_speed) {
			index->frame_timer = 0;
			if (index->current_frame < index->frames - 1)
				index->current_frame++;
			else
				index->current_frame--;
		}

		//margens da fase
		if ((index->x < 0) || (index->x > level_width) || (index->x + BULLET_1_WIDTH < camera_x) || (index->x  > camera_x + X_SCREEN)) {
			if (previous) {
				previous->next = index->next;
				bullet_destroy(index);
				index = (bullet*) previous->next;
			}
			else {
				buster->shots = (bullet*) index->next;
				bullet_destroy(index);
				index = buster->shots;
			}
		}
		else {
			previous = index;
			index = (bullet*) index->next;
		}
	}
}



//ja

void update_ja_bullets(float camera_x, ja_buster_t *ja_buster, int X_SCREEN) {
	ja_bullet *previous = NULL;
	for (ja_bullet *index = ja_buster->shots; index != NULL;) {
		if (index->trajectory == -1) index->x -= JA_BULLET_MOVE;
		else if (index->trajectory == 1) index->x += JA_BULLET_MOVE;

		index->frame_timer++;
		if (index->frame_timer > JA_BULLET_ANIMATION_SPEED) {
			index->frame_timer = 0;
			if (index->current_frame < 3)
				index->current_frame++;
			else
				index->current_frame--;
		}

		//margens da fase
		if ((index->x < 0) || (index->x > 8000) || (index->x + JA_BULLET_WIDTH < camera_x) || (index->x  > camera_x + X_SCREEN)) {
			if (previous) {
				previous->next = index->next;
				ja_bullet_destroy(index);
				index = (ja_bullet*) previous->next;
			}
			else {
				ja_buster->shots = (ja_bullet*) index->next;
				ja_bullet_destroy(index);
				index = ja_buster->shots;
			}
		}
		else {
			previous = index;
			index = (ja_bullet*) index->next;
		}
	}
}

ja_buster_t *ja_buster_create(float dificulty){
	ja_buster_t *ja_buster = (ja_buster_t*) malloc(sizeof(ja_buster_t));
	if (!ja_buster) return NULL;
    ja_buster->timer = 0;
    ja_buster->dificulty = dificulty;
    ja_buster->shots = NULL;
	return ja_buster;
}

ja_bullet* ja_buster_shot(unsigned short x, unsigned short y, unsigned char trajectory, ja_buster_t *ja_buster) {
    ja_bullet *new_bullet = ja_bullet_create(ja_buster->dificulty, x,y,trajectory, ja_buster->shots);
    if (!new_bullet) return NULL;
    return new_bullet;
}

void ja_buster_destroy(ja_buster_t *ja_buster) {
    ja_bullet *sentinel;
    for (ja_bullet *index = ja_buster->shots; index != NULL; index = sentinel) {
        sentinel = (ja_bullet*) index->next;
        ja_bullet_destroy(index);
    }
	free(ja_buster);
}
