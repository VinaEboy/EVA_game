#ifndef __ASSETS__
#define __ASSETS__

#include <allegro5/allegro.h>

struct title_screen ;
struct options ;
struct level_select ;
struct pause_game ;
struct load_game ;
struct save_game;
struct game_over;
struct game_end;
struct level_1;
struct level_2;
struct level_3;
struct level_4;
struct level_5;
struct level_6;
struct level_7;
struct level_8;

typedef struct entities_sprites {
    ALLEGRO_BITMAP *player_run_no_gun;
    ALLEGRO_BITMAP *player_run_gun; 
    ALLEGRO_BITMAP *player_jump;
    ALLEGRO_BITMAP *player_stopped_gun;
    ALLEGRO_BITMAP *player_stopped_no_gun;
    ALLEGRO_BITMAP *player_damage; //frame para quando levar dano
    ALLEGRO_BITMAP *player_squat;
    ALLEGRO_BITMAP *charging_shot;
    ALLEGRO_BITMAP *life_bar;
    ALLEGRO_BITMAP *player_jump_damage;
    ALLEGRO_BITMAP *player_death;
    ALLEGRO_BITMAP *player_run_gun_up;

    ALLEGRO_BITMAP *level_1_background;
    ALLEGRO_BITMAP *level_1_background_final; 
    ALLEGRO_BITMAP *level_1_ground;

    ALLEGRO_BITMAP *bullet_1_image; //(0 a 8) frames
    ALLEGRO_BITMAP *bullet_2_image; //(0 a 5) frames
    ALLEGRO_BITMAP *bullet_3_image; //(0 a 4) frames

    ALLEGRO_BITMAP *jet_alone_shot; //(0 a 3) frames; É O tiro e apenas o tiro. 36x36 cada frame em uma linha
    ALLEGRO_BITMAP *jet_alone_squat; //(0 a 1) frames; 
    ALLEGRO_BITMAP *jet_alone_stop; //2 frames, o da esquerda tá normal e o da direita tá atirando
    ALLEGRO_BITMAP *jet_alone_walk; // 2 linhas com 2 frames, na linha de cima está atirando e na debaixo não

    ALLEGRO_BITMAP *sa_default_and_under;
    ALLEGRO_BITMAP *sa_shot;
    ALLEGRO_BITMAP *sa_minor_p1;
    ALLEGRO_BITMAP *sa_minor_p2 ;
    ALLEGRO_BITMAP *sa_minor_p3 ;
    ALLEGRO_BITMAP *sa_bullet;
    ALLEGRO_BITMAP *sa_heart;
    ALLEGRO_BITMAP *sa_face;
    ALLEGRO_BITMAP *sa_hand;
    ALLEGRO_BITMAP *sa_life_bar;

    //fases que não foram concluidas:
    ALLEGRO_BITMAP *level_2_background;
    ALLEGRO_BITMAP *level_2_ground;
    ALLEGRO_BITMAP *level_3_background;
    ALLEGRO_BITMAP *level_3_ground;
    ALLEGRO_BITMAP *level_4_background;
    ALLEGRO_BITMAP *level_4_ground;
    ALLEGRO_BITMAP *level_5_background;
    ALLEGRO_BITMAP *level_5_ground;
    ALLEGRO_BITMAP *level_6_background;
    ALLEGRO_BITMAP *level_6_ground;
    ALLEGRO_BITMAP *level_7_background;
    ALLEGRO_BITMAP *level_7_ground;
    ALLEGRO_BITMAP *level_8_background;
    ALLEGRO_BITMAP *level_8_ground;

} entities_sprites;

typedef struct game_assets {
    ALLEGRO_BITMAP *title_screen_image;
    struct title_screen *title_screen_info;
    struct options *options_info;
    ALLEGRO_BITMAP *level_select_image;
    struct level_select *level_select_info;
    struct pause_game *pause_info;
    ALLEGRO_BITMAP *pause_image;
    struct save_game *save_game_info;
    ALLEGRO_BITMAP *default_slot_image;
    ALLEGRO_BITMAP *save_game_image;
    struct load_game *load_game_info;
    ALLEGRO_BITMAP *load_game_image;
    ALLEGRO_BITMAP *game_over_image;
    struct game_over *game_over_info;
    ALLEGRO_BITMAP *game_end_image;
    struct game_end *game_end_info;

    struct level_1 *level_1_info;
    struct level_2 *level_2_info;
    struct level_3 *level_3_info;
    struct level_4 *level_4_info;
    struct level_5 *level_5_info;
    struct level_6 *level_6_info;
    struct level_7 *level_7_info;
    struct level_8 *level_8_info;

    entities_sprites *sprites; //sprites do level_1
} game_assets;

game_assets *game_assets_create();
void game_assets_destroy(game_assets *assets);

#endif