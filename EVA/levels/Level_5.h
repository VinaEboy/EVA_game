#ifndef __LEVEL_5__
#define __LEVEL_5__

#include "../gameflow/Title_screen.h"
#include "../gameflow/Assets.h"
#include "../entities/Player.h"
#include "../mechanics/Objects.h"
#include "../gameflow/Game_state.h"
#include "../entities/Jet_alone.h"
#include "../entities/Sachiel.h"

#define LEVEL_5_WIDTH X_SCREEN*2
#define MAX_PLATFORMS 20

typedef struct level_5 {
    float FLOOR; //altura do chão no começo
    Player *player; 
    float camera_x;   
    Platform *platforms[MAX_PLATFORMS]; // Um array para até 20 plataformas
    unsigned char boss_defeated; //a fase não tem boss então essa flag vira verdade quando chega no final
    int num_platforms;     // O número de plataformas que realmente existem
    int checkpoint;

    unsigned char exit_level_5;
} level_5;

void start_level_5(game_state *state, level_5 **level_5_info, entities_sprites *sprites, int X_SCREEN, int Y_SCREEN, int checkpoint);
void show_level_5(ALLEGRO_EVENT *event, game_state *state, ALLEGRO_FONT *font, ALLEGRO_DISPLAY *disp,entities_sprites *sprites, level_5 *level_5_info, int X_SCREEN, int Y_SCREEN);
void level_5_update(level_5 *level_5_info, game_state *state, int X_SCREEN, int Y_SCREEN);

///// auxiliares

void create_level_5_platforms(level_5 *level_5_info, int X_SCREEN, int Y_SCREEN);
void exit_level_5(game_state *state, level_5 *level_5_info, entities_sprites *sprites);


#endif