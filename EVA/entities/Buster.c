#include "Buster.h"
#include <stdlib.h>


buster_t* buster_create(float dificulty) {
    buster_t *buster = (buster_t *) malloc (sizeof(buster_t));
    if (!buster) return NULL;
	buster->dificulty = dificulty;
    buster->timer = 0;
    buster->shots_1 = NULL;
    buster->shots_2 = NULL;
    buster->shots_3 = NULL;
    return buster;
}


bullet_1* buster_shot_1(unsigned short x, unsigned short y, unsigned char trajectory, buster_t *buster) {
    bullet_1 *new_bullet = bullet_1_create(buster->dificulty, x,y,trajectory, buster->shots_1);
    if (!new_bullet) return NULL;
    return new_bullet;
}

bullet_2* buster_shot_2(unsigned short x, unsigned short y, unsigned char trajectory, buster_t *buster) {
    bullet_2 *new_bullet = bullet_2_create(buster->dificulty, x,y,trajectory, buster->shots_2);
    if (!new_bullet) return NULL;
    return new_bullet;
}

bullet_3* buster_shot_3(unsigned short x, unsigned short y, unsigned char trajectory, buster_t *buster) {
    bullet_3 *new_bullet = bullet_3_create(buster->dificulty, x,y,trajectory, buster->shots_3);
    if (!new_bullet) return NULL;
    return new_bullet;
}


void buster_destroy(buster_t *buster) {
    bullet_1 *sentinel_1;
    for (bullet_1 *index = buster->shots_1; index != NULL; index = sentinel_1) {
        sentinel_1 = (bullet_1*) index->next;
        bullet_1_destroy(index);
    }
    bullet_2 *sentinel_2;
    for (bullet_2 *index = buster->shots_2; index != NULL; index = sentinel_2) {
        sentinel_2 = (bullet_2*) index->next;
        bullet_2_destroy(index);
    }

    bullet_3 *sentinel_3;
    for (bullet_3 *index = buster->shots_3; index != NULL; index = sentinel_3) {
        sentinel_3 = (bullet_3*) index->next;
        bullet_3_destroy(index);
    }
    free(buster);
}

// funções de atualizar os tiros
// por enquanto não estou trabalhando com os sprites do tiro, é só um retangulo por enquanto

void update_bullets_1(float camera_x, buster_t *buster, int X_SCREEN) {
	bullet_1 *previous = NULL;
	for (bullet_1 *index = buster->shots_1; index != NULL;) {
		if (index->trajectory == -1) index->x -= BULLET_MOVE;
		else if (index->trajectory == 1) index->x += BULLET_MOVE;

		index->frame_timer++;
		if (index->frame_timer > BULLET_1_ANIMATION_SPEED) {
			index->frame_timer = 0;
			if (index->current_frame < 8)
				index->current_frame++;
			else
				index->current_frame--;
		}

		//margens da fase
		if ((index->x < 0) || (index->x > 8000) || (index->x + BULLET_1_WIDTH < camera_x) || (index->x  > camera_x + X_SCREEN)) {
			if (previous) {
				previous->next = index->next;
				bullet_1_destroy(index);
				index = (bullet_1*) previous->next;
			}
			else {
				buster->shots_1 = (bullet_1*) index->next;
				bullet_1_destroy(index);
				index = buster->shots_1;
			}
		}
		else {
			previous = index;
			index = (bullet_1*) index->next;
		}
	}
}

void update_bullets_2(float camera_x, buster_t *buster, int X_SCREEN) {
	bullet_2 *previous = NULL;
	for (bullet_2 *index = buster->shots_2; index != NULL;) {
		if (index->trajectory == -1) index->x -= BULLET_MOVE;
		else if (index->trajectory == 1) index->x += BULLET_MOVE;
	
		index->frame_timer++;
		if (index->frame_timer > BULLET_2_ANIMATION_SPEED) {
			index->frame_timer = 0;
			if (index->current_frame < 5)
				index->current_frame++;
			else
				index->current_frame--;
		}

		//margens da fase
		if ((index->x < 0) || (index->x > 8000) || (index->x + BULLET_2_WIDTH < camera_x) || (index->x > camera_x + X_SCREEN)) {
			if (previous) {
				previous->next = index->next;
				bullet_2_destroy(index);
				index = (bullet_2*) previous->next;
			}
			else {
				buster->shots_2 = (bullet_2*) index->next;
				bullet_2_destroy(index);
				index = buster->shots_2;
			}
		}
		else {
			previous = index;
			index = (bullet_2*) index->next;
		}
	}
}

void update_bullets_3(float camera_x, buster_t *buster, int X_SCREEN) {
	bullet_3 *previous = NULL;
	for (bullet_3 *index = buster->shots_3; index != NULL;) {
		if (index->trajectory == -1) index->x -= BULLET_MOVE;
		else if (index->trajectory == 1) index->x += BULLET_MOVE;
	
		index->frame_timer++;
		if (index->frame_timer > BULLET_3_ANIMATION_SPEED) {
			index->frame_timer = 0;
			if (index->current_frame < 4)
				index->current_frame++;
			else
				index->current_frame--;
		}

		//margens da fase
		if ((index->x < 0) || (index->x > 8000) || (index->x + BULLET_3_WIDTH < camera_x) || (index->x > camera_x + X_SCREEN)) {
			if (previous) {
				previous->next = index->next;
				bullet_3_destroy(index);
				index = (bullet_3*) previous->next;
			}
			else {
				buster->shots_3 = (bullet_3*) index->next;
				bullet_3_destroy(index);
				index = buster->shots_3;
			}
		}
		else {
			previous = index;
			index = (bullet_3*) index->next;
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
			if (index->current_frame < 4)
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