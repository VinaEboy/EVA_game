#include "Draw.h"
#include <math.h> // para a função seno que oscila o brilho
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro.h>
#include <stdio.h>

// BACKGROUND

void draw_level_1_background(float camera_x, entities_sprites *sprites, int X_SCREEN, int Y_SCREEN, float FLOOR) {

    ALLEGRO_BITMAP *bg_tile_A = sprites->level_1_background;
    ALLEGRO_BITMAP *bg_tile_B = sprites->level_1_background_final;

    if (!bg_tile_A || !bg_tile_B) return;
    
    float current_world_x = 0;
    long tile_width = X_SCREEN;
    const int num_tiles = 7;

    for (int i = 0; i < num_tiles; i++) {
        ALLEGRO_BITMAP *current_tile_image = NULL;
        int flip_flag = 0; // definir a priori

        switch (i) {
            case 0: 
                current_tile_image = bg_tile_A;
                flip_flag = 0;
                break;
            case 1: 
                current_tile_image = bg_tile_A;
                flip_flag = ALLEGRO_FLIP_HORIZONTAL;
                break;
            case 2: 
                current_tile_image = bg_tile_A;
                flip_flag = 0;
                break;
            case 3: 
                current_tile_image = bg_tile_A;
                flip_flag = ALLEGRO_FLIP_HORIZONTAL;
                break;
            case 4: 
                current_tile_image = bg_tile_A;
                flip_flag = 0;
                break;
            case 5: 
                current_tile_image = bg_tile_A;
                flip_flag = ALLEGRO_FLIP_HORIZONTAL;
                break;
            case 6:
                current_tile_image = bg_tile_B;
                flip_flag = 0;
                break;
        }


        // Verifica se o tile atual está dentro da área visível da câmera (Culling)
        if ((current_world_x + tile_width) >= camera_x && current_world_x <= (camera_x + X_SCREEN)) {
            
            float draw_x = current_world_x - camera_x;

            al_draw_scaled_bitmap(
                current_tile_image,
                0, 0,                                // (sx, sy) Pega a imagem de origem inteira
                al_get_bitmap_width(current_tile_image), // (sw) Largura da imagem de origem
                al_get_bitmap_height(current_tile_image), // (sh) Altura da imagem de origem
                draw_x, 0,                           // (dx, dy) Posição na tela
                tile_width, Y_SCREEN - FLOOR, // (dw, dh) Tamanho final, escalando a altura
                flip_flag
            );
        }

        // Avança a posição X para o próximo tile
        current_world_x += tile_width;
    }

}

//reescrever comentários
void draw_level_1_ground(float camera_x, Platform *current_platform, entities_sprites *sprites, int X_SCREEN, int Y_SCREEN) {
    
    // Pega a imagem que será usada como ladrilho para o chão
    ALLEGRO_BITMAP *ground_tile = sprites->level_1_ground; 
    
    // Pega as dimensões do ladrilho para os cálculos
    const float tile_original_width = al_get_bitmap_width(ground_tile);
    const float tile_original_height = al_get_bitmap_height(ground_tile);


    // Otimização: Se a plataforma estiver totalmente fora da tela, nem tenta desenhar.
    if ((current_platform->x + current_platform->width) < camera_x || current_platform->x > (camera_x + X_SCREEN)) {
        return; 
    }

    float drawn_width = 0; // Controla o quanto da plataforma já foi desenhado

    // Continua desenhando ladrilhos até que toda a largura da plataforma seja preenchida
    while (drawn_width < current_platform->width) {
            
        float tile_dest_x = current_platform->x + drawn_width; // Posição X para desenhar o ladrilho atual
        float remaining_width = current_platform->width - drawn_width; // O que falta desenhar da plataforma
            
        float source_width_to_draw = tile_original_width; // Por padrão, desenha o ladrilho inteiro

        // Se o que falta for menor que um ladrilho completo, ajusta para desenhar só um pedaço
        if (remaining_width < tile_original_width) {
            source_width_to_draw = remaining_width;
        }

        al_draw_scaled_bitmap(
            ground_tile,
            // --- Fonte (Source) ---
            0, 0,                             // (sx, sy) Pega o ladrilho desde o seu canto superior esquerdo.
            source_width_to_draw,             // (sw) Largura do recorte na imagem original (ladrilho inteiro ou parcial).
            tile_original_height,             // (sh) Altura do recorte na imagem original.
                
            // --- Destino (Destination) ---
            tile_dest_x - camera_x,           // (dx) Posição X na tela (ajustada pela câmera).
            current_platform->y,               // (dy) Posição Y na tela.
            source_width_to_draw,             // (dw) A largura final do ladrilho na tela (sem esticar horizontalmente).
            current_platform->height,          // (dh) A altura final, redimensionada para a altura da plataforma.
            0
        );
            
        // Atualiza o total já desenhado
        drawn_width += source_width_to_draw;
    }
    
}

// PLAYER ////////////////////////////


//Função para desenhar o jogador
void draw_player(float camera_x, Player *player, entities_sprites *sprites) {

    if (player->life <= 0) {
        draw_player_death(camera_x, player, sprites);
        draw_life_bar_EVA(camera_x, player, sprites);
        return;
    }

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

    if (!player->is_invincible || (player->invincible_timer / 4) % 2 != 0) {
        al_draw_tinted_bitmap_region(
        sprite_sheet,
        tint_color,          // A cor de tingimento que calculamos
        frame_x, frame_y,
        EVA_WIDTH, EVA_HEIGHT,
        player->x - camera_x, 
        player->y,
        flip_flag
        );
    
    }



    draw_life_bar_EVA(camera_x, player, sprites);

}


void draw_bullets(float camera_x, Player *player,entities_sprites *sprites) {
    bullet *shot = player->buster->shots;

    ALLEGRO_BITMAP *sprite_sheet = NULL;

    while(shot != NULL) {
        bullet_sprite(shot, &sprite_sheet, sprites);

        if (sprite_sheet == NULL) {
            printf("AAA\n");
            shot = (bullet*)shot->next;
            continue; 
        }

        float original_width = al_get_bitmap_width(sprite_sheet);
        float original_height = al_get_bitmap_height(sprite_sheet);

        // Posição do frame na folha de sprites (source_x)
        float sx = shot->current_frame * (original_width/shot->frames);

        // Posição na tela (destination_x), ajustada para centralizar o sprite
        // Posição do tiro - deslocamento da câmera - metade da largura do sprite
        float dx = (shot->x - camera_x) - (shot->width / 2.0f);
        float dy = shot->y - (shot->height / 2.0f);

        int flags;
        if (shot->trajectory == -1) flags = ALLEGRO_FLIP_HORIZONTAL;
        else flags = 0;

        al_draw_scaled_bitmap(sprite_sheet,
                                sx, 0,           // Posição (sx, sy) e
                                original_width/shot->frames, original_height, // tamanho do frame na imagem original
                                dx, dy,            // Posição (dx, dy) e
                                shot->width , shot->height, // tamanho (dw, dh) final na tela
                                flags);

        shot = (bullet*)shot->next;
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
        case 1: // Carga Nível 1 
            target_r = 255;
            target_g = 255;
            target_b = 50; // Pouco azul para um amarelo bem "aceso"
            break;
        case 2: // Carga Nível 2 
            target_r = 255;
            target_g = 160; // Menos verde para criar um tom de laranja forte
            target_b = 40;
            break;
        case 3: // Carga Nível 3 
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
    if (player->charge_shot == 2) {
        sx = 0;   // Usa o frame da esquerda (0 a 255)
    } else { // charge_shot == 3
        sx = 256; // Usa o frame da direita (256 a 511)
    }

    float sw = 256; // Largura de um frame
    float sh = 256; // Altura de um frame
    float dx = (player->center_x - camera_x) - (sw / 2.0f) - 10;
    float dy = (player->center_y) - (sh / 2.0f);

    // Usa o blender aditivo para o efeito de brilho
    al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_ONE);

    if (player->charge_shot == 2 || player->charge_shot == 3)
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

void draw_player_death(float camera_x, Player *player, entities_sprites *sprites) {
    if (!sprites->player_death) {
        return;
    }


    float pa = 5 + 0.2*player->current_frame; //eu quero que as bolinhas se expandam por isso aumento o tamanho destino em uma PA

    float sx = player->current_frame * 42;
    float sy = 0; // O sprite está todo na primeira linha
    float sw = 42;
    float sh = 50;

    // Parâmetros de Destino (Destination)
    float dx = player->x - camera_x;
    float dy = player->y;

    // Centro de Rotação/Escala (cx, cy)
    // Este é o ponto DENTRO DO SPRITE (na região de origem) que servirá como âncora.
    // Para o comportamento padrão (desenhar a partir do canto superior esquerdo), use 0, 0.
    float cx = 0;
    float cy = 0;


    ALLEGRO_COLOR tint = al_map_rgb(255, 255, 255);


    al_draw_tinted_scaled_rotated_bitmap_region(
        sprites->player_death,  // O bitmap completo
        sx, sy, sw, sh,         // A região do frame atual para copiar
        tint,                   // A cor (branca, para não alterar)
        cx, cy,                 // O centro da transformação (canto superior esquerdo)
        dx, dy,                 // A posição final na tela
        pa,     // Escala no eixo X
        pa,     // Escala no eixo Y
        0,                    // Ângulo de rotação (0 = sem rotação)
        0                       // Flags (0 = sem espelhamento)
    );
}


// JA ///////////////////////////

void draw_ja(float camera_x, Jet_alone *ja, entities_sprites *sprites) {
    ALLEGRO_BITMAP *sprite_sheet = NULL;

    int row = 0;
    if (ja->state == JA_WALK && !ja->is_shooting)
        row = 1;
    ja_sprite (ja, &sprite_sheet, sprites);
    if (!sprite_sheet) {
        printf("DEU ERRO \n");
        exit(1);
    }

    int frame_x = ja->current_frame * 512;
    int frame_y = row * 512;

    int flip_flag;
    if (ja->direction == 1) flip_flag = ALLEGRO_FLIP_HORIZONTAL;
    else flip_flag = 0;

    //a priori não tem tingimento, mas se ele levar dano tem
    ALLEGRO_COLOR tint_color = al_map_rgb(255, 255, 255);

    if(ja->is_taking_damage) ja->is_taking_damage = 0;
    else
        al_draw_tinted_scaled_bitmap(
            sprite_sheet,        // O bitmap de onde vamos tirar o sprite.
            tint_color,          // A cor de tingimento.
            frame_x, frame_y,    // Posição (x,y) do frame na spritesheet.
            511, 511,            // Largura e Altura DO FRAME ORIGINAL na spritesheet.
            ja->x - camera_x,    // Posição final (x) na tela onde será desenhado.
            ja->y,               // Posição final (y) na tela onde será desenhado.
            JA_WIDTH, JA_HEIGHT, // LARGURA E ALTURA FINAL do sprite na tela (redimensionado).
            flip_flag
        );

}

void draw_ja_bullets(float camera_x, Jet_alone *ja,entities_sprites *sprites) {
    ja_bullet *shot = ja->ja_buster->shots;
    ALLEGRO_BITMAP *sprite_sheet = sprites->jet_alone_shot;

    while(shot != NULL) {
        // Posição do frame na folha de sprites (source_x)
        float sx = shot->current_frame * 36;

        // Posição na tela (destination_x), ajustada para centralizar o sprite
        // Posição do tiro - deslocamento da câmera - metade da largura do sprite
        float dx = (shot->x - camera_x) - (JA_BULLET_WIDTH / 2.0f);
        float dy = shot->y - (JA_BULLET_HEIGHT / 2.0f);

        int flags;
        if (shot->trajectory == -1) flags = ALLEGRO_FLIP_HORIZONTAL;
        else flags = 0;

        al_draw_scaled_bitmap(sprite_sheet,
                                sx, 0,           // Posição (sx, sy) e
                                36, 36, // tamanho do frame na imagem original
                                dx, dy,            // Posição (dx, dy) e
                                JA_BULLET_WIDTH , JA_BULLET_HEIGHT, // tamanho (dw, dh) final na tela
                                flags);

        shot = (ja_bullet*)shot->next;
    }
}