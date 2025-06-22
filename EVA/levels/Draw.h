#ifndef __DRAW__
#define __DRAW__

#define RATIO_LIFE_BAR_X 0.035
#define RATIO_LIFE_BAR_Y 0.08
#define RATIO_LIFE_BAR_WIDTH 0.12
#define RATIO_LIFE_BAR_HEIGHT 0.45

#define RATIO_HEALTH_FILL_MAX_WIDTH 0.014
#define RATIO_HEALTH_FILL_MAX_HEIGHT 0.245
#define RATIO_HEALTH_FILL_OFFSET_X 0.042
#define RATIO_HEALTH_FILL_OFFSET_Y 0.076

// defines do SA
#define SA_RATIO_LIFE_BAR_X 0.88
#define SA_RATIO_LIFE_BAR_Y 0.03
#define SA_RATIO_LIFE_BAR_WIDTH 0.12
#define SA_RATIO_LIFE_BAR_HEIGHT 0.55

#define SA_RATIO_HEALTH_FILL_MAX_WIDTH 0.012
#define SA_RATIO_HEALTH_FILL_MAX_HEIGHT 0.345
#define SA_RATIO_HEALTH_FILL_OFFSET_X 0.052
#define SA_RATIO_HEALTH_FILL_OFFSET_Y 0.045


#include "../entities/Player.h"
#include "../gameflow/Assets.h"
#include "../gameflow/Game_state.h"
#include "../entities/Jet_alone.h"
#include "../entities/Sachiel.h"
#include <allegro5/allegro_font.h>	


void draw_player(ALLEGRO_FONT *font,game_state *state,float camera_x, Player *player, entities_sprites *sprites, int X_SCREEN, int Y_SCREEN);
void draw_level_1_background(float camera_x, entities_sprites *sprites, int X_SCREEN, int Y_SCREEN, float FLOOR);
void draw_bullets(float camera_x, Player *player,entities_sprites *sprites);
void draw_platform(float camera_x, Platform *current_platform, ALLEGRO_BITMAP *platform_image, int X_SCREEN, int Y_SCREEN);

// AUXILIARES
void draw_charging_EVA(float camera_x, Player *player, ALLEGRO_COLOR *tint_color, entities_sprites *sprites);
void draw_life_bar_EVA(ALLEGRO_FONT *font,game_state *state,float camera_x, Player *player, entities_sprites *sprites, int X_SCREEN, int Y_SCREEN );
void draw_player_death(float camera_x, Player *player, entities_sprites *sprites);

// JA

void draw_ja(float camera_x, Jet_alone *ja, entities_sprites *sprites);
void draw_ja_bullets(float camera_x, Jet_alone *ja,entities_sprites *sprites);

// Sachiel (chefão)

void draw_sa(float camera_x, Sachiel *sa, entities_sprites *sprites, int X_SCREEN, int Y_SCREEN, float FLOOR);
void draw_sa_heart(float camera_x, Sachiel *sa, entities_sprites *sprites);
void draw_sa_face(float camera_x, Sachiel *sa, entities_sprites *sprites, int X_SCREEN, int Y_SCREEN);
void draw_life_bar_sa(float camera_x, Sachiel *sa, entities_sprites *sprites, int X_SCREEN, int Y_SCREEN);
void draw_sa_bullets(float camera_x, Sachiel *sa, entities_sprites *sprites) ;
void draw_sa_death(float camera_x, Sachiel *sa, entities_sprites *sprites );

// backgrounds para as fases genéricas
void draw_default_background(float camera_x, ALLEGRO_BITMAP *background_image,int X_SCREEN,int Y_SCREEN, float FLOOR);

#endif