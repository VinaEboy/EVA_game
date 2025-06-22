#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#include <math.h>
#include "Level_2.h"
#include "Draw.h"
#include "../gameflow/Game_state.h"
#include "../gameflow/Assets.h"
#include "../entities/Player.h"
#include "../entities/Buster.h"
#include "../entities/Bullet.h"


level_7 *level_7_info_create(game_state *state, int X_SCREEN, int Y_SCREEN, int checkpoint) {
    level_7 *level_7_info = malloc(sizeof(level_7));
    if (!level_7_info) return NULL;
    level_7_info->camera_x = 0;
    level_7_info->FLOOR = Y_SCREEN*0.07;

    level_7_info->checkpoint = state->checkpoint;
    if (level_7_info->checkpoint == 0)
        level_7_info->player = create_player(state->player_progress->dificulty, 0, 0, X_SCREEN, Y_SCREEN);
 

    level_7_info->num_platforms = 2;
    create_level_7_platforms(level_7_info, X_SCREEN, Y_SCREEN);

    level_7_info->exit_level_7 = 0;
    
    return level_7_info;
} 

void start_level_7(game_state *state, level_7 **level_7_info, entities_sprites *sprites, int X_SCREEN, int Y_SCREEN, int checkpoint) {
    
    *level_7_info = level_7_info_create(state, X_SCREEN, Y_SCREEN, checkpoint);

    sprites->level_7_background = al_load_bitmap("images/cenario/level_7_background.png");
    sprites->level_7_ground = al_load_bitmap("images/cenario/level_7_ground.png");

    sprites->player_run_no_gun = al_load_bitmap("images/EVA_sprites/EVA_run_no_gun.png");
    sprites->player_run_gun = al_load_bitmap("images/EVA_sprites/EVA_run_gun.png");
    sprites->player_jump =  al_load_bitmap("images/EVA_sprites/EVA_jump.png");
    sprites->player_stopped_gun =  al_load_bitmap("images/EVA_sprites/EVA_stopped_gun.png");
    sprites->player_stopped_no_gun =  al_load_bitmap("images/EVA_sprites/EVA_stopped_no_gun.png");
    sprites->player_damage =  al_load_bitmap("images/EVA_sprites/EVA_damage.png");
    sprites->player_squat =  al_load_bitmap("images/EVA_sprites/EVA_squat.png");
    sprites->charging_shot = al_load_bitmap("images/EVA_sprites/charging_shot.png");
    sprites->life_bar = al_load_bitmap("images/EVA_sprites/life_bar.png");
    sprites->player_jump_damage = al_load_bitmap("images/EVA_sprites/EVA_jump_damage.png");
    sprites->player_death = al_load_bitmap("images/EVA_sprites/EVA_death.png");
    sprites->player_run_gun_up = al_load_bitmap("images/EVA_sprites/EVA_run_gun_up.png");

    sprites->bullet_1_image = al_load_bitmap("images/bullets_sprites/bullet_1.png");
    sprites->bullet_2_image = al_load_bitmap("images/bullets_sprites/bullet_2.png");
    sprites->bullet_3_image = al_load_bitmap("images/bullets_sprites/bullet_3.png");



    if (// Cenário
        !sprites->level_7_background || !sprites->level_7_ground || 
        // Jogador
        !sprites->player_run_no_gun || !sprites->player_run_gun || !sprites->player_jump || 
        !sprites->player_stopped_gun || !sprites->player_stopped_no_gun || !sprites->player_damage || 
        !sprites->player_squat || !sprites->charging_shot || !sprites->life_bar || 
        !sprites->player_jump_damage || !sprites->player_death || !sprites->player_run_gun_up ||
        // Projéteis
        !sprites->bullet_1_image || !sprites->bullet_2_image || !sprites->bullet_3_image) 
    {
        fprintf(stderr, "Falha ao carregar um ou mais arquivos de imagem para a fase 2.\nVerifique se todos os arquivos estão nos caminhos corretos.\n");
        exit(1);
    }

    state->level_7_started = 1;
}

void level_7_update(level_7 *level_7_info, game_state *state, int X_SCREEN, int Y_SCREEN) {
    Player *player = level_7_info->player;

    //verifica gravidade e colisão com plataformas
    player_update_position (player, level_7_info->num_platforms, level_7_info->platforms, LEVEL_7_WIDTH);
    
    update_player_sprite(player);
    update_player_bullets(level_7_info->camera_x,  level_7_info->player->buster, X_SCREEN, LEVEL_7_WIDTH);

    player_update_state(player, Y_SCREEN); //verifica se o estado do jogador é de tomando dano ou morto
    update_camera(player, &level_7_info->camera_x, X_SCREEN, LEVEL_7_WIDTH);

    if (player->is_dead) level_7_info->exit_level_7 = 1; 
    if (player->x >= LEVEL_7_WIDTH - player->width) {
        level_7_info->boss_defeated = 1; //como a fase não tem boss de verdade, andar até o final dela é acabar a fase
        level_7_info->exit_level_7 = 1;
    }
}

void show_level_7(ALLEGRO_EVENT *event, game_state *state, ALLEGRO_FONT *font, ALLEGRO_DISPLAY *disp,entities_sprites *sprites, level_7 *level_7_info, int X_SCREEN, int Y_SCREEN) {
    al_clear_to_color(al_map_rgb(0, 0, 0)); //o que não for desenhado vai ser um fundo preto (é para os voids da fase)

    // Desenha o cenário de forma genérica
    draw_default_background(level_7_info->camera_x, sprites->level_7_background, X_SCREEN, Y_SCREEN, level_7_info->FLOOR);

    for (int i=0; i<level_7_info->num_platforms; i++)
        draw_platform(level_7_info->camera_x, level_7_info->platforms[i], sprites->level_7_ground, X_SCREEN, Y_SCREEN);

    // Desenha o jogador por cima do cenário
    draw_player(font,state, level_7_info->camera_x, level_7_info->player, sprites, X_SCREEN, Y_SCREEN);
    draw_bullets(level_7_info->camera_x, level_7_info->player, sprites);
    
    al_flip_display();

    //descobrir se ele vai renascer ou não
    if (level_7_info->exit_level_7) {
        if (level_7_info->player->is_dead) {
            state->player_progress->Lifes -= 1;
            exit_level_7(state,level_7_info, sprites);

            if (state->player_progress->Lifes == 0) state->game_over = 1; //deu game over
            else state->level_7 = 1; //vai renascer no checkpoint
        } 
        else if (level_7_info->boss_defeated) {
            state->checkpoint = 0;
            state->player_progress->Level_7_completed = 1;
            state->level_select = 1; //volta para a tela de seleção
            exit_level_7(state,level_7_info, sprites);
        }
    
    }
}

///////////////////////////////////// AUXILIARES /////////////////////////////////////

void create_level_7_platforms(level_7 *level_7_info, int X_SCREEN, int Y_SCREEN) {

    float default_ground_Y = Y_SCREEN - level_7_info->FLOOR;
    float default_ground_height = level_7_info->FLOOR;
    float pos_x[MAX_PLATFORMS] = {0, 1.3*X_SCREEN};
    float pos_y[MAX_PLATFORMS] = {default_ground_Y, default_ground_Y};
    float width[MAX_PLATFORMS] = {X_SCREEN, 0.7*X_SCREEN};
    float height[MAX_PLATFORMS] = {default_ground_height, default_ground_height};

    for (int i=0; i < level_7_info->num_platforms; i++) 
        level_7_info->platforms[i] = create_platform(pos_x[i],pos_y[i],width[i],height[i]);

}


void exit_level_7(game_state *state, level_7 *level_7_info, entities_sprites *sprites) {
    if (!level_7_info || !sprites) {
        return;
    }
 
    al_destroy_bitmap(sprites->level_7_background);
    al_destroy_bitmap(sprites->level_7_ground);

    al_destroy_bitmap(sprites->player_run_no_gun);
    al_destroy_bitmap(sprites->player_run_gun);
    al_destroy_bitmap(sprites->player_jump);
    al_destroy_bitmap(sprites->player_stopped_gun);
    al_destroy_bitmap(sprites->player_stopped_no_gun);
    al_destroy_bitmap(sprites->player_damage);
    al_destroy_bitmap(sprites->player_squat);
    al_destroy_bitmap(sprites->charging_shot);
    al_destroy_bitmap(sprites->life_bar);
    al_destroy_bitmap(sprites->player_jump_damage);
    al_destroy_bitmap(sprites->player_death);
    al_destroy_bitmap(sprites->player_run_gun_up);

    al_destroy_bitmap(sprites->bullet_1_image);
    al_destroy_bitmap(sprites->bullet_2_image);
    al_destroy_bitmap(sprites->bullet_3_image);
    

    player_destroy(level_7_info->player);

    for (int i = 0; i < level_7_info->num_platforms; i++) {
        if (level_7_info->platforms[i] != NULL) {
            platform_destroy(level_7_info->platforms[i]);
        }
    }
    
    free(level_7_info);

    state->level_7 = 0;
    state->level_7_started = 0;
}
