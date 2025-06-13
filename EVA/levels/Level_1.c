#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#include <math.h>
#include "Level_1.h"
#include "Draw.h"
#include "../gameflow/Game_state.h"
#include "../gameflow/Assets.h"
#include "../entities/Player.h"
#include "../entities/Buster.h"
#include "../entities/Charge_shot.h"

level_1 *level_1_info_create(game_state *state, int Y_SCREEN) {
    level_1 *level_1_info = malloc(sizeof(level_1));
    if (!level_1_info) return NULL;
    level_1_info->camera_x = 0;
    level_1_info->FLOOR = Y_SCREEN*0.07;
    level_1_info->player = create_player(state->player_progress->dificulty, Y_SCREEN, level_1_info->FLOOR + Y_SCREEN/2);

    level_1_info->num_platforms = 1;
    level_1_info->platforms[0].x = 0;
    level_1_info->platforms[0].y = Y_SCREEN - level_1_info->FLOOR;
    level_1_info->platforms[0].width = 8000; 
    level_1_info->platforms[0].height = level_1_info->FLOOR;

    level_1_info->ja_num = 1; //por enquanto é 1 porque quero testar se está funcionando

    for (int i =0; i < level_1_info->ja_num; i++)
        level_1_info->did_jet_spawn[i] = 0;

    return level_1_info;
} 


void start_level_1(game_state *state, level_1 **level_1_info, entities_sprites *sprites, int Y_SCREEN) {
    
    *level_1_info = level_1_info_create(state, Y_SCREEN);

    sprites->level_1_background = al_load_bitmap("images/level_1_background.png");
    sprites->level_1_ground = al_load_bitmap("images/ground.png");

    sprites->player_run_no_gun = al_load_bitmap("images/EVA_sprites/EVA_run_no_gun.png");
    sprites->player_run_gun = al_load_bitmap("images/EVA_sprites/EVA_run_gun.png");
    sprites->player_jump =  al_load_bitmap("images/EVA_sprites/EVA_jump.png");
    sprites->player_stopped_gun =  al_load_bitmap("images/EVA_sprites/EVA_stopped_gun.png");
    sprites->player_stopped_no_gun =  al_load_bitmap("images/EVA_sprites/EVA_stopped_no_gun.png");
    sprites->player_damage =  al_load_bitmap("images/EVA_sprites/EVA_damage.png");
    sprites->player_squat =  al_load_bitmap("images/EVA_sprites/EVA_squat.png");
    sprites->charging_shot = al_load_bitmap("images/EVA_sprites/charging_shot.png");
    sprites->life_bar = al_load_bitmap("images/EVA_sprites/life_bar.png");

    sprites->bullet_1_image = al_load_bitmap("images/entities_sprites/bullet_1.png");
    sprites->bullet_2_image = al_load_bitmap("images/entities_sprites/bullet_2.png");
    sprites->bullet_3_image = al_load_bitmap("images/entities_sprites/bullet_3.png");

    sprites->jet_alone_shot = al_load_bitmap("images/jet_alone/jet_alone_shot.png");
    sprites->jet_alone_squat = al_load_bitmap("images/jet_alone/jet_alone_squat.png");
    sprites->jet_alone_stop = al_load_bitmap("images/jet_alone/jet_alone_stop.png");
    sprites->jet_alone_walk = al_load_bitmap("images/jet_alone/jet_alone_walk.png");

    if (!sprites->player_run_no_gun || !sprites->player_jump || !sprites->player_stopped_gun||
        !sprites->player_damage || !sprites->player_squat || !sprites->player_stopped_no_gun) {
        fprintf(stderr, "Falha ao carregar sprite do jogador\n");
        exit(1);
    }

    state->level_1_started = 1;
}


void level_1_update(level_1 *level_1_info, int X_SCREEN, int Y_SCREEN) {
    Player *player = level_1_info->player;

    //verifica gravidade e colisão com plataformas
    player_update_position (player, level_1_info->num_platforms, level_1_info->platforms);

    update_player_sprite(player);

    update_bullets_1(level_1_info->camera_x, player->buster, X_SCREEN);
    update_bullets_2(level_1_info->camera_x, player->buster, X_SCREEN);
    update_bullets_3(level_1_info->camera_x, player->buster, X_SCREEN);

    level_1_spawn_ja(level_1_info, player, X_SCREEN, Y_SCREEN);
    for (int i=0; i<level_1_info->ja_num; i++)
        if (level_1_info->did_jet_spawn[i])
            update_ja(&level_1_info->jet_alones[i], level_1_info->camera_x, player, X_SCREEN);
    
    update_camera(player, &level_1_info->camera_x, X_SCREEN);

}



void show_level_1(ALLEGRO_EVENT *event, game_state *state, ALLEGRO_FONT *font, ALLEGRO_DISPLAY *disp,entities_sprites *sprites, level_1 *level_1_info, int X_SCREEN, int Y_SCREEN) {

    // Desenha o cenário primeiro
    draw_level_1_background(level_1_info->camera_x, sprites, X_SCREEN, Y_SCREEN, level_1_info->FLOOR);

    // Desenha o jogador por cima do cenário
    draw_player(level_1_info->camera_x, level_1_info->player, sprites);
    draw_bullets(level_1_info->camera_x, level_1_info->player, sprites);
    
    for (int i=0; i<level_1_info->ja_num; i++)
        if (level_1_info->did_jet_spawn[i] && level_1_info->jet_alones[i].dead != 1)
            draw_ja(level_1_info->camera_x, &level_1_info->jet_alones[i], sprites);

    al_flip_display();
}

//função que faz spawnar os Jet Alone
void level_1_spawn_ja(level_1 *level_1_info, Player *player, int X_SCREEN, int Y_SCREEN) {

    int activate_pos[MAX_JA] = {0}; //inicialmente só tem uma posição de ativação que é 0
    int spawn_pos_x[MAX_JA] = {500}; //posição x em que cada inimigo vai spawnar
    int spawn_pos_y[MAX_JA] = {Y_SCREEN - level_1_info->FLOOR - JA_HEIGHT}; // posição y
    float squat_prob_pos[MAX_JA] = {0.1}; //probabilidade de cada inimigo tem a agachar
    int spawn_direction[MAX_JA] = {-1};

    for (int i=0; i < level_1_info->ja_num; i++) {
        if (level_1_info->did_jet_spawn[i] == 0) {
            if (player->x >= activate_pos[i]) {
                level_1_info->jet_alones[i] = *ja_create(player->buster->dificulty, squat_prob_pos[i], spawn_pos_x[i], spawn_pos_y[i], spawn_direction[i]);
                level_1_info->did_jet_spawn[i] = 1;
            }
        }
    }
}



void exit_level_1(game_state *state, level_1 *level_1_info, entities_sprites *sprites) {
    state->level_1 = 0;
    state->level_1_started = 0;
    free(level_1_info);
}