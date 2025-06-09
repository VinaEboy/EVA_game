#include "Assets.h"

game_assets *game_assets_create() {
    game_assets *assets = malloc(sizeof(game_assets));
    if (!assets) return NULL;

    assets->title_screen_image = NULL;
    assets->title_screen_info = NULL;
    assets->options_info = NULL;
    assets->level_select_image = NULL;
    assets->level_select_info = NULL;
    assets->pause_info = NULL;
    assets->load_game_info = NULL;
    assets->save_game_info = NULL;
    assets->default_slot_image = NULL;
    assets->save_game_image = NULL;
    assets->load_game_info = NULL;
    assets->load_game_image = NULL;

    entities_sprites *sprites = malloc(sizeof(entities_sprites));
    if (!sprites) {
        free(assets);
        return NULL;
    }
    sprites->player_run_no_gun = NULL;
    sprites->player_run_gun = NULL;
    sprites->level_1_background = NULL;
    sprites->level_1_ground = NULL;

    assets->sprites = sprites;

    return assets;
}

//ver depois certinho os free
void game_assets_destroy(game_assets *assets) {
    free(assets->sprites);
    free(assets); 
}