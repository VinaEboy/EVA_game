#ifndef __COLLISIONS__
#define __COLLISIONS__

#include "Objects.h"

struct Player;
struct Jet_alone;
struct Sachiel;

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
int player_check_collision_with_platform(struct Player *player, Platform *platform);

// caso tenha colisão, ele resolve essa colisão jogando o player de volta de onde ele veio
// Para arrumar a colisão precisa saber do status do player
void player_resolve_collision_with_platform(struct Player *player, Platform *platform, int status);

// JA

//// colisão para o JA
int ja_check_collision_with_platform(struct Jet_alone *ja, Platform *platform);

// com base no status resolve a colisão
void ja_resolve_collision_with_platform(struct Jet_alone *ja, Platform *platform, int status);

///////////////////////////// COLISÃO DE TIROS E INIMIGOS ////////////////////////////////////


// verifica se o player levou dano de uma das balas de um inimigo JA
void check_player_hit_by_ja_bullets(struct Player *player, struct Jet_alone **jet_alones, int ja_num, unsigned char *did_jet_died, unsigned char *did_jet_spawn);

// verifica se o player colidiu com o JA
void check_player_collision_with_ja(struct Player *player, struct Jet_alone **jet_alones, int ja_num, unsigned char *did_jet_died, unsigned char *did_jet_spawn);

// verifica se o JA foi atingido por uma das balas
void check_ja_hit_by_player_bullets(struct Player *player, struct Jet_alone **jet_alones, int ja_num, unsigned char *did_jet_died, unsigned char *did_jet_spawn);

// COLISAO SACHIEL

// verifica se o player levou tiro do SA
void check_player_hit_by_sa_bullets(struct Player *player, struct Sachiel *sa);

// Verifica se o CORAÇÃO do Sachiel levou dano
void check_sachiel_hit_by_player_bullets(struct Player *player, struct Sachiel *sa);

// Verifica se o jogador chegou perto do coração do Sachiel para levar dano
void check_player_collision_with_sachiel(struct Player *player, struct Sachiel *sa);

#endif
