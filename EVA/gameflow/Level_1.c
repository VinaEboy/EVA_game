#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro5.h>																																												
#include <allegro5/allegro_font.h>																																											
#include <allegro5/allegro_primitives.h>			

#include "Level_1.h"
#include "Game_state.h"
#include "Assets.h"

#define FLOOR 0.07

level_1 *level_1_info_create() {
    level_1 *level_1_info = malloc(sizeof(level_1));
    if (!level_1_info) return NULL;
    level_1_info->inicio = 1;
    return level_1_info;
}

void start_level_1(game_state *state, level_1 **level_1_info, entities_sprites *sprites) {
    *level_1_info = level_1_info_create();
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
}


void show_level_1(ALLEGRO_EVENT *event, game_state *state, ALLEGRO_FONT *font, ALLEGRO_DISPLAY *disp, entities_sprites *sprites,level_1 *level_1_info, int X_SCREEN, int Y_SCREEN) {

    draw_level_1_background(0, sprites, X_SCREEN, Y_SCREEN);

    al_flip_display();
}

///aux  


void draw_level_1_background(float camera_x, entities_sprites *sprites, int X_SCREEN, int Y_SCREEN) {
    ALLEGRO_BITMAP *background = sprites->level_1_background;
    ALLEGRO_BITMAP *ground = sprites->level_1_ground;

    int bg_width = al_get_bitmap_width(background);
    int bg_height = al_get_bitmap_height(background);

    int ground_height = al_get_bitmap_height(ground);  // altura real do bitmap do chão
    int ground_screen_height = FLOOR * Y_SCREEN;       // altura do chão na tela
    int background_screen_height = Y_SCREEN - ground_screen_height;

    // Clamp da câmera para não passar da imagem
    if (camera_x < 0) camera_x = 0;
    if (camera_x > bg_width - X_SCREEN) camera_x = bg_width - X_SCREEN;

    // --- Desenha o fundo, apenas na área acima do chão ---
    al_draw_scaled_bitmap(
        background,
        camera_x, 0,                      // sx, sy
        X_SCREEN, bg_height,             // sw, sh (total da imagem de fundo)
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
        X_SCREEN, ground_screen_height, // dw, dh (ocupa os últimos 7% da tela)
        0
    );
}

