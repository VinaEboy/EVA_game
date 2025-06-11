#include "Buster.h"
#include <stdlib.h>

buster_t* buster_create() {
    buster_t *buster = (buster_t *) malloc (sizeof(buster_t));
    if (!buster) return NULL;
    buster->timer = 0;
    buster->shots_1 = NULL;
    buster->shots_2 = NULL;
    buster->shots_3 = NULL;
    return buster;
}


bullet_1* buster_shot_1(unsigned short x, unsigned short y, unsigned char trajectory, buster_t *buster) {
    bullet_1 *new_bullet = bullet_1_create(x,y,trajectory, buster->shots_1);
    if (!new_bullet) return NULL;
    return new_bullet;
}

bullet_2* buster_shot_2(unsigned short x, unsigned short y, unsigned char trajectory, buster_t *buster) {
    bullet_2 *new_bullet = bullet_2_create(x,y,trajectory, buster->shots_2);
    if (!new_bullet) return NULL;
    return new_bullet;
}

bullet_3* buster_shot_3(unsigned short x, unsigned short y, unsigned char trajectory, buster_t *buster) {
    bullet_3 *new_bullet = bullet_3_create(x,y,trajectory, buster->shots_3);
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

void update_bullets_1(buster_t *buster) {
	bullet_1 *previous = NULL;
	for (bullet_1 *index = buster->shots_1; index != NULL;) {
		if (!index->trajectory) index->x -= BULLET_MOVE;
		else if (index->trajectory == 1) index->x += BULLET_MOVE;

		//margens da fase
		if ((index->x < 0) || (index->x > 8000)) {
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

void update_bullets_2(buster_t *buster) {
	bullet_2 *previous = NULL;
	for (bullet_2 *index = buster->shots_2; index != NULL;) {
		if (!index->trajectory) index->x -= BULLET_MOVE;
		else if (index->trajectory == 1) index->x += BULLET_MOVE;
	

		//margens da fase
		if ((index->x < 0) || (index->x > 8000)) {
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

void update_bullets_3(buster_t *buster) {
	bullet_3 *previous = NULL;
	for (bullet_3 *index = buster->shots_3; index != NULL;) {
		if (!index->trajectory) index->x -= BULLET_MOVE;
		else if (index->trajectory == 1) index->x += BULLET_MOVE;
	

		//margens da fase
		if ((index->x < 0) || (index->x > 8000)) {
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