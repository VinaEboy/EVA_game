#ifndef __DRAW__
#define __DRAW__

#define LIFE_BAR_X 100
#define LIFE_BAR_Y 10
#define LIFE_BAR_WIDTH 150
#define LIFE_BAR_HEIGHT 400
#define HEALTH_FILL_MAX_WIDTH 15
#define HEALTH_FILL_MAX_HEIGHT 216
#define HEALTH_FILL_OFFSET_X 54
#define HEALTH_FILL_OFFSET_Y 68

#include "../entities/Player.h"
#include "../gameflow/Assets.h"
#include "../entities/Jet_alone.h"


void draw_player(float camera_x, Player *player, entities_sprites *sprites);

void draw_level_1_background(float camera_x, entities_sprites *sprites, int X_SCREEN, int Y_SCREEN, float FLOOR);

void draw_bullets(float camera_x, Player *player,entities_sprites *sprites);

void draw_level_1_ground(float camera_x, Platform *current_platform, entities_sprites *sprites, int X_SCREEN, int Y_SCREEN);

// AUXILIARES
void draw_charging_EVA(float camera_x, Player *player, ALLEGRO_COLOR *tint_color, entities_sprites *sprites);

void draw_life_bar_EVA(float camera_x, Player *player, entities_sprites *sprites );

void draw_player_death(float camera_x, Player *player, entities_sprites *sprites);
// JA

void draw_ja(float camera_x, Jet_alone *ja, entities_sprites *sprites);
void draw_ja_bullets(float camera_x, Jet_alone *ja,entities_sprites *sprites);
#endif