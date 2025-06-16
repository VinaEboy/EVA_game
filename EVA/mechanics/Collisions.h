#ifndef __COLLISIONS__
#define __COLLISIONS__

#include "Objects.h"

struct Player;
struct Jet_alone;

/// COLISOES
//status 0: não colidiu
//status 1: Estava acima da plataforma e colidiu
//status 2: Estava abaixo da plataforma e colidiu (como se fosse um teto)
//status 3: Estava no lado esquerdo da plataforma e colidiu
//status 4: Estava no lado direito da plataforma e colidiu

int player_check_collision_with_platform(struct Player *player, Platform *platform);

void player_resolve_collision_with_platform(struct Player *player, Platform *platform, int status);

// JA

int ja_check_collision_with_platform(struct Jet_alone *ja, Platform *platform);

void ja_resolve_collision_with_platform(struct Jet_alone *ja, Platform *platform, int status);

// colisao de tiro
void check_player_hit_by_ja_bullets(struct Player *player, struct Jet_alone **jet_alones, int ja_num, unsigned char *did_jet_died, unsigned char *did_jet_spawn);

void check_player_collision_with_ja(struct Player *player, struct Jet_alone **jet_alones, int ja_num, unsigned char *did_jet_died, unsigned char *did_jet_spawn);

void check_ja_hit_by_player_bullets(struct Player *player, struct Jet_alone **jet_alones, int ja_num, unsigned char *did_jet_died, unsigned char *did_jet_spawn);

#endif
