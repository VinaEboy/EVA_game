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
#include "../entities/Bullet.h"

level_1 *level_1_info_create(game_state *state, int X_SCREEN, int Y_SCREEN, int checkpoint) {
    level_1 *level_1_info = malloc(sizeof(level_1));
    if (!level_1_info) return NULL;
    level_1_info->camera_x = 0;
    level_1_info->FLOOR = Y_SCREEN*0.07;

    if (checkpoint == 0)
        level_1_info->player = create_player(state->player_progress->dificulty, 0, 0, Y_SCREEN);
    else if (checkpoint == 1)
        level_1_info->player = create_player(state->player_progress->dificulty, 2000, 0, Y_SCREEN);


    level_1_info->ja_num = 2; //por enquanto é 1 porque quero testar se está funcionando

    if (checkpoint == 0)
        for (int i =0; i < level_1_info->ja_num; i++) {
            level_1_info->did_jet_spawn[i] = 0;
            level_1_info->did_jet_died[i] = 0;
            level_1_info->jet_alones[i] = NULL; //os inimigos ainda não spawnaram
        }
    else if (checkpoint == 1) //significa que derrotou os inimigos da fase e está no chefão
        for (int i =0; i < level_1_info->ja_num; i++) {
            level_1_info->did_jet_spawn[i] = 1;
            level_1_info->did_jet_died[i] = 1;
            level_1_info->jet_alones[i] = NULL; //os inimigos ainda não spawnaram
        }

    level_1_info->num_platforms = 2;
    create_level_1_platforms(level_1_info, X_SCREEN, Y_SCREEN);

    level_1_info->exit_level_1 = 0;

    return level_1_info;
} 


void start_level_1(game_state *state, level_1 **level_1_info, entities_sprites *sprites, int X_SCREEN, int Y_SCREEN, int checkpoint) {
    
    *level_1_info = level_1_info_create(state, X_SCREEN, Y_SCREEN, checkpoint);

    sprites->level_1_background = al_load_bitmap("images/level_1_background.png");
    sprites->level_1_ground = al_load_bitmap("images/ground.png");
    sprites->level_1_background_final = al_load_bitmap("images/level_1_background_final.png");

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

    sprites->bullet_1_image = al_load_bitmap("images/bullets_sprites/bullet_1.png");
    sprites->bullet_2_image = al_load_bitmap("images/bullets_sprites/bullet_2.png");
    sprites->bullet_3_image = al_load_bitmap("images/bullets_sprites/bullet_3.png");

    sprites->jet_alone_shot = al_load_bitmap("images/jet_alone_sprites/jet_alone_shot.png");
    sprites->jet_alone_squat = al_load_bitmap("images/jet_alone_sprites/jet_alone_squat.png");
    sprites->jet_alone_stop = al_load_bitmap("images/jet_alone_sprites/jet_alone_stop.png");
    sprites->jet_alone_walk = al_load_bitmap("images/jet_alone_sprites/jet_alone_walk.png");

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
    player_update_position (player, level_1_info->num_platforms, level_1_info->platforms, LEVEL_1_WIDTH);

    update_player_sprite(player);

    update_player_bullets( level_1_info->camera_x,  level_1_info->player->buster, X_SCREEN, LEVEL_1_WIDTH);


    level_1_spawn_ja(level_1_info, player, X_SCREEN, Y_SCREEN);
    for (int i=0; i<level_1_info->ja_num; i++)
        if (level_1_info->did_jet_spawn[i] && level_1_info->did_jet_died[i] != 1) {
            update_ja(level_1_info->jet_alones[i], level_1_info->camera_x, player, X_SCREEN);
            update_ja_position (level_1_info->jet_alones[i], level_1_info->num_platforms, level_1_info->platforms, LEVEL_1_WIDTH);
            update_ja_bullets(level_1_info->camera_x, level_1_info->jet_alones[i]->ja_buster, X_SCREEN);
        }

    check_player_hit_by_ja_bullets(level_1_info->player, level_1_info->jet_alones, level_1_info->ja_num, level_1_info->did_jet_died, level_1_info->did_jet_spawn);
    check_player_collision_with_ja(level_1_info->player, level_1_info->jet_alones, level_1_info->ja_num, level_1_info->did_jet_died, level_1_info->did_jet_spawn);
    check_ja_hit_by_player_bullets(level_1_info->player, level_1_info->jet_alones, level_1_info->ja_num, level_1_info->did_jet_died, level_1_info->did_jet_spawn);
    player_update_state(player, Y_SCREEN); //verifica se o estado do jogador é de tomando dano ou morto

    update_camera(player, &level_1_info->camera_x, X_SCREEN, LEVEL_1_WIDTH);
    if (player->is_dead) level_1_info->exit_level_1 = 1; 

}



void show_level_1(ALLEGRO_EVENT *event, game_state *state, ALLEGRO_FONT *font, ALLEGRO_DISPLAY *disp,entities_sprites *sprites, level_1 *level_1_info, int X_SCREEN, int Y_SCREEN) {
    al_clear_to_color(al_map_rgb(0, 0, 0)); //o que não for desenhado vai ser um fundo preto (é para os voids da fase)

    // Desenha o cenário primeiro
    draw_level_1_background(level_1_info->camera_x, sprites, X_SCREEN, Y_SCREEN, level_1_info->FLOOR);

    for (int i=0; i<level_1_info->num_platforms; i++)
        draw_level_1_ground(level_1_info->camera_x, level_1_info->platforms[i], sprites, X_SCREEN, Y_SCREEN);

    // Desenha o jogador por cima do cenário
    draw_player(level_1_info->camera_x, level_1_info->player, sprites);
    draw_bullets(level_1_info->camera_x, level_1_info->player, sprites);
    
    for (int i=0; i<level_1_info->ja_num; i++)
        if (level_1_info->did_jet_spawn[i] && level_1_info->did_jet_died[i] != 1) {
            draw_ja(level_1_info->camera_x, level_1_info->jet_alones[i], sprites);
            draw_ja_bullets(level_1_info->camera_x, level_1_info->jet_alones[i],sprites);
        }

    al_flip_display();

    //descobrir se ele vai renascer ou não
    if (level_1_info->exit_level_1) {
        state->player_progress->Lifes -= 1;
        exit_level_1(state,level_1_info, sprites);

        if (state->player_progress->Lifes == 0) state->game_over = 1; //deu game over
        else state->level_1 = 1; //vai renascer no checkpoint
    }
}

///////////// AUXX


//função que faz spawnar os Jet Alone
void level_1_spawn_ja(level_1 *level_1_info, Player *player, int X_SCREEN, int Y_SCREEN) {

    int activate_pos[MAX_JA] = {0, 4000}; //inicialmente só tem uma posição de ativação que é 0
    int spawn_pos_x[MAX_JA] = {2000, 7000}; //posição x em que cada inimigo vai spawnar
    int spawn_pos_y[MAX_JA] = {Y_SCREEN - level_1_info->FLOOR - JA_HEIGHT, Y_SCREEN - level_1_info->FLOOR - JA_HEIGHT}; // posição y
    float squat_prob_pos[MAX_JA] = {0.1, 0.5}; //probabilidade de cada inimigo tem a agachar
    int spawn_direction[MAX_JA] = {-1, -1};
    float distance_to_player[MAX_JA] = {X_SCREEN/3, X_SCREEN/2};

    for (int i=0; i < level_1_info->ja_num; i++) {
        if (level_1_info->did_jet_spawn[i] == 0) {
            if (player->x >= activate_pos[i]) {
                level_1_info->jet_alones[i] = ja_create(player->buster->dificulty, squat_prob_pos[i], spawn_pos_x[i], spawn_pos_y[i], spawn_direction[i], distance_to_player[i]);
                level_1_info->did_jet_spawn[i] = 1;
            }
        }
    }
}

void create_level_1_platforms(level_1 *level_1_info, int X_SCREEN, int Y_SCREEN) {

    float pos_x[MAX_PLATFORMS] = {0, 1400, 1800};
    float pos_y[MAX_PLATFORMS] = {Y_SCREEN - level_1_info->FLOOR, Y_SCREEN - level_1_info->FLOOR, Y_SCREEN - level_1_info->FLOOR - 1000};
    float width[MAX_PLATFORMS] = {1000,30000, 1000};
    float height[MAX_PLATFORMS] = {level_1_info->FLOOR, level_1_info->FLOOR, 1000};

    for (int i=0; i < level_1_info->num_platforms; i++) 
        level_1_info->platforms[i] = create_platform(pos_x[i],pos_y[i],width[i],height[i]);

}

//confere em qual checkpoint está de acordo com o requisito ser ter matado todos os jet alone
//como são só 2 checkpoints possiveis a verificação está simples
void level_1_checkpoint_checker(game_state *state, level_1 *level_1_info) {
    state->checkpoint = 1;
    for (int i=0; i<level_1_info->ja_num; i++) {
        if (level_1_info->did_jet_died[i] == 0 || level_1_info->did_jet_spawn[i] == 0) {
            state->checkpoint = 0;
            break;
        }
    }
}

void exit_level_1(game_state *state, level_1 *level_1_info, entities_sprites *sprites) {
    if (!level_1_info || !sprites) {
        return;
    }

    al_destroy_bitmap(sprites->level_1_background);
    al_destroy_bitmap(sprites->level_1_ground);
    al_destroy_bitmap(sprites->level_1_background_final);
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
    al_destroy_bitmap(sprites->bullet_1_image);
    al_destroy_bitmap(sprites->bullet_2_image);
    al_destroy_bitmap(sprites->bullet_3_image);
    al_destroy_bitmap(sprites->jet_alone_shot);
    al_destroy_bitmap(sprites->jet_alone_squat);
    al_destroy_bitmap(sprites->jet_alone_stop);
    al_destroy_bitmap(sprites->jet_alone_walk);

    player_destroy(level_1_info->player);

    for (int i = 0; i < level_1_info->ja_num; i++) 
        if (level_1_info->jet_alones[i] != NULL) 
            ja_destroy(level_1_info->jet_alones[i]);

    for (int i=0; i<level_1_info->num_platforms; i++) 
        if (level_1_info->platforms[i] != NULL)
            platform_destroy(level_1_info->platforms[i]);
    
    free(level_1_info);
    state->level_1 = 0;
    state->level_1_started = 0;
}