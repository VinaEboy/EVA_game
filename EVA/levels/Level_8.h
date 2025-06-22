#ifndef __LEVEL_8__
#define __LEVEL_8__

#include "../gameflow/Title_screen.h"
#include "../gameflow/Assets.h"
#include "../entities/Player.h"
#include "../mechanics/Objects.h"
#include "../gameflow/Game_state.h"
#include "../entities/Jet_alone.h"
#include "../entities/Sachiel.h"

#define LEVEL_8_WIDTH X_SCREEN*2
#define MAX_PLATFORMS 20

typedef struct level_8 {
    float FLOOR; //altura do chão no começo
    Player *player; 
    float camera_x;   
    Platform *platforms[MAX_PLATFORMS]; // Um array para até 20 plataformas
    unsigned char boss_defeated; //a fase não tem boss então essa flag vira verdade quando chega no final
    int num_platforms;     // O número de plataformas que realmente existem
    int checkpoint;

    unsigned char exit_level_8;
} level_8;

void start_level_8(game_state *state, level_8 **level_8_info, entities_sprites *sprites, int X_SCREEN, int Y_SCREEN, int checkpoint);
void show_level_8(ALLEGRO_EVENT *event, game_state *state, ALLEGRO_FONT *font, ALLEGRO_DISPLAY *disp,entities_sprites *sprites, level_8 *level_8_info, int X_SCREEN, int Y_SCREEN);
void level_8_update(level_8 *level_8_info, game_state *state, int X_SCREEN, int Y_SCREEN);

///// auxiliares

void create_level_8_platforms(level_8 *level_8_info, int X_SCREEN, int Y_SCREEN);
void exit_level_8(game_state *state, level_8 *level_8_info, entities_sprites *sprites);


#endif