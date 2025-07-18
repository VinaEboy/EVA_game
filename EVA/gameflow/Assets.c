#include "Assets.h"

//cria o game_assets como tudo NULL porque vai ser carregado (inicializado) ao iniciar uma etapa do jogo
game_assets *game_assets_create() {
    game_assets *assets = malloc(sizeof(game_assets));
    if (!assets) return NULL;

    assets->title_screen_image = NULL;
    assets->title_screen_info = NULL;
    assets->options_info = NULL;
    assets->level_select_image = NULL;
    assets->level_select_info = NULL;
    assets->pause_info = NULL;
    assets->pause_image = NULL;
    assets->load_game_info = NULL;
    assets->save_game_info = NULL;
    assets->default_slot_image = NULL;
    assets->save_game_image = NULL;
    assets->load_game_info = NULL;
    assets->load_game_image = NULL;
    assets->game_over_image = NULL;
    assets->game_over_info = NULL;
    assets->game_end_image = NULL;
    assets->game_end_info = NULL;

    assets->level_1_info = NULL;
    assets->level_2_info = NULL;
    assets->level_3_info = NULL;
    assets->level_4_info = NULL;
    assets->level_5_info = NULL;
    assets->level_6_info = NULL;
    assets->level_7_info = NULL; 
    assets->level_8_info = NULL;

    entities_sprites *sprites = malloc(sizeof(entities_sprites));
    if (!sprites) {
        free(assets);
        return NULL;
    }
    sprites->player_run_no_gun = NULL;
    sprites->player_run_gun = NULL;
    sprites->player_jump = NULL;
    sprites->player_stopped_gun = NULL;
    sprites->player_stopped_no_gun = NULL;
    sprites->player_damage = NULL;
    sprites->player_squat =  NULL;
    sprites->charging_shot = NULL;
    sprites->life_bar = NULL;
    sprites->player_jump_damage = NULL;
    sprites->player_death = NULL;
    sprites->player_run_gun_up = NULL;
    
    sprites->level_1_background = NULL;
    sprites->level_1_ground = NULL;
    sprites->level_1_background_final = NULL;

    sprites->bullet_1_image = NULL;
    sprites->bullet_2_image = NULL;
    sprites->bullet_3_image = NULL;

    sprites->jet_alone_shot = NULL;
    sprites->jet_alone_squat = NULL;
    sprites->jet_alone_stop = NULL;
    sprites->jet_alone_walk = NULL;

    sprites->sa_default_and_under = NULL;
    sprites->sa_shot = NULL;
    sprites->sa_minor_p1 = NULL;
    sprites->sa_minor_p2 = NULL;
    sprites->sa_minor_p3 = NULL;
    sprites->sa_bullet = NULL;
    sprites->sa_heart = NULL;
    sprites->sa_face = NULL;
    sprites->sa_hand = NULL;
    sprites->sa_life_bar = NULL;

    sprites->level_2_background = NULL;
    sprites->level_2_ground = NULL;
    sprites->level_3_background = NULL;
    sprites->level_3_ground = NULL;
    sprites->level_4_background = NULL;
    sprites->level_4_ground = NULL;
    sprites->level_5_background = NULL;
    sprites->level_5_ground = NULL;
    sprites->level_6_background = NULL;
    sprites->level_6_ground = NULL;
    sprites->level_7_background = NULL;
    sprites->level_7_ground = NULL;
    sprites->level_8_background = NULL;
    sprites->level_8_ground = NULL;
    
    assets->sprites = sprites;

    assets->current_music = NULL;

    return assets;
}

//libera memoria do game assets
void game_assets_destroy(game_assets *assets) {
    al_destroy_audio_stream(assets->current_music);
    free(assets->sprites);
    free(assets); 
}