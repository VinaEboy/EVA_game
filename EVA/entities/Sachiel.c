#include "Sachiel.h"
#include <stdlib.h> 
#include <math.h>

//cria o chefão
Sachiel *create_sa(float dificulty, int X_SCREEN, int Y_SCREEN) {
    Sachiel *sa = (Sachiel *) malloc(sizeof(Sachiel));
    if (!sa) return NULL;

    sa->life = 400*dificulty;
    sa->max_life = 400*dificulty;
    
    sa->damage = 50*dificulty; //dano em caso de contato do player com o heart do sachiel
    sa->is_dead = 0;
    sa->death_timer = 0;

    sa->height = Y_SCREEN*0.85, 
    sa->width = X_SCREEN*0.3;
    sa->heart_height = Y_SCREEN*0.14, 
    sa->heart_width = Y_SCREEN*0.14;
    
    sa->top_margin_default = Y_SCREEN*0.15;
    sa->ground_margin_default = Y_SCREEN*0.55;
    sa->top_margin_transition =  Y_SCREEN*0.33;
    sa->left_margin = X_SCREEN*0.2;
    sa->right_margin = X_SCREEN*0.2;
    sa->minor_step_1 = 0; //no switching side ele fica pequeno (step 1)
    sa->minor_step_2 = 0; // e depois volta ao normal (step 2);

    sa->level_width = X_SCREEN*7; //metadado
    sa->x = sa->level_width - sa->right_margin; 
    sa->y = Y_SCREEN - 0.07*Y_SCREEN - sa->height/2;
    sa->vx = 0,
    sa->vy = 0;
    sa->center_x = sa->x + sa->heart_width/2, 
    sa->center_y = sa->y + sa->heart_height/2;
    sa->hit_box_x = sa->heart_width, 
    sa->hit_box_y = sa->heart_height;
    sa->heart_direction = -1; // -1 é para cima, 1 é para baixo
    
    sa->state = SA_DEFAULT;
    sa->position_timer = 0; //timer para o coração trocar de posição na tela ou não
    sa->fire_timer = 0; //timer para ele atirar
    sa->frame_minor_part = 1; //o sprites do Sachiel são grandes demais e uma animação tive que colocar em 3 pngs

    sa->current_frame = 0;
    sa->frame_timer = 0;

    sa->bersek_mode = 0;
    sa->is_invencible = 0;
    sa->invencible_timer = 0;
    sa->hit_take = 0;
    sa->is_left = 0;
    sa->is_right = 1;

    sa->is_minor = 0; //se ele está encolhido ou nao
    sa->side_switched = 0; //se já terminou de trocar de lado

    sa->heart_speed = X_SCREEN*0.003;
    sa->frequency_fire = 75/dificulty; //ao decorrer da luta, o tiro do chefão fica mais frequente
    sa->fire_speed = X_SCREEN*0.015*dificulty;
    sa->arm_up_timer = 0;

    sa_buster_t *sa_buster = sa_buster_create(dificulty);
    if (!sa_buster) {
        free(sa);
        return NULL;
    }
    sa->sa_buster = sa_buster;
    sa->shot_timer = 0;

    return sa;
}

//funções para atualizar tudo que é necessário do Sachiel
void update_sa(Sachiel *sa, Player *player, int X_SCREEN, int Y_SCREEN) {
    update_state_sa(sa, player, X_SCREEN, Y_SCREEN);
    action_sa(sa, X_SCREEN, Y_SCREEN);
}

// atualiza o estado dele 
void update_state_sa (Sachiel *sa, Player *player, int X_SCREEN, int Y_SCREEN) {
    if (sa->life <= 0) {
        sa->death_timer++;
        if (sa->death_timer > SACHIEL_DEATH_TIME)
            sa->is_dead = 1;
        return;
    }

    if (sa->arm_up_timer > 0) sa->arm_up_timer--;
    
    sa->position_timer++;
    sa->fire_timer++;
    if (sa->hit_take) {
        sa->is_invencible = 1;
        sa->invencible_timer++;
        if (sa->invencible_timer > INVENCIBLE_TIME) {
            sa->hit_take = 0;
            sa->invencible_timer = 0;
            sa->is_invencible = 0;
        }
    }

    // Ele entra em desespero!
    if (sa->life <= sa->max_life*0.4 && !sa->bersek_mode) {
        sa->frequency_fire /= 1.5;
        sa->fire_speed *= 1.5;
        sa->heart_speed *= 1.5;
        sa->bersek_mode = 1;
    }


    if (sa->state == SA_SWITCHING_SIDE) sa->fire_timer = 0; //ele não vai atirar enquanto muda de lado
    
    if (sa->fire_timer > sa->frequency_fire) {
        sa->arm_up_timer = SA_ARM_UP_TIME;
        if (sa->is_left && (player->x >= sa->level_width - X_SCREEN*0.25 || player->x <= sa->x) ) 
            sa->state = SA_PLAYER_BELOW;
        else if (sa->is_right && (player->x <= sa->level_width - X_SCREEN*0.9 || player->x >= sa->x)) 
            sa->state = SA_PLAYER_BELOW;

        else if ( (float)(rand() % 101) / 100 < SHOT_UP_PROBABILITY )
            sa->state = SA_UP_SHOT;
        else
            sa->state = SA_DOWN_SHOT;

    } else if (sa->position_timer >= POSITION_TIME) {
        sa->state = SA_SWITCHING_SIDE;
    } else if (sa->arm_up_timer == 0) {
        sa->state = SA_DEFAULT;
    }
}

//o coração vai ter 2 modos de andar: O modo padrão 0 que ele fica indo para cima e para baixo na ETAPA1
//e o modo de transição que ele vai para outro lado da tela, no modo 2
void update_heart_position (Sachiel *sa, int level_width, int X_SCREEN, int Y_SCREEN) {

    // definir a priori a nova posição e se necessário corrigir
    sa->x += sa->vx;
    sa->y += sa->vy;
    if (sa->state == SA_DEFAULT || sa->state == SA_PLAYER_BELOW || sa->state == SA_UP_SHOT || sa->state == SA_DOWN_SHOT) {
        if (sa->y <= sa->top_margin_default) sa->y = sa->top_margin_default;
        else if (sa->y >= Y_SCREEN - sa->ground_margin_default) sa->y = Y_SCREEN - sa->ground_margin_default;
    }
    else if (sa->state == SA_SWITCHING_SIDE) {
        if (sa->y < sa->top_margin_transition) sa->y = sa->top_margin_transition;

        if (sa->x <= level_width - X_SCREEN + sa->left_margin) sa->x = level_width - X_SCREEN + sa->left_margin;
        else if (sa->x >= level_width - sa->right_margin) sa->x = level_width - sa->right_margin;
    }

    sa->center_x = sa->x + sa->heart_width/2;
    sa->center_y = sa->y + sa->heart_height/2;
}

// faz a ação correspondente ao estado dele
void action_sa(Sachiel *sa, int X_SCREEN, int Y_SCREEN) {
    if (sa->life <= 0) return;

    switch (sa->state) {
        case SA_DEFAULT:
            heart_default_move(sa,X_SCREEN,Y_SCREEN);
            break; 
        case SA_PLAYER_BELOW:
        case SA_UP_SHOT:
        case SA_DOWN_SHOT:
            sa_buster_fire(sa,X_SCREEN,Y_SCREEN); //ele atira, dai o estado dele determina como ele vai atirar
            heart_default_move(sa,X_SCREEN,Y_SCREEN);
            break;
        case SA_SWITCHING_SIDE:
            switching_side_sa(sa, X_SCREEN);
            break;
        default:
            heart_default_move(sa,X_SCREEN,Y_SCREEN);
            break;
    }
}

////////////////////////////// AÇÕES DOS ESTADOS ////////////////////////////////////////////////

//movimento default do coração
void heart_default_move(Sachiel *sa, int X_SCREEN, int Y_SCREEN) {
    if (sa->heart_direction == -1) {
        if (sa->y > sa->top_margin_default) sa->vy = -sa->heart_speed;
        else sa->heart_direction = 1;
    }
    else if (sa->heart_direction == 1) {
        if (sa->y < Y_SCREEN - sa->ground_margin_default) sa->vy = sa->heart_speed;
        else sa->heart_direction = -1;
    }
}

// ação dele mudar de lado, incluindo animação
void switching_side_sa(Sachiel *sa, int X_SCREEN) {

    //ainda não trocou de lado da fase
    if (!sa->side_switched) {

        //ainda não ficou pequeno
        if (!sa->minor_step_1) {
            sa->current_frame = sa->frame_timer/MINOR_ANIMATION % 2;
           
            sa->frame_timer++;
            if (sa->frame_timer < 2*MINOR_ANIMATION) sa->frame_minor_part = 1;
            else if (sa->frame_timer < 4*MINOR_ANIMATION) sa->frame_minor_part = 2;
            else if (sa->frame_timer < 6*MINOR_ANIMATION) sa->frame_minor_part = 3;
            else {
                sa->minor_step_1 = 1;
                sa->heart_direction = -1; //vai subir pra cima o coração
                sa->frame_timer = 6*MINOR_ANIMATION - 1; //para anular o próximo frame_timer++
            }
        }

        if (sa->y > sa->top_margin_transition) sa->vy = -sa->heart_speed;
        else if (sa->minor_step_1){
                sa->vy = 0;
                if (sa->is_right) {
                    if (sa->x > sa->level_width - X_SCREEN + sa->left_margin) sa->vx = -3*sa->heart_speed;
                    else {
                        sa->side_switched = 1;
                        sa->vx = 0;
                        sa->is_right = 0;
                        sa->is_left = 1;
                    }
                } else {
                    if (sa->x < sa->level_width - sa->right_margin) sa->vx = 3*sa->heart_speed;
                    else {
                        sa->side_switched = 1;            
                        sa->vx = 0;
                        sa->is_right = 1;
                        sa->is_left = 0;
                    }    
                }
            
        }
    }

    else {
        //ainda não ficou maior (saiu do coração)
        if (!sa->minor_step_2) {
            sa->current_frame = sa->frame_timer/MINOR_ANIMATION % 2;
                
            sa->frame_timer--;       

            if (sa->frame_timer < 0) {
                sa->frame_timer = 0;
                sa->minor_step_2 = 1; // voltou ao tamanho normal
                //não vou fazer o coração "descer" até uma posição em especifico
            }
            //lógica inversa
            else if (sa->frame_timer < 2*MINOR_ANIMATION) sa->frame_minor_part = 1;
            else if (sa->frame_timer < 4*MINOR_ANIMATION) sa->frame_minor_part = 2;
            else if (sa->frame_timer < 6*MINOR_ANIMATION) sa->frame_minor_part = 3;
          
        }

        else {
            sa->state = SA_DEFAULT; //volta ao normal
            sa->side_switched = 0;
            sa->minor_step_1 = 0;
            sa->minor_step_2 = 0;
            sa->position_timer = 0;
        }
    }

} 

// sprite correspondente ao estado dele, útil para o arquivo Draw
void sa_sprite (Sachiel *sa, ALLEGRO_BITMAP **sprite_sheet, entities_sprites *sprites) {
    switch (sa->state) {
        case SA_DEFAULT:
        case SA_PLAYER_BELOW:
            *sprite_sheet = sprites->sa_default_and_under;
            if (sa->state == SA_PLAYER_BELOW) sa->current_frame = 1;
            else sa->current_frame = 0;
            break; 
        case SA_UP_SHOT:
        case SA_DOWN_SHOT:
            *sprite_sheet = sprites->sa_shot;
            if (sa->state == SA_UP_SHOT) sa->current_frame = 0;
            else sa->current_frame = 1;
            break;
        case SA_SWITCHING_SIDE:
            if (sa->frame_minor_part == 1)
                *sprite_sheet = sprites->sa_minor_p1;
            else if (sa->frame_minor_part == 2)
                *sprite_sheet = sprites->sa_minor_p2;
            else if (sa->frame_minor_part == 3)
                *sprite_sheet = sprites->sa_minor_p3;
            break;
        default:
            *sprite_sheet = sprites->sa_default_and_under;
            break;
    }
}


// ação de atirar de acordo com o estado em que ele está
void sa_buster_fire(Sachiel *sa, int X_SCREEN, int Y_SCREEN) {
    sa_bullet *shot = NULL;
    if (sa->arm_up_timer != SA_ARM_UP_TIME) return; //significa que já atirou a primeira vez que entrou no estado
    
    float x;
    float y;
    int direction = -1;
    int type = 1;
    if (sa->is_left) direction = 1;

    if(sa->state == SA_PLAYER_BELOW) {
        type = 2;
        x = sa->center_x;
        y = sa->ground_margin_default + sa->height*0.2;
    }

    else if (sa->state == SA_UP_SHOT) {
        if (sa->is_left) x = sa->x + sa->width/2 - sa->heart_width/2;
        else x = sa->x - sa->width/2 + sa->heart_width/2;
        y = sa->ground_margin_default + Y_SCREEN*0.05;
        type = 3;
    }
    else if (sa->state == SA_DOWN_SHOT) {
        if (sa->is_left) x = sa->x + sa->width/2 - sa->heart_width/2;
        else x = sa->x - sa->width/2 + sa->heart_width/2;
        y = sa->ground_margin_default + Y_SCREEN*0.3;
    }

    shot = sa_bullet_create(sa->sa_buster->dificulty, type*sa->fire_speed, x, y, direction, sa->sa_buster->shots, X_SCREEN, Y_SCREEN, type);
    if (shot) sa->sa_buster->shots = shot;

    sa->fire_timer = 0;
}

// libera memória
void sa_destroy(struct Sachiel *sa) {
    sa_buster_destroy(sa->sa_buster);
    free(sa);
}