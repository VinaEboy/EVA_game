#ifndef __ASSETS__
#define __ASSETS__


#include <allegro5/allegro.h>

typedef struct title_screen title_screen;
typedef struct options options;
typedef struct level_select level_select;
typedef struct pause_game pause_game;
typedef struct load_game load_game;
typedef struct save_game save_game;
typedef struct level_1 level_1;

typedef struct entities_sprites {
    ALLEGRO_BITMAP *EVA01_no_gun_run;
    ALLEGRO_BITMAP *EVA01_gun_run;
    ALLEGRO_BITMAP *level_1_background;
    ALLEGRO_BITMAP *level_1_ground;
} entities_sprites;

typedef struct game_assets {
    ALLEGRO_BITMAP *title_screen_image;
    title_screen *title_screen_info;
    options *options_info;
    ALLEGRO_BITMAP *level_select_image;
    level_select *level_select_info;
    pause_game *pause_info;
    save_game *save_game_info;
    ALLEGRO_BITMAP *default_slot_image;
    ALLEGRO_BITMAP *save_game_image;
    load_game *load_game_info;
    ALLEGRO_BITMAP *load_game_image;
    level_1 *level_1_info;
    entities_sprites *sprites;
    // outros ponteiros futuros
} game_assets;

game_assets *game_assets_create();
void game_assets_destroy(game_assets *assets);

#endif