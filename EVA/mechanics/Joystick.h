#ifndef __JOYSTICK__
#define __JOYSTICK__

// O tempo que demora para carregar da fase anterior até a fase da bala, em frames
#define BULLET_2_TIME 25
#define BULLET_3_TIME 25

// implementação da leitura do teclado quando o jogador está controlando o personagem

#include "../entities/Player.h"
#include "../gameflow/Game_state.h"

// verifica as teclas pressionadas de forma contínua
// é chamado no evento de tempo
void joystick_update(game_state *state, Player *player);

// Verifica chamadas pontuais (apertos de teclas)
void joystick_handle(ALLEGRO_EVENT *event, game_state *state, Player *player, int X_SCREEN, int Y_SCREEN);

//////////////////////////////////// AUXILIARES ////////////////////////////////////////////

// lógica do pulo
void joystick_jump(Player *player);

// lógica de agachar
void joystick_down(Player *player);

// lógica de levantaar
void joystick_stand_up(Player *player);

#endif