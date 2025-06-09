// Level_1.c
#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#include <math.h>
#include "Level_1.h"
#include "Game_state.h"
#include "Assets.h"
#include "../entities/Player.h"


level_1 *level_1_info_create(int Y_SCREEN) {
    level_1 *level_1_info = malloc(sizeof(level_1));
    if (!level_1_info) return NULL;
    level_1_info->camera_x = 0;
    level_1_info->FLOOR = Y_SCREEN*0.07;
    level_1_info->player = create_player(Y_SCREEN, level_1_info->FLOOR + Y_SCREEN/2);

    level_1_info->num_platforms = 1;
    level_1_info->platforms[0].x = 0;
    level_1_info->platforms[0].y = Y_SCREEN - level_1_info->FLOOR;
    level_1_info->platforms[0].width = 8000; 
    level_1_info->platforms[0].height = level_1_info->FLOOR;

    return level_1_info;
} 


void start_level_1(game_state *state, level_1 **level_1_info, entities_sprites *sprites, int Y_SCREEN) {
    
    *level_1_info = level_1_info_create(Y_SCREEN);
    if (!*level_1_info) {
        fprintf(stderr, "Falha ao carregar informações level 1\n");
        exit(1);
    }

    sprites->level_1_background = al_load_bitmap("images/level_1_background.png");
    if (!sprites->level_1_background) {
        fprintf(stderr, "Falha ao carregar fundo level 1\n");
        exit(1);
    }
    sprites->level_1_ground = al_load_bitmap("images/ground.png");
    if (!sprites->level_1_ground) {
        fprintf(stderr, "Falha ao carregar chão level 1\n");
        exit(1);
    }

    sprites->player_run_no_gun = al_load_bitmap("images/EVA_sprites/EVA_run_no_gun.png");
    if (!sprites->player_run_no_gun) {
        fprintf(stderr, "Falha ao carregar sprite do jogador\n");
        exit(1);
    }

    state->level_1_started = 1;
}


void level_1_update(level_1 *level_1_info, int X_SCREEN) {
    Player *player = level_1_info->player;

    //verifica gravidade e colisão com plataformas
    player_update_position (player, level_1_info->num_platforms, level_1_info->platforms);

    update_player_sprite(player);

    update_camera(player, &level_1_info->camera_x, X_SCREEN);
}



void show_level_1(ALLEGRO_EVENT *event, game_state *state, ALLEGRO_FONT *font, ALLEGRO_DISPLAY *disp,entities_sprites *sprites, level_1 *level_1_info, int X_SCREEN, int Y_SCREEN) {

    // Desenha o cenário primeiro
    draw_level_1_background(level_1_info->camera_x, sprites, X_SCREEN, Y_SCREEN, level_1_info->FLOOR);

    // Desenha o jogador por cima do cenário
    draw_player(level_1_info->camera_x, level_1_info->player, sprites);

    al_flip_display();
}

//////////////////////////////////////////////////////////////////////////////////
///aux  
////////////////////////////////////////////////////////////////////////////////


//Função para desenhar o jogador
void draw_player(float camera_x, Player *player, entities_sprites *sprites) {
    ALLEGRO_BITMAP *sprite_sheet = NULL;
    int frames_per_row = 1;

    switch (player->current_anim_state) {
        // ... (seu switch case para decidir o sprite sheet) ...
        default:
            sprite_sheet = sprites->player_run_no_gun;
            frames_per_row = 3;
            break;
    }
    
    if (!sprite_sheet) return;

    int frame_x = (player->current_frame % frames_per_row) * FRAME_WIDTH;
    int frame_y = (player->current_frame / frames_per_row) * FRAME_HEIGHT;

    int flip_flag;
    if (player->direction == -1) flip_flag = ALLEGRO_FLIP_HORIZONTAL;
    else flip_flag = 0;

    // Desenha o jogador na posição correta da tela (MUNDO - CÂMERA)
    al_draw_bitmap_region(
        sprite_sheet,
        frame_x, frame_y,
        FRAME_WIDTH, FRAME_HEIGHT,
        player->x - camera_x, // <<< MUDANÇA CRÍTICA AQUI
        player->y,
        flip_flag
    );
}


void draw_level_1_background(float camera_x, entities_sprites *sprites, int X_SCREEN, int Y_SCREEN, float FLOOR) {
    ALLEGRO_BITMAP *background = sprites->level_1_background;
    ALLEGRO_BITMAP *ground = sprites->level_1_ground;

    int background_width = al_get_bitmap_width(background);
    int background_height = al_get_bitmap_height(background);

    int ground_height = al_get_bitmap_height(ground);  // altura real do bitmap do chão
    int background_screen_height = Y_SCREEN - FLOOR;

    // Clamp da câmera para não passar da imagem
    if (camera_x < 0) camera_x = 0;
    if (camera_x > background_width - X_SCREEN) camera_x = background_width - X_SCREEN;

    // --- Desenha o fundo, apenas na área acima do chão ---
    al_draw_scaled_bitmap(
        background,
        camera_x, 0,                      // sx, sy
        X_SCREEN, background_height,             // sw, sh (total da imagem de fundo)
        0, 0,                            // dx, dy (topo da tela)
        X_SCREEN, background_screen_height, // dw, dh (desenha até onde começa o chão)
        0
    );

    // --- Desenha o chão exatamente no rodapé da tela ---
    al_draw_scaled_bitmap(
        ground,
        camera_x, 0,                   // sx, sy
        X_SCREEN, ground_height,      // sw, sh
        0, background_screen_height,  // dx, dy (posição na tela)
        X_SCREEN, FLOOR, // dw, dh (ocupa os últimos 7% da tela)
        0
    );
}
