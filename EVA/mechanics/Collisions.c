#include "Collisions.h"

#include "../entities/Player.h"
#include "../entities/Jet_alone.h"
#include "../levels/Level_1.h"
#include "../entities/Buster.h"
#include "../entities/Bullet.h"
#include <stdio.h>

//a chave para a chegagem é saber que o centro do jogador não está atualizado, ou seja
//a coordenada x e y é aonde o jogador quer ir e a coordenada center_x center_y fala aonde ele estava
int player_check_collision_with_platform(struct Player *player, Platform *platform) {
    // Coordenadas do frame atual
    float player_x1 = player->x;
    float player_x2 = player->x + EVA_WIDTH;
    float player_y1 = player->y;
    float player_y2 = player->y + EVA_HEIGHT;

    float plat_x1 = platform->x;
    float plat_x2 = platform->x + platform->width;
    float plat_y1 = platform->y;
    float plat_y2 = platform->y + platform->height;

    // 1. Checar se há colisão usando o método AABB correto
    if (player_x2 <= plat_x1 || player_x1 >= plat_x2 || player_y2 <= plat_y1 || player_y1 >= plat_y2) {
        return 0; // Sem colisão
    }

    // 2. Se colidiu, calcular a profundidade da sobreposição em cada eixo
    float overlap_x1 = player_x2 - plat_x1; // Overlap vindo da esquerda
    float overlap_x2 = plat_x2 - player_x1; // Overlap vindo da direita
    float overlap_y1 = player_y2 - plat_y1; // Overlap vindo de cima
    float overlap_y2 = plat_y2 - player_y1; // Overlap vindo de baixo

    // Achar a menor sobreposição para X e Y
    float overlap_x = (overlap_x1 < overlap_x2) ? overlap_x1 : overlap_x2;
    float overlap_y = (overlap_y1 < overlap_y2) ? overlap_y1 : overlap_y2;

    // 3. A direção da colisão é o eixo com a MENOR sobreposição
    if (overlap_y < overlap_x) {
        // --- COLISÃO VERTICAL ---
        
        // Usamos a posição anterior (ou a velocidade) para saber se veio de cima ou de baixo
        // center_y aqui é a posição Y do centro no frame anterior
        if (player->center_y < plat_y1) {
            return 1; // Estava acima e pousou
        } else {
            return 2; // Estava abaixo e bateu a cabeça
        }

    } else {
        // --- COLISÃO HORIZONTAL ---

        // Usamos a posição anterior (ou a velocidade) para saber o lado
        // center_x aqui é a posição X do centro no frame anterior
        if (player->center_x < plat_x1) {
            return 3; // Estava à esquerda e colidiu
        } else {
            return 4; // Estava à direita e colidiu
        }
    }
}

//reposiciona o player de acordo com o tipo de colisão que sofreu
void player_resolve_collision_with_platform(struct Player *player, Platform *platform, int status) {

    //colidiu com a plataforma verticalmente
    if (status == 1) {
        player->y = platform->y - EVA_HEIGHT;
        player->vy = 0;
        player->is_on_ground = 1;
    }
    else if (status == 2) {
        player->y = platform->y + platform->height;
        player->vy = 0;
    }
    else if (status == 3) {
        player->x = platform->x - EVA_WIDTH;
    }
    else if (status == 4) {
        player->x = platform->x + platform->width;
    }
}

//// colisão para o JA

int ja_check_collision_with_platform(struct Jet_alone *ja, Platform *platform) {
    // Coordenadas do frame atual do Jet Alone
    float ja_x1 = ja->x;
    float ja_x2 = ja->x + JA_WIDTH;
    float ja_y1 = ja->y;
    float ja_y2 = ja->y + JA_HEIGHT;

    // Coordenadas da plataforma
    float plat_x1 = platform->x;
    float plat_x2 = platform->x + platform->width;
    float plat_y1 = platform->y;
    float plat_y2 = platform->y + platform->height;

    // 1. Checar se há colisão usando o método AABB
    if (ja_x2 <= plat_x1 || ja_x1 >= plat_x2 || ja_y2 <= plat_y1 || ja_y1 >= plat_y2) {
        return 0; // Sem colisão
    }

    // 2. Se colidiu, calcular a profundidade da sobreposição em cada eixo
    float overlap_x1 = ja_x2 - plat_x1;
    float overlap_x2 = plat_x2 - ja_x1;
    float overlap_y1 = ja_y2 - plat_y1;
    float overlap_y2 = plat_y2 - ja_y1;

    // Achar a menor sobreposição para X e Y
    float overlap_x = (overlap_x1 < overlap_x2) ? overlap_x1 : overlap_x2;
    float overlap_y = (overlap_y1 < overlap_y2) ? overlap_y1 : overlap_y2;

    // 3. A direção da colisão é o eixo com a MENOR sobreposição
    if (overlap_y < overlap_x) {
        // --- COLISÃO VERTICAL ---
        // Usa a posição anterior para saber se veio de cima ou de baixo
        if (ja->center_y < plat_y1) {
            return 1; // Estava acima e pousou
        } else {
            return 2; // Estava abaixo e bateu a cabeça
        }
    } else {
        // --- COLISÃO HORIZONTAL ---
        // Usa a posição anterior para saber o lado
        if (ja->center_x < plat_x1) {
            return 3; // Estava à esquerda e colidiu
        } else {
            return 4; // Estava à direita e colidiu
        }
    }
}

void ja_resolve_collision_with_platform(struct Jet_alone *ja, Platform *platform, int status) {
    switch (status) {
        case 1: // Pousou no topo
            ja->y = platform->y - JA_HEIGHT;
            ja->vy = 0;
            ja->is_on_ground = 1;
            break;
        case 2: // Bateu a cabeça
            ja->y = platform->y + platform->height;
            ja->vy = 0;
            break;
        case 3: // Colidiu vindo da esquerda
            ja->x = platform->x - JA_WIDTH;
            break;
        case 4: // Colidiu vindo da direita
            ja->x = platform->x + platform->width;
            break;
        // default: não faz nada se status for 0
    }
}

// colisão de tiros e inimigos


void check_player_hit_by_ja_bullets(Player *player, Jet_alone **jet_alones, int ja_num, unsigned char *did_jet_died, unsigned char *did_jet_spawn) {
    if (player->is_invincible || player->life <= 0) {
        return;
    }

    float player_x1 = player->center_x - player->hit_box_x / 2;
    float player_x2 = player->center_x + player->hit_box_x / 2;
    float player_y1 = player->center_y - player->hit_box_y / 2;
    float player_y2 = player->center_y + player->hit_box_y / 2;

    for (int i = 0; i < ja_num; i++) {
        Jet_alone *current_ja = jet_alones[i];

        if (did_jet_spawn[i] && !did_jet_died[i]) {

            struct ja_bullet *prev = NULL;
            struct ja_bullet *current = current_ja->ja_buster->shots;

            while (current) {
                float bullet_x1 = current->x;
                float bullet_x2 = current->x + current->hit_box_x;
                float bullet_y1 = current->y;
                float bullet_y2 = current->y + current->hit_box_y;

                unsigned char no_collision = (player_x2 <= bullet_x1 || player_x1 >= bullet_x2 ||
                                              player_y2 <= bullet_y1 || player_y1 >= bullet_y2);

                if (no_collision) {
                    prev = current;
                    current = current->next;
                } else {
                    player->life -= current->damage;
                    player->damage_direction = current->trajectory;
                    player->is_taking_damage = 1;

                    struct ja_bullet *bullet_to_remove = current;

                    if (prev) {
                        prev->next = current->next;
                    } else {
                        current_ja->ja_buster->shots = current->next;
                    }

                    current = current->next;
                    ja_bullet_destroy(bullet_to_remove);
                }
            }
        }
    }
}

void check_player_collision_with_ja(struct Player *player, struct Jet_alone **jet_alones, int ja_num, unsigned char *did_jet_died, unsigned char *did_jet_spawn) {
    
    // Se o jogador já estiver invencível ou morto, não há necessidade de checar nada.
    if (player->is_invincible || player->life <= 0) {
        return;
    }

    float player_x1 = player->center_x - player->hit_box_x / 2;
    float player_x2 = player->center_x + player->hit_box_x / 2;
    float player_y1 = player->center_y - player->hit_box_y / 2;
    float player_y2 = player->center_y + player->hit_box_y / 2;

    for (int i = 0; i < ja_num; i++) {
        Jet_alone *current_ja = jet_alones[i];

        // Verifica se o inimigo está ativo na fase
        if (did_jet_spawn[i] && !did_jet_died[i]) {

            // Pega a hitbox do Jet Alone
            float ja_x1 = current_ja->center_x - current_ja->hit_box_x/2; 
            float ja_x2 = current_ja->center_x + current_ja->hit_box_x/2; 
            float ja_y1 = current_ja->center_y - current_ja->hit_box_x/2; 
            float ja_y2 = current_ja->center_y + current_ja->hit_box_y; 

            // Checagem de colisão (AABB - Axis-Aligned Bounding Box)
            unsigned char no_collision = (player_x2 <= ja_x1 || player_x1 >= ja_x2 ||
                                          player_y2 <= ja_y1 || player_y1 >= ja_y2);

            if (!no_collision) {
                
                // Aplica o dano e ativa o estado "levando dano"
                player->life -= JA_CONTACT_DAMAGE;
                player->is_taking_damage = 1;

                // Determina a direção do recuo (knockback)
                // Se o centro do jogador está à esquerda do centro do inimigo, o jogador é empurrado para a esquerda (-1)
                if (player->center_x < current_ja->center_x) {
                    player->damage_direction = -1;
                } else {
                    player->damage_direction = 1;
                }
            }
        }
    }
}


void check_ja_hit_by_player_bullets(struct Player *player, struct Jet_alone **jet_alones, int ja_num, unsigned char *did_jet_died, unsigned char *did_jet_spawn) {

    for (int i = 0; i < ja_num; i++) {
        Jet_alone *current_ja = jet_alones[i];


        if (did_jet_spawn[i] && !did_jet_died[i]) {


            float ja_x1 = current_ja->center_x - current_ja->hit_box_x / 2;
            float ja_x2 = current_ja->center_x + current_ja->hit_box_x / 2;
            float ja_y1 = current_ja->center_y - current_ja->hit_box_y / 2;
            float ja_y2 = current_ja->center_y + current_ja->hit_box_y / 2;
            

            bullet *prev_bullet = NULL;
            bullet *current_bullet = player->buster->shots;

            // Loop para percorrer todas as balas ativas do jogador
            while (current_bullet) {
                // Calcula a hitbox da bala atual
                float bullet_x1 = current_bullet->x;
                float bullet_x2;
                if (current_bullet->type == 3 && current_bullet->current_frame < 2) // no tipo de bala 3 a hitbox é menor
                    bullet_x2 = current_bullet->x + 0.5*current_bullet->hit_box_x;
                else
                    bullet_x2 = current_bullet->x + current_bullet->hit_box_x;
                float bullet_y1 = current_bullet->y;
                float bullet_y2 = current_bullet->y + current_bullet->hit_box_y;

                // Lógica de colisão AABB. Se "no_collision" for verdadeiro, não houve colisão.
                unsigned char no_collision = (ja_x2 <= bullet_x1 || ja_x1 >= bullet_x2 ||
                                              ja_y2 <= bullet_y1 || ja_y1 >= bullet_y2);
                
                if (no_collision) {
                    // Se não houve colisão, apenas avança na lista
                    prev_bullet = current_bullet;
                    current_bullet = current_bullet->next;
                } else {

                    current_ja->life -= current_bullet->damage;
                    current_ja->is_taking_damage = 1;

                    // Verifica se o Jet_alone morreu após o dano
                    //tem que dar free
                    if (current_ja->life <= 0) {
                        did_jet_died[i] = 1; 
                    }


                    bullet *bullet_to_remove = current_bullet;
                    current_bullet = current_bullet->next; 

                    if (prev_bullet)
                        prev_bullet->next = current_bullet;
                     else 
                        player->buster->shots = current_bullet;
                
                    bullet_destroy(bullet_to_remove);
                }
            }
        }
    }
}