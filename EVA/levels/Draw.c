#include "Draw.h"
#include <math.h> // para a função seno que oscila o brilho
#include <allegro5/allegro_primitives.h>

//Função para desenhar o jogador
void draw_player(float camera_x, Player *player, entities_sprites *sprites) {

    ALLEGRO_BITMAP *sprite_sheet = NULL;
    int frames_per_row = 0;
    player_sprite(player, &sprite_sheet, sprites, &frames_per_row);

    int frame_x = (player->current_frame % frames_per_row) * 256;
    int frame_y = (player->current_frame / frames_per_row) * 256;

    int flip_flag;
    if (player->direction == -1) flip_flag = ALLEGRO_FLIP_HORIZONTAL;
    else flip_flag = 0;


    //definir a priori nenhum tingimento
    ALLEGRO_COLOR tint_color = al_map_rgb(255, 255, 255);

    //se tiver carregando tiro, vai "piscar" e ter fundo colorido
    if (player->is_charging_shot)
        draw_charging_EVA(camera_x, player, &tint_color, sprites);


    al_draw_tinted_bitmap_region(
        sprite_sheet,
        tint_color,          // A cor de tingimento que calculamos
        frame_x, frame_y,
        EVA_WIDTH, EVA_HEIGHT,
        player->x - camera_x, 
        player->y,
        flip_flag
    );

    draw_life_bar_EVA(camera_x, player, sprites);

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

//por enquanto são retangulos e não estou usando os sprites
void draw_bullets(float camera_x, Player *player,entities_sprites *sprites) {
    bullet_1 *shot_1 = player->buster->shots_1;
    ALLEGRO_BITMAP *sprite_sheet_1 = sprites->bullet_1_image;

    while(shot_1 != NULL) {
        // Posição do frame na folha de sprites (source_x)
        float sx = shot_1->current_frame * 24;

        // Posição na tela (destination_x), ajustada para centralizar o sprite
        // Posição do tiro - deslocamento da câmera - metade da largura do sprite
        float dx = (shot_1->x - camera_x) - (BULLET_1_WEIGHT / 2.0f);
        float dy = shot_1->y - (BULLET_1_HEIGHT / 2.0f);

        int flags;
        if (shot_1->trajectory == -1) flags = ALLEGRO_FLIP_HORIZONTAL;
        else flags = 0;

        al_draw_scaled_bitmap(sprite_sheet_1,
                                sx, 0,           // Posição (sx, sy) e
                                24, 36, // tamanho do frame na imagem original
                                dx, dy,            // Posição (dx, dy) e
                                BULLET_1_WEIGHT, BULLET_1_HEIGHT, // tamanho (dw, dh) final na tela
                                flags);

        shot_1 = (bullet_1*)shot_1->next;
    }

    bullet_2 *shot_2 = player->buster->shots_2;
    ALLEGRO_BITMAP *sprite_sheet_2 = sprites->bullet_2_image;

    while(shot_2 != NULL) {
        // Posição do frame na folha de sprites (source_x)
        float sx = shot_2->current_frame * 30;

        // Posição na tela (destination_x), ajustada para centralizar o sprite
        // Posição do tiro - deslocamento da câmera - metade da largura do sprite
        float dx = (shot_2->x - camera_x) - (BULLET_2_WEIGHT / 2.0f);
        float dy = shot_2->y - (BULLET_2_HEIGHT / 2.0f);

        int flags;
        if (shot_2->trajectory == -1) flags = ALLEGRO_FLIP_HORIZONTAL;
        else flags = 0;

        al_draw_scaled_bitmap(sprite_sheet_2,
                                sx, 0,           // Posição (sx, sy) e
                                30, 36, // tamanho do frame na imagem original
                                dx, dy,            // Posição (dx, dy) e
                                BULLET_2_WEIGHT, BULLET_2_HEIGHT, // tamanho (dw, dh) final na tela
                                flags);

        shot_2 = (bullet_2*)shot_2->next;
    }

    bullet_3 *shot_3 = player->buster->shots_3;
    ALLEGRO_BITMAP *sprite_sheet_3 = sprites->bullet_3_image;  

    while(shot_3 != NULL) {
        // Posição do frame na folha de sprites (source_x)
        float sx = shot_3->current_frame * 64;

        // Posição na tela (destination_x), ajustada para centralizar o sprite
        // Posição do tiro - deslocamento da câmera - metade da largura do sprite
        float dx = (shot_3->x - camera_x) - (BULLET_3_WEIGHT / 2.0f);
        float dy = shot_3->y - (BULLET_3_HEIGHT / 2.0f);

        int flags;
        if (shot_3->trajectory == -1) flags = ALLEGRO_FLIP_HORIZONTAL;
        else flags = 0;

        al_draw_scaled_bitmap(sprite_sheet_3,
                                sx, 0,           // Posição (sx, sy) e
                                64, 36, // tamanho do frame na imagem original
                                dx, dy,            // Posição (dx, dy) e
                                BULLET_3_WEIGHT, BULLET_3_HEIGHT, // tamanho (dw, dh) final na tela
                                flags);

        shot_3 = (bullet_3*)shot_3->next;
    }
}

// AUXILIARES dentro do proprio draw


//Modifica o tingimento que vai piscar se estiver carregando  tiro
void draw_charging_EVA(float camera_x, Player *player, ALLEGRO_COLOR *tint_color, entities_sprites *sprites) {
    // Usa a função seno com o tempo de jogo para criar uma pulsação suave.
    float pulse = (sin(al_get_time() * CHARGE_BLINK_SPEED) + 1.0f) / 2.0f; // Valor entre 0.0 e 1.0

    //definir a priori
    int target_r = 255, target_g = 255, target_b = 255; 

    switch (player->charge_shot) {
        case 0: // Carga Nível 1 
            target_r = 255;
            target_g = 255;
            target_b = 50; // Pouco azul para um amarelo bem "aceso"
            break;
        case 1: // Carga Nível 2 
            target_r = 255;
            target_g = 160; // Menos verde para criar um tom de laranja forte
            target_b = 40;
            break;
        case 2: // Carga Nível 3 
            target_r = 50;
            target_g = 255; // Verde no máximo
            target_b = 50; // Pouco vermelho e azul para um verde puro e poderoso
            break;
    }

    // Mistura a cor normal (branco) com a cor alvo (verde) usando a pulsação.
    int final_r = 255 + (target_r - 255) * pulse;
    int final_g = 255 + (target_g - 255) * pulse;
    int final_b = 255 + (target_b - 255) * pulse;

    // Cria a cor final para o tingimento
    *tint_color = al_map_rgb(final_r, final_g, final_b);

    float sx = 0; // Posição X do frame na imagem
    if (player->charge_shot == 1) {
        sx = 0;   // Usa o frame da esquerda (0 a 255)
    } else { // charge_shot == 2
        sx = 256; // Usa o frame da direita (256 a 511)
    }

    float sw = 256; // Largura de um frame
    float sh = 256; // Altura de um frame
    float dx = (player->center_x - camera_x) - (sw / 2.0f) - 10;
    float dy = (player->center_y) - (sh / 2.0f);

    // Usa o blender aditivo para o efeito de brilho
    al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_ONE);

    if (player->charge_shot == 1 || player->charge_shot == 2)
        al_draw_tinted_bitmap_region(
            sprites->charging_shot,
            *tint_color,
            sx, 0, sw, sh,
            dx, dy,
            0
        );

    // Restaura o modo de desenho padrão
    al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_INVERSE_ALPHA);

}

void draw_life_bar_EVA(float camera_x, Player *player, entities_sprites *sprites) {
    ALLEGRO_BITMAP* life_bar_sprite = sprites->life_bar;

    float source_w = al_get_bitmap_width(life_bar_sprite);
    float source_h = al_get_bitmap_height(life_bar_sprite);

    player->life -= 1/30;

    al_draw_scaled_bitmap(
        life_bar_sprite,
        0, 0, source_w, source_h,              // sx, sy, sw, sh (usa a imagem inteira)
        LIFE_BAR_X, LIFE_BAR_Y,                // dx, dy (posição na tela)
        LIFE_BAR_WIDTH, LIFE_BAR_HEIGHT,       // dw, dh (o novo tamanho)
        0
    );

    // calculo procentagem vida
    float health_percentage = player->life / 100.0f;
    if (health_percentage < 0) health_percentage = 0;
    if (health_percentage > 1) health_percentage = 1;

    float current_health_height = HEALTH_FILL_MAX_HEIGHT * health_percentage;

    // desenha o retangulo de vida
    if (current_health_height > 1) {
        // A posição do preenchimento agora é baseada na posição da barra + o offset
        float fill_x = LIFE_BAR_X + HEALTH_FILL_OFFSET_X;
        float fill_y = LIFE_BAR_Y + HEALTH_FILL_OFFSET_Y + HEALTH_FILL_MAX_HEIGHT;

        ALLEGRO_COLOR health_color = al_map_rgb(60, 200, 90); // Verde
        if (health_percentage < 0.3f) {
            health_color = al_map_rgb(220, 50, 50); // Vermelho
        } else if (health_percentage < 0.6f) {
            health_color = al_map_rgb(230, 210, 70); // Amarelo
        }
        
        al_draw_filled_rectangle( 
            fill_x, 
            fill_y,  
            fill_x + HEALTH_FILL_MAX_WIDTH, 
            fill_y - current_health_height,
            health_color
        );
    }
}