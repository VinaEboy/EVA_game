#ifndef __ASSETS__
#define __ASSETS__


/*#include "Title_screen.h"
#include "Options.h"
#include "Load_game.h"
#include "Level_select.h"
#include "Save_game.h"
#include "Pause.h"
#include "Level_1.h"*/

#include <allegro5/allegro.h>

typedef struct title_screen title_screen;
typedef struct options options;
typedef struct level_select level_select;
typedef struct pause_game pause_game;
typedef struct load_game load_game;
typedef struct level_1 level_1;

typedef struct game_assets {
    ALLEGRO_BITMAP *title_screen_image;
    title_screen *title_screen_info;
    options *options_info;
    ALLEGRO_BITMAP *level_select_image;
    level_select *level_select_info;
    pause_game *pause_info;
    load_game *load_game_info;
    level_1 *level_1_info;
    // outros ponteiros futuros
} game_assets;

game_assets *game_assets_create();
void game_assets_destroy(game_assets *assets);

#endif