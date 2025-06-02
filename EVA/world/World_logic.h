#ifndef __WORLD_LOGIC__
#define __WORLD_LOGIC__

unsigned char collision_2D(square *element_first, square *element_second);
unsigned char check_kill(square *killer, square *victim);

void update_bullets(square *player, int X_SCREEN);

void update_position(square *player_1, square *player_2, int X_SCREEN, int Y_SCREEN);

#endif