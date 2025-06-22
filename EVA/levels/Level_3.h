#ifndef __LEVEL_3__
#define __LEVEL_3__

#include "../gameflow/Title_screen.h"
#include "../gameflow/Assets.h"
#include "../entities/Player.h"
#include "../mechanics/Objects.h"
#include "../gameflow/Game_state.h"
#include "../entities/Jet_alone.h"
#include "../entities/Sachiel.h"

#define LEVEL_3_WIDTH X_SCREEN*2
#define MAX_PLATFORMS 20

typedef struct level_3 {
    float FLOOR; //altura do chão no começo
    Player *player; 
    float camera_x;   
    Platform *platforms[MAX_PLATFORMS]; // Um array para até 20 plataformas
    unsigned char boss_defeated; //a fase não tem boss então essa flag vira verdade quando chega no final
    int num_platforms;     // O número de plataformas que realmente existem
    int checkpoint;

    unsigned char exit_level_3;
} level_3;

void start_level_3(game_state *state, level_3 **level_3_info, entities_sprites *sprites, int X_SCREEN, int Y_SCREEN, int checkpoint);
void show_level_3(ALLEGRO_EVENT *event, game_state *state, ALLEGRO_FONT *font, ALLEGRO_DISPLAY *disp,entities_sprites *sprites, level_3 *level_3_info, int X_SCREEN, int Y_SCREEN);
void level_3_update(level_3 *level_3_info, game_state *state, int X_SCREEN, int Y_SCREEN);

///// auxiliares

void create_level_3_platforms(level_3 *level_3_info, int X_SCREEN, int Y_SCREEN);
void exit_level_3(game_state *state, level_3 *level_3_info, entities_sprites *sprites);


#endif