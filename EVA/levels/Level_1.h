// Level_1.h
#ifndef __LEVEL_1__
#define __LEVEL_1__

#include "../gameflow/Title_screen.h"
#include "../gameflow/Assets.h"
#include "../entities/Player.h"
#include "../mechanics/Objects.h"
#include "../gameflow/Game_state.h"
#include "../entities/Jet_alone.h"
#include "../entities/Sachiel.h"


#define MAX_PLATFORMS 20
#define MAX_JA 20
#define LEVEL_1_WIDTH X_SCREEN*7

typedef struct level_1 {
    float FLOOR; //altura do chão no começo
    Player *player; 
    float camera_x;   
    Platform *platforms[MAX_PLATFORMS]; // Um array para até 20 plataformas
    Jet_alone *jet_alones[MAX_JA];
    unsigned char did_jet_spawn[MAX_JA];
    unsigned char did_jet_died[MAX_JA];
    unsigned char block_screen; //trava a tela quando estiver na parte do chefão
    int checkpoint;

    Sachiel *Boss_sachiel;
    unsigned char boss_spawned;
    
    int ja_num;
    int num_platforms;     // O número de plataformas que realmente existem

    unsigned char exit_level_1;
} level_1;


void start_level_1(game_state *state, level_1 **level_1_info, entities_sprites *sprites, int X_SCREEN, int Y_SCREEN, int checkpoint);
void show_level_1(ALLEGRO_EVENT *event, game_state *state, ALLEGRO_FONT *font, ALLEGRO_DISPLAY *disp,entities_sprites *sprites, level_1 *level_1_info, int X_SCREEN, int Y_SCREEN);
void level_1_update(level_1 *level_1_info, game_state *state, int X_SCREEN, int Y_SCREEN);

// aux
void level_1_spawn_ja(level_1 *level_1_info, Player *player, int X_SCREEN, int Y_SCREEN);
void create_level_1_platforms(level_1 *level_1_info, int X_SCREEN, int Y_SCREEN);

void exit_level_1(game_state *state, level_1 *level_1_info, entities_sprites *sprites);
#endif