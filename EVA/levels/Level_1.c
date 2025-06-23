#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>

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

    level_1_info->checkpoint = state->checkpoint;
    if (level_1_info->checkpoint == 0)
        level_1_info->player = create_player(state->player_progress->dificulty, 0, 0, X_SCREEN, Y_SCREEN);
    else if (level_1_info->checkpoint == 1)
        level_1_info->player = create_player(state->player_progress->dificulty, X_SCREEN*6, 0, X_SCREEN, Y_SCREEN);


    level_1_info->ja_num = 7; 

    if (level_1_info->checkpoint == 0)
        for (int i =0; i < level_1_info->ja_num; i++) {
            level_1_info->did_jet_spawn[i] = 0;
            level_1_info->did_jet_died[i] = 0;
            level_1_info->jet_alones[i] = NULL; //os inimigos ainda não spawnaram
        }
    else if (level_1_info->checkpoint == 1) //significa que derrotou os inimigos da fase e está no chefão
        for (int i =0; i < level_1_info->ja_num; i++) {
            level_1_info->did_jet_spawn[i] = 1;
            level_1_info->did_jet_died[i] = 1;
            level_1_info->jet_alones[i] = NULL; //está como null pq não precisa dar free em nada
        }

    level_1_info->num_platforms = 4;
    create_level_1_platforms(level_1_info, X_SCREEN, Y_SCREEN);

    level_1_info->exit_level_1 = 0;

    Sachiel *Boss_sachiel = create_sa(state->player_progress->dificulty, X_SCREEN, Y_SCREEN);
    level_1_info->Boss_sachiel = Boss_sachiel;
    level_1_info->boss_spawned = 0;
    level_1_info->block_screen = 0;
    
    return level_1_info;
} 


void start_level_1(game_state *state, level_1 **level_1_info, entities_sprites *sprites, int X_SCREEN, int Y_SCREEN, int checkpoint, ALLEGRO_AUDIO_STREAM **current_music) {
    if (*current_music) {
        al_set_audio_stream_playing(*current_music, false);
        al_destroy_audio_stream(*current_music);
    }
    *current_music = al_load_audio_stream("sounds/level_1.ogg", 4, 2048); // (arquivo, buffer count, buffer size)
    al_attach_audio_stream_to_mixer(*current_music, al_get_default_mixer());
    al_set_audio_stream_playmode(*current_music, ALLEGRO_PLAYMODE_LOOP);
    al_set_audio_stream_gain(*current_music, state->sound_volume); // configura o volume do jogo

    *level_1_info = level_1_info_create(state, X_SCREEN, Y_SCREEN, checkpoint);

    sprites->level_1_background = al_load_bitmap("images/cenario/level_1_background.png");
    sprites->level_1_ground = al_load_bitmap("images/cenario/level_1_ground.png");
    sprites->level_1_background_final = al_load_bitmap("images/cenario/level_1_background_final.png");

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
    sprites->jet_alone_shot = al_load_bitmap("images/bullets_sprites/ja_bullet.png");
    sprites->sa_bullet = al_load_bitmap("images/bullets_sprites/sa_bullet.png");

    sprites->jet_alone_squat = al_load_bitmap("images/jet_alone_sprites/jet_alone_squat.png");
    sprites->jet_alone_stop = al_load_bitmap("images/jet_alone_sprites/jet_alone_stop.png");
    sprites->jet_alone_walk = al_load_bitmap("images/jet_alone_sprites/jet_alone_walk.png");

    sprites->sa_shot = al_load_bitmap("images/sachiel/sachiel_shot.png");
    sprites->sa_default_and_under = al_load_bitmap("images/sachiel/sachiel_default_and_under.png");
    sprites->sa_minor_p1 = al_load_bitmap("images/sachiel/sachiel_minor_p1.png");
    sprites->sa_minor_p2 = al_load_bitmap("images/sachiel/sachiel_minor_p2.png");
    sprites->sa_minor_p3 = al_load_bitmap("images/sachiel/sachiel_minor_p3.png");
    sprites->sa_heart = al_load_bitmap("images/sachiel/heart.png");
    sprites->sa_face = al_load_bitmap("images/sachiel/face.png");
    sprites->sa_hand = al_load_bitmap("images/sachiel/hand.png");
    sprites->sa_life_bar = al_load_bitmap("images/sachiel/sachiel_life_bar.png");
    
    if (// Cenário
        !sprites->level_1_background || !sprites->level_1_ground || !sprites->level_1_background_final ||
        // Jogador
        !sprites->player_run_no_gun || !sprites->player_run_gun || !sprites->player_jump || 
        !sprites->player_stopped_gun || !sprites->player_stopped_no_gun || !sprites->player_damage || 
        !sprites->player_squat || !sprites->charging_shot || !sprites->life_bar || 
        !sprites->player_jump_damage || !sprites->player_death || !sprites->player_run_gun_up ||
        // Projéteis
        !sprites->bullet_1_image || !sprites->bullet_2_image || !sprites->bullet_3_image || 
        !sprites->jet_alone_shot ||
        // Inimigo Jet Alone
        !sprites->jet_alone_squat || !sprites->jet_alone_stop || !sprites->jet_alone_walk ||
        // Chefe Sachiel
        !sprites->sa_shot || !sprites->sa_default_and_under || !sprites->sa_minor_p1 || 
        !sprites->sa_minor_p2 || !sprites->sa_minor_p3 || !sprites->sa_bullet || 
        !sprites->sa_heart || !sprites->sa_face || !sprites->sa_hand || !sprites->sa_life_bar) 
    {
        fprintf(stderr, "Falha ao carregar um ou mais arquivos de imagem para a fase 1.\nVerifique se todos os arquivos estão nos caminhos corretos.\n");
        exit(1);
    }

    state->level_1_started = 1;
}


void level_1_update(level_1 *level_1_info, game_state *state, int X_SCREEN, int Y_SCREEN) {
    Player *player = level_1_info->player;

    //verifica gravidade e colisão com plataformas
    player_update_position (player, level_1_info->num_platforms, level_1_info->platforms, LEVEL_1_WIDTH);
    if (level_1_info->boss_spawned) 
        if (player->x < X_SCREEN*6) player->x = X_SCREEN*6;
    
    update_player_sprite(player);
    update_player_bullets(level_1_info->camera_x,  level_1_info->player->buster, X_SCREEN, LEVEL_1_WIDTH);


    level_1_spawn_ja(level_1_info, player, X_SCREEN, Y_SCREEN);
    for (int i=0; i<level_1_info->ja_num; i++)
        if (level_1_info->did_jet_spawn[i] && level_1_info->did_jet_died[i] != 1) {
            update_ja(level_1_info->jet_alones[i], level_1_info->camera_x, player, X_SCREEN, Y_SCREEN);
            update_ja_position (level_1_info->jet_alones[i], level_1_info->num_platforms, level_1_info->platforms, LEVEL_1_WIDTH);
            update_ja_bullets(level_1_info->camera_x, level_1_info->jet_alones[i]->ja_buster, X_SCREEN);
        }

    if (player->x >= X_SCREEN*6) level_1_info->boss_spawned = 1;
    if (level_1_info->boss_spawned && !level_1_info->Boss_sachiel->is_dead) {
        update_sa(level_1_info->Boss_sachiel, player, X_SCREEN, Y_SCREEN );
        update_heart_position(level_1_info->Boss_sachiel, LEVEL_1_WIDTH, X_SCREEN, Y_SCREEN);
        update_sa_bullets(level_1_info->camera_x, level_1_info->Boss_sachiel->sa_buster, X_SCREEN, LEVEL_1_WIDTH);
    }

    
    //ja_collisions
    check_player_hit_by_ja_bullets(level_1_info->player, level_1_info->jet_alones, level_1_info->ja_num, level_1_info->did_jet_died, level_1_info->did_jet_spawn);
    check_player_collision_with_ja(level_1_info->player, level_1_info->jet_alones, level_1_info->ja_num, level_1_info->did_jet_died, level_1_info->did_jet_spawn);
    check_ja_hit_by_player_bullets(level_1_info->player, level_1_info->jet_alones, level_1_info->ja_num, level_1_info->did_jet_died, level_1_info->did_jet_spawn);
    //sachiel_collisions
    if (level_1_info->boss_spawned && !level_1_info->Boss_sachiel->is_dead) {
        check_player_hit_by_sa_bullets(level_1_info->player, level_1_info->Boss_sachiel);
        check_sachiel_hit_by_player_bullets(level_1_info->player, level_1_info->Boss_sachiel);
        check_player_collision_with_sachiel(level_1_info->player, level_1_info->Boss_sachiel);
    }

    
    player_update_state(player, Y_SCREEN); //verifica se o estado do jogador é de tomando dano ou morto

    //trava a camera se estiver no chefão
    unsigned char player_defeated_all_ja = 1;
    if (level_1_info->checkpoint == 0)
        for (int i=0; i < level_1_info->ja_num; i++) 
            if (!level_1_info->did_jet_died[i]) player_defeated_all_ja = 0;

    if (!player_defeated_all_ja && player->x + player->width > 6*X_SCREEN) player->x = 6*X_SCREEN - player->width;

    if (player->x >= 6*X_SCREEN) state->checkpoint = 1;
    if (player->x >= X_SCREEN*6.4) level_1_info->block_screen = 1;
    
    if (level_1_info->block_screen) 
        level_1_info->camera_x = X_SCREEN * 6;
    else 
        update_camera(player, &level_1_info->camera_x, X_SCREEN, LEVEL_1_WIDTH);

    if (player->is_dead || (level_1_info->boss_spawned && level_1_info->Boss_sachiel->is_dead)) level_1_info->exit_level_1 = 1; 

}



void show_level_1(ALLEGRO_EVENT *event, game_state *state, ALLEGRO_FONT *font, ALLEGRO_DISPLAY *disp,entities_sprites *sprites, level_1 *level_1_info, int X_SCREEN, int Y_SCREEN) {
    al_clear_to_color(al_map_rgb(0, 0, 0)); //o que não for desenhado vai ser um fundo preto (é para os voids da fase)

    // Desenha o cenário primeiro
    draw_level_1_background(level_1_info->camera_x, sprites, X_SCREEN, Y_SCREEN, level_1_info->FLOOR);

    for (int i=0; i<level_1_info->num_platforms; i++)
        draw_platform(level_1_info->camera_x, level_1_info->platforms[i], sprites->level_1_ground, X_SCREEN, Y_SCREEN);

    if (level_1_info->boss_spawned) {
        draw_sa(level_1_info->camera_x, level_1_info->Boss_sachiel, sprites, X_SCREEN,Y_SCREEN, level_1_info->FLOOR);
        if (!level_1_info->Boss_sachiel->is_dead)
            draw_sa_bullets(level_1_info->camera_x, level_1_info->Boss_sachiel, sprites);
    }

    // Desenha o jogador por cima do cenário
    draw_player(font,state, level_1_info->camera_x, level_1_info->player, sprites, X_SCREEN, Y_SCREEN);
    draw_bullets(level_1_info->camera_x, level_1_info->player, sprites);
    
    for (int i=0; i<level_1_info->ja_num; i++)
        if (level_1_info->did_jet_spawn[i] && level_1_info->did_jet_died[i] != 1) {
            draw_ja(level_1_info->camera_x, level_1_info->jet_alones[i], sprites);
            draw_ja_bullets(level_1_info->camera_x, level_1_info->jet_alones[i],sprites);
        }


    al_flip_display();

    //descobrir se ele vai renascer ou não
    if (level_1_info->exit_level_1) {
        if (level_1_info->player->is_dead) {
            state->player_progress->Lifes -= 1;
            exit_level_1(state,level_1_info, sprites);

            if (state->player_progress->Lifes == 0) state->game_over = 1; //deu game over
            else state->level_1 = 1; //vai renascer no checkpoint
        } 
        else if (level_1_info->boss_spawned && level_1_info->Boss_sachiel->is_dead) {
            state->checkpoint = 0;
            state->player_progress->Level_1_completed = 1;
            state->game_end = 1; //é o final do jogo porque só tem 1 fase
            exit_level_1(state,level_1_info, sprites);
        }
    
    }
}

///////////// AUXX


//função que faz spawnar os Jet Alone
void level_1_spawn_ja(level_1 *level_1_info, Player *player, int X_SCREEN, int Y_SCREEN) {

    float default_ground_Y = Y_SCREEN - level_1_info->FLOOR - Y_SCREEN*0.55; //o ultimo desconto é o tamanho do JA


    //posições x em que o jogador tem que ultrapassar para spawnar os JA
    int activate_pos[MAX_JA] = {0.8*X_SCREEN, 1.3*X_SCREEN, 1.4*X_SCREEN, 2.7*X_SCREEN , 3.2*X_SCREEN, 3.6*X_SCREEN, 4.7*X_SCREEN}; 
    int spawn_pos_x[MAX_JA] = {1.4*X_SCREEN, 2.4*X_SCREEN, 2.6*X_SCREEN, 3.3*X_SCREEN, 4*X_SCREEN, 4.3*X_SCREEN, 5.5*X_SCREEN}; //posição x em que cada inimigo vai spawnar
    int spawn_pos_y[MAX_JA] = {default_ground_Y,default_ground_Y,default_ground_Y, default_ground_Y - Y_SCREEN*0.2, default_ground_Y - Y_SCREEN*0.2, default_ground_Y - Y_SCREEN*0.2, default_ground_Y}; // posição y
    float squat_prob_pos[MAX_JA] = {0.2, 0.5, 0.2, 1, 0.3, 0.1, 0.5}; //probabilidade de cada inimigo tem a agachar
    int spawn_direction[MAX_JA] = {-1, -1, -1, -1, -1, -1, -1};
    float distance_to_player[MAX_JA] = {X_SCREEN*0.35, X_SCREEN*0.35, X_SCREEN*0.5, X_SCREEN*0.2, X_SCREEN*0.35, X_SCREEN*0.2, X_SCREEN*0.2};

    for (int i=0; i < level_1_info->ja_num; i++) {
        if (level_1_info->did_jet_spawn[i] == 0) {
            if (player->x >= activate_pos[i]) {
                level_1_info->jet_alones[i] = ja_create(player->buster->dificulty, squat_prob_pos[i], spawn_pos_x[i], spawn_pos_y[i], spawn_direction[i], distance_to_player[i], X_SCREEN, Y_SCREEN);
                if (level_1_info->jet_alones[i] != NULL) level_1_info->did_jet_spawn[i] = 1;
            }
        }
    }

}

void create_level_1_platforms(level_1 *level_1_info, int X_SCREEN, int Y_SCREEN) {

    float default_ground_Y = Y_SCREEN - level_1_info->FLOOR;
    float default_ground_height = level_1_info->FLOOR;
    float pos_x[MAX_PLATFORMS] = {0, 1.3*X_SCREEN, 3.1*X_SCREEN, 4.7*X_SCREEN};
    float pos_y[MAX_PLATFORMS] = {default_ground_Y, default_ground_Y, default_ground_Y - Y_SCREEN*0.2, default_ground_Y};
    float width[MAX_PLATFORMS] = {X_SCREEN, 1.5*X_SCREEN, 1.3*X_SCREEN, 2.3*X_SCREEN};
    float height[MAX_PLATFORMS] = {default_ground_height, default_ground_height, default_ground_height + Y_SCREEN*0.2, default_ground_height};

    for (int i=0; i < level_1_info->num_platforms; i++) 
        level_1_info->platforms[i] = create_platform(pos_x[i],pos_y[i],width[i],height[i]);

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

    al_destroy_bitmap(sprites->sa_shot); 
    al_destroy_bitmap(sprites->sa_default_and_under); 
    al_destroy_bitmap(sprites->sa_minor_p1); 
    al_destroy_bitmap(sprites->sa_minor_p2); 
    al_destroy_bitmap(sprites->sa_minor_p3); 
    al_destroy_bitmap(sprites->sa_heart); 
    al_destroy_bitmap(sprites->sa_face); 
    al_destroy_bitmap(sprites->sa_hand);
    al_destroy_bitmap(sprites->sa_life_bar);

    player_destroy(level_1_info->player);

    for (int i = 0; i < level_1_info->ja_num; i++) 
        if (level_1_info->jet_alones[i] != NULL) 
            ja_destroy(level_1_info->jet_alones[i]);

    for (int i=0; i<level_1_info->num_platforms; i++) 
        if (level_1_info->platforms[i] != NULL)
            platform_destroy(level_1_info->platforms[i]);
    
    if (level_1_info->Boss_sachiel)
        sa_destroy(level_1_info->Boss_sachiel); 

    free(level_1_info);
    state->level_1 = 0;
    state->level_1_started = 0;
}