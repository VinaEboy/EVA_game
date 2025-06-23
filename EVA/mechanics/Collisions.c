#include "Collisions.h"

#include "../entities/Player.h"
#include "../entities/Jet_alone.h"
#include "../levels/Level_1.h"
#include "../entities/Buster.h"
#include "../entities/Bullet.h"
#include <stdio.h>

//////////////////////// COLISOES COM PLATAFORMAS //////////////////////////////////////////
// verifica colisão usando o método AABB (é mais fácil verificar se não colidiu do que se colidiu)

//status 0: não colidiu
//status 1: Estava acima da plataforma e colidiu
//status 2: Estava abaixo da plataforma e colidiu (como se fosse um teto)
//status 3: Estava no lado esquerdo da plataforma e colidiu
//status 4: Estava no lado direito da plataforma e colidiu


// verifica se o player colidiu usando o método AABB 
// e retorna um inteiro que é o status de colisão (se não colidiu ou de qual direção o player veio e colidiu)
// para saber de onde veio, faz checagem por sobreposição (assume que sobrepos perto de onde veio)
int player_check_collision_with_platform(struct Player *player, Platform *platform) {
    // Coordenadas do frame atual do jogador
    float player_x1 = player->x;
    float player_x2 = player->x + player->width;
    float player_y1 = player->y;
    float player_y2 = player->y + player->height;

    // Coordenadas da plataforma
    float plat_x1 = platform->x;
    float plat_x2 = platform->x + platform->width;
    float plat_y1 = platform->y;
    float plat_y2 = platform->y + platform->height;

    // Verifica pelo método AABB  se o player está com certeza fora da plataforma
    if (player_x2 <= plat_x1 || player_x1 >= plat_x2 || player_y2 <= plat_y1 || player_y1 >= plat_y2) 
        return 0; // Sem colisão
    

    // Se colidiu, calcular a profundidade da sobreposição em cada eixo
    float overlap_x1 = player_x2 - plat_x1; // da esquerda
    float overlap_x2 = plat_x2 - player_x1; // da direita
    float overlap_y1 = player_y2 - plat_y1; // de cima
    float overlap_y2 = plat_y2 - player_y1; // de baixo

    // Achar a menor sobreposição para X 
    float overlap_x;
    if (overlap_x1 < overlap_x2) overlap_x = overlap_x1;
    else overlap_x = overlap_x2;

    // Achar a menor sobreposição para Y
    float overlap_y;
    if (overlap_y1 < overlap_y2) overlap_y = overlap_y1 ;
    else overlap_y = overlap_y2;;

    // A direção da colisão é o eixo com a MENOR sobreposição
    if (overlap_y < overlap_x) {
        // Colisão vertical
        
        // Usamos a posição anterior para saber se veio de cima ou de baixo
        // center_y aqui é a posição Y do centro no frame anterior
        if (player->center_y < plat_y1) 
            return 1; // Estava acima e pousou
        else 
            return 2; // Estava abaixo e bateu a cabeça

    } else {
        // Colisão horizontal

        // Usamos a posição anterior para saber o lado
        // center_x aqui é a posição X do centro no frame anterior
        if (player->center_x < plat_x1) 
            return 3; // Estava à esquerda e colidiu
        else 
            return 4; // Estava à direita e colidiu
        
    }
}


// caso tenha colisão, ele resolve essa colisão jogando o player de volta de onde ele veio
// Para arrumar a colisão precisa saber do status do player
void player_resolve_collision_with_platform(struct Player *player, Platform *platform, int status) {

    //Estava acima da plataforma e colidiu
    if (status == 1) {
        player->y = platform->y - player->height;
        player->vy = 0;
        player->is_on_ground = 1;
    }

    // Estava abaixo da plataforma e colidiu (como se fosse um teto)
    else if (status == 2) {
        player->y = platform->y + platform->height;
        player->vy = 0;
    }

    // Estava no lado esquerdo da plataforma e colidiu
    else if (status == 3) {
        player->x = platform->x - player->width;
    }

    // Estava no lado direito da plataforma e colidiu
    else if (status == 4) {
        player->x = platform->x + platform->width;
    }
}

//// colisão para o JA
int ja_check_collision_with_platform(struct Jet_alone *ja, Platform *platform) {
    // Coordenadas do frame atual do Jet Alone
    float ja_x1 = ja->x;
    float ja_x2 = ja->x + ja->width;
    float ja_y1 = ja->y;
    float ja_y2 = ja->y + ja->height;

    // Coordenadas da plataforma
    float plat_x1 = platform->x;
    float plat_x2 = platform->x + platform->width;
    float plat_y1 = platform->y;
    float plat_y2 = platform->y + platform->height;

    // Checar se há colisão usando o método AABB
    if (ja_x2 <= plat_x1 || ja_x1 >= plat_x2 || ja_y2 <= plat_y1 || ja_y1 >= plat_y2) 
        return 0; // Sem colisão
    

    // Se colidiu, calcular a profundidade da sobreposição em cada eixo
    float overlap_x1 = ja_x2 - plat_x1;
    float overlap_x2 = plat_x2 - ja_x1;
    float overlap_y1 = ja_y2 - plat_y1;
    float overlap_y2 = plat_y2 - ja_y1;

    // Achar a menor sobreposição para X 
    float overlap_x;
    if (overlap_x1 < overlap_x2) overlap_x = overlap_x1;
    else overlap_x = overlap_x2;

    // Achar a menor sobreposição para Y
    float overlap_y;
    if (overlap_y1 < overlap_y2) overlap_y = overlap_y1 ;
    else overlap_y = overlap_y2;;

    // A direção da colisão é o eixo com a menor sobreposição
    if (overlap_y < overlap_x) {
        // colisão vertical

        // Usa a posição anterior para saber se veio de cima ou de baixo
        if (ja->center_y < plat_y1) 
            return 1; // Estava acima e pousou
        else 
            return 2; // Estava abaixo e bateu a cabeça
        
    } else {
        // colisão horizontal

        // Usa a posição anterior para saber o lado
        if (ja->center_x < plat_x1) 
            return 3; // Estava à esquerda e colidiu
        else 
            return 4; // Estava à direita e colidiu
        
    }
}

// com base no status resolve a colisão
void ja_resolve_collision_with_platform(struct Jet_alone *ja, Platform *platform, int status) {
    switch (status) {
        case 1: // Pousou no topo
            ja->y = platform->y - ja->height;
            ja->vy = 0;
            ja->is_on_ground = 1;
            break;
        case 2: // Bateu a cabeça
            ja->y = platform->y + platform->height;
            ja->vy = 0;
            break;
        case 3: // Colidiu vindo da esquerda
            ja->x = platform->x - ja->width;
            break;
        case 4: // Colidiu vindo da direita
            ja->x = platform->x + platform->width;
            break;
        // default: não faz nada se status for 0
    }
}

///////////////////////////// COLISÃO DE TIROS E INIMIGOS ////////////////////////////////////

// verifica se o player levou dano de uma das balas de um inimigo JA
void check_player_hit_by_ja_bullets(Player *player, Jet_alone **jet_alones, int ja_num, unsigned char *did_jet_died, unsigned char *did_jet_spawn) {
    if (player->is_invincible || player->life <= 0) 
        return;

    float player_x1 = player->center_x - player->hit_box_x / 2;
    float player_x2 = player->center_x + player->hit_box_x / 2;
    float player_y1 = player->center_y - player->hit_box_y / 2;
    float player_y2 = player->center_y + player->hit_box_y / 2;

    //verifica todos os inimigos da fase
    for (int i = 0; i < ja_num; i++) {
        Jet_alone *current_ja = jet_alones[i];

        //verifica se tá spawnado e vivo e percorre a lista encadeada que é os tiros
        if (did_jet_spawn[i] && !did_jet_died[i]) {

            struct ja_bullet *prev = NULL;
            struct ja_bullet *current = current_ja->ja_buster->shots;

            //enquanto tiver bullet na fila encadeada, verifica
            while (current) {
                float bullet_x1 = current->x;
                float bullet_x2 = current->x + current->hit_box_x;
                float bullet_y1 = current->y;
                float bullet_y2 = current->y + current->hit_box_y;

                //AABB
                unsigned char no_collision = (player_x2 <= bullet_x1 || player_x1 >= bullet_x2 ||
                                              player_y2 <= bullet_y1 || player_y1 >= bullet_y2);

                // vai pro próximo da fila
                if (no_collision) {
                    prev = current;
                    current = current->next;
                } else {
                    // desconta dano
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

// verifica se o player colidiu com o JA
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

// verifica se o JA foi atingido por uma das balas
void check_ja_hit_by_player_bullets(struct Player *player, struct Jet_alone **jet_alones, int ja_num, unsigned char *did_jet_died, unsigned char *did_jet_spawn) {

    for (int i = 0; i < ja_num; i++) {
        Jet_alone *current_ja = jet_alones[i];

        //se tiver vivo ou spawnado
        if (did_jet_spawn[i] && !did_jet_died[i]) {


            float ja_x1 = current_ja->center_x - current_ja->hit_box_x / 2;
            float ja_x2 = current_ja->center_x + current_ja->hit_box_x / 2;
            float ja_y1 = current_ja->center_y - current_ja->hit_box_y*0.4;
            float ja_y2 = current_ja->center_y + current_ja->hit_box_y*0.65;
            

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

                // Lógica de colisão AABB. 
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

/////// Chefão da primeira fase, Sachiel
// verifica se o player levou tiro do SA
void check_player_hit_by_sa_bullets(struct Player *player, struct Sachiel *sa) {
    if (player->is_invincible || player->life <= 0) {
        return;
    }

    float player_x1 = player->center_x - player->hit_box_x / 2;
    float player_x2 = player->center_x + player->hit_box_x / 2;
    float player_y1 = player->center_y - player->hit_box_y / 2;
    float player_y2 = player->center_y + player->hit_box_y / 2;

    //percore a lista encadeada que é os tiros do Sachiel
    if (sa && sa->life > 0) {
        struct sa_bullet *prev = NULL;
        struct sa_bullet *current = sa->sa_buster->shots;

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

                struct sa_bullet *bullet_to_remove = current;

                if (prev) {
                    prev->next = current->next;
                } else {
                    sa->sa_buster->shots = current->next;
                }

                current = current->next;
                sa_bullet_destroy(bullet_to_remove);
            }
        }
    }
}

// Verifica se o CORAÇÃO do Sachiel levou dano
void check_sachiel_hit_by_player_bullets(struct Player *player, struct Sachiel *sa) {
    if (sa->is_invencible || sa->life <= 0) {
        return;
    }

    float sachiel_x1 = sa->x;
    float sachiel_x2 = sa->x + sa->hit_box_x;
    float sachiel_y1 = sa->y;
    float sachiel_y2 = sa->y + sa->hit_box_y;
    
    struct bullet *prev = NULL;
    struct bullet *current = player->buster->shots;

    while (current) {
        float bullet_x1 = current->x;
        float bullet_x2 = current->x + current->hit_box_x;
        float bullet_y1 = current->y;
        float bullet_y2 = current->y + current->hit_box_y;

        unsigned char no_collision = (sachiel_x2 <= bullet_x1 || sachiel_x1 >= bullet_x2 ||
                                      sachiel_y2 <= bullet_y1 || sachiel_y1 >= bullet_y2);
        
        if (no_collision) {
            prev = current;
            current = (struct bullet*)current->next;
        } else {
            sa->life -= current->damage;
            sa->hit_take = 1;

            struct bullet *bullet_to_remove = current;

            if (prev) {
                prev->next = current->next;
            } else {
                player->buster->shots = (struct bullet*)current->next;
            }

            current = (struct bullet*)current->next;
            bullet_destroy(bullet_to_remove);
        }
    }
}

// Verifica se o jogador chegou perto do coração do Sachiel para levar dano
void check_player_collision_with_sachiel(struct Player *player, struct Sachiel *sa) {
    if (player->is_invincible || player->life <= 0 || sa->life <= 0) {
        return;
    }

    float player_x1 = player->center_x - player->hit_box_x / 2;
    float player_x2 = player->center_x + player->hit_box_x / 2;
    float player_y1 = player->center_y - player->hit_box_y / 2;
    float player_y2 = player->center_y + player->hit_box_y / 2;

    float sachiel_x1 = sa->x;
    float sachiel_x2 = sa->x + sa->hit_box_x;
    float sachiel_y1 = sa->y;
    float sachiel_y2 = sa->y + sa->hit_box_y;

    unsigned char no_collision = (player_x2 <= sachiel_x1 || player_x1 >= sachiel_x2 ||
                                  player_y2 <= sachiel_y1 || player_y1 >= sachiel_y2);

    if (!no_collision) {
        player->life -= sa->damage;
        player->is_taking_damage = 1;

        if (player->center_x < sa->center_x) 
            player->damage_direction = -1;
        else 
            player->damage_direction = 1;
    }
}