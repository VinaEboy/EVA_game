#ifndef __JOYSTICK__
#define __JOYSTICK__
#include "../entities/Player.h"
#include "../gameflow/Game_state.h"

void joystick_update(game_state *state, Player *player);
void joystick_handle(ALLEGRO_EVENT *event, game_state *state, Player *player);

void joystick_jump(Player *player);
void joystick_down(Player *player);

#endif