#ifndef __SQUARE__ 																																	
#define __SQUARE__																																	

#include "../mechanics/Joystick.h"																																
#include "../items/Pistol.h" 																																

#define SQUARE_STEP 10																																

typedef struct {																																	
	unsigned char side;																																
	unsigned char face;																																
	unsigned char hp;																																
	unsigned short x;																																
	unsigned short y;																																
	joystick *control;																																
	pistol *gun;																																	
} square;																																			

square* square_create(unsigned char side, unsigned char face, unsigned short x, unsigned short y, unsigned short max_x, unsigned short max_y);		
void square_move(square *element, char steps, unsigned char trajectory, unsigned short max_x, unsigned short max_y);								
void square_shot(square *element);																													
void square_destroy(square *element);																												

#endif																																				