#include "Buster.h"
#include <stdlib.h>

// buster do jogador
buster_t *buster_create(float dificulty) {
    buster_t *buster = (buster_t *) malloc (sizeof(buster_t));
    if (!buster) return NULL;
	buster->dificulty = dificulty;
    buster->timer = 0;
    buster->shots = NULL;
    return buster;
}

// enfileira o tiro na fila encadeada
bullet *buster_shot(unsigned short x, unsigned short y, unsigned char trajectory, buster_t *buster, int type, int X_SCREEN, int Y_SCREEN) {
    bullet *new_bullet = bullet_create(buster->dificulty,x,y,trajectory, buster->shots, type, X_SCREEN, Y_SCREEN);
    if (!new_bullet) return NULL;
    return new_bullet;
}

// libera memória
void buster_destroy(buster_t *buster) {
    bullet *sentinel;
    for (bullet *index = buster->shots; index != NULL; index = sentinel) {
        sentinel = (bullet*) index->next;
        bullet_destroy(index);
    }
    free(buster);
}


// atualiza as posições do tiro 
void update_player_bullets(float camera_x, buster_t *buster, int X_SCREEN, int level_width) {
	bullet *previous = NULL;
	for (bullet *index = buster->shots; index != NULL;) {
		if (index->trajectory == -1) index->x -= index->speed;
		else if (index->trajectory == 1) index->x += index->speed;
		else if (index->trajectory == 2) index->y -= index->speed;

		index->frame_timer++;
		if (index->frame_timer > index->animation_speed) {
			index->frame_timer = 0;
			if (index->current_frame < index->frames - 1)
				index->current_frame++;
			else
				index->current_frame--;
		}

		//margens da fase
		if ((index->x < 0) || (index->x > level_width) || (index->x + index->width < camera_x) || (index->x  > camera_x + X_SCREEN) || index->y < 0) {
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

//////// JA

// atualiza posições
void update_ja_bullets(float camera_x, ja_buster_t *ja_buster, int X_SCREEN) {
	ja_bullet *previous = NULL;
	for (ja_bullet *index = ja_buster->shots; index != NULL;) {
		if (index->trajectory == -1) index->x -= index->speed;
		else if (index->trajectory == 1) index->x += index->speed;

		index->frame_timer++;
		if (index->frame_timer > JA_BULLET_ANIMATION_SPEED) {
			index->frame_timer = 0;
			index->current_frame = (index->current_frame + 1) % 4;
		}

		//margens da fase
		if ((index->x < 0) || (index->x > 8000) || (index->x + index->width < camera_x) || (index->x  > camera_x + X_SCREEN)) {
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

// cria o sentinela
ja_buster_t *ja_buster_create(float dificulty, float speed){
	ja_buster_t *ja_buster = (ja_buster_t*) malloc(sizeof(ja_buster_t));
	if (!ja_buster) return NULL;
    ja_buster->bullet_speed = speed;
    ja_buster->timer = 0;
    ja_buster->dificulty = dificulty;
    ja_buster->shots = NULL;
	return ja_buster;
}

// enfileira tiro
ja_bullet* ja_buster_shot(unsigned short x, unsigned short y, unsigned char trajectory, ja_buster_t *ja_buster, int X_SCREEN, int Y_SCREEN) {
    ja_bullet *new_bullet = ja_bullet_create(ja_buster->dificulty,ja_buster->bullet_speed, x,y,trajectory, ja_buster->shots, X_SCREEN, Y_SCREEN);
    if (!new_bullet) return NULL;
    return new_bullet;
}

// libera memória
void ja_buster_destroy(ja_buster_t *ja_buster) {
    ja_bullet *sentinel;
    for (ja_bullet *index = ja_buster->shots; index != NULL; index = sentinel) {
        sentinel = (ja_bullet*) index->next;
        ja_bullet_destroy(index);
    }
	free(ja_buster);
}

/////////////////////////////// SACHIEL

// cria buster do sachiel
sa_buster_t *sa_buster_create(float dificulty) {
    sa_buster_t *sa_buster = (sa_buster_t *) malloc(sizeof(sa_buster_t));
    if (!sa_buster) return NULL;

    sa_buster->dificulty = dificulty;
    sa_buster->timer = 0;
    sa_buster->shots = NULL;

    return sa_buster;
}

// enfileira tiro
sa_bullet *sa_buster_shot(int speed, unsigned short x, unsigned short y, unsigned char trajectory, sa_buster_t *sa_buster,int X_SCREEN, int Y_SCREEN, int type) {
    sa_bullet *new_bullet = sa_bullet_create(sa_buster->dificulty, speed, x, y, trajectory, sa_buster->shots, X_SCREEN, Y_SCREEN, type);
    if (!new_bullet) return NULL;
    sa_buster->shots = new_bullet;

    return new_bullet;
}

// libera memória
void sa_buster_destroy(sa_buster_t *sa_buster) {
    if (!sa_buster) return;

    sa_bullet *sentinel;
    for (sa_bullet *index = sa_buster->shots; index != NULL; index = sentinel) {
        sentinel = (sa_bullet*) index->next;
        sa_bullet_destroy(index);
    }
    free(sa_buster);
}

// atualiza posições
void update_sa_bullets(float camera_x, sa_buster_t *sa_buster, int X_SCREEN, int level_width) {
    sa_bullet *previous = NULL;
    for (sa_bullet *index = sa_buster->shots; index != NULL;) {
        if (index->trajectory == -1) index->x -= index->speed;      // Esquerda
        else if (index->trajectory == 1) index->x += index->speed;  // Direita
        else if (index->trajectory == 2) index->y += index->speed;  // Baixo


        index->frame_timer++;
        if (index->frame_timer > SA_BULLET_ANIMATION_SPEED) { 
            index->frame_timer = 0;
            index->current_frame = (index->current_frame + 1) % 2; 
        }

        if ((index->x < 0) || (index->x > level_width) || (index->x + index->hit_box_x < camera_x) || (index->x > camera_x + X_SCREEN) || index->y < 0) {
            sa_bullet *temp_to_destroy = index;
            if (previous) {
                previous->next = index->next;
                index = (sa_bullet*) previous->next;
            } else {
                sa_buster->shots = (sa_bullet*) index->next;
                index = sa_buster->shots;
            }
            sa_bullet_destroy(temp_to_destroy);
        } else {
            previous = index;
            index = (sa_bullet*) index->next;
        }
    }
}
