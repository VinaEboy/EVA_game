#include <stdlib.h>
#include "Square.h"

square* square_create(unsigned char side, unsigned char face, unsigned short x, unsigned short y, unsigned short max_x, unsigned short max_y){			

	if ((x - side/2 < 0) || (x + side/2 > max_x) || (y - side/2 < 0) || (y + side/2 > max_y)) return NULL;												
	if (face > 3) return NULL;																															

	square *new_square = (square*) malloc(sizeof(square));																								
	if (!new_square) return NULL;																														
	new_square->side = side;																															
	new_square->face = face;																															
	new_square->hp = 5;																																	
	new_square->x = x;																																	
	new_square->y = y;																																	
	new_square->control = joystick_create();																											
	new_square->gun = pistol_create();																													
	return new_square;																																	
}

void square_move(square *element, char steps, unsigned char trajectory, unsigned short max_x, unsigned short max_y){									

	if (!trajectory){ if ((element->x - steps*SQUARE_STEP) - element->side/2 >= 0) element->x = element->x - steps*SQUARE_STEP;} 						
	else if (trajectory == 1){ if ((element->x + steps*SQUARE_STEP) + element->side/2 <= max_x) element->x = element->x + steps*SQUARE_STEP;}			
	else if (trajectory == 2){ if ((element->y - steps*SQUARE_STEP) - element->side/2 >= 0) element->y = element->y - steps*SQUARE_STEP;}				
	else if (trajectory == 3){ if ((element->y + steps*SQUARE_STEP) + element->side/2 <= max_y) element->y = element->y + steps*SQUARE_STEP;}			
}

void square_shot(square *element){																														
	bullet *shot;

	if (!element->face) shot = pistol_shot(element->x - element->side/2, element->y, element->face, element->gun);										
	else if (element->face == 1) shot = pistol_shot(element->x + element->side/2, element->y, element->face, element->gun);								
	if (shot) element->gun->shots = shot;
}

void square_destroy(square *element){																													
	
	pistol_destroy(element->gun);																														
	joystick_destroy(element->control);																													
	free(element);																																		
}