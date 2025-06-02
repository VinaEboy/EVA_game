#include <allegro5/allegro5.h>																																												
#include <allegro5/allegro_font.h>																																											
#include <allegro5/allegro_primitives.h>																																									

unsigned char collision_2D(square *element_first, square *element_second){																																	

	if ((((element_second->y-element_second->side/2 >= element_first->y-element_first->side/2) && (element_first->y+element_first->side/2 >= element_second->y-element_second->side/2)) || 	
		((element_first->y-element_first->side/2 >= element_second->y-element_second->side/2) && (element_second->y+element_second->side/2 >= element_first->y-element_first->side/2))) && 	
		(((element_second->x-element_second->side/2 >= element_first->x-element_first->side/2) && (element_first->x+element_first->side/2 >= element_second->x-element_second->side/2)) || 	
		((element_first->x-element_first->side/2 >= element_second->x-element_second->side/2) && (element_second->x+element_second->side/2 >= element_first->x-element_first->side/2)))) return 1;			
	else return 0;																																															
}

unsigned char check_kill(square *killer, square *victim){																																					

	bullet *previous = NULL;
	for (bullet *index = killer->gun->shots; index != NULL; index = (bullet*) index->next){																													
		if ((index->x >= victim->x - victim->side/2) && (index->x <= victim->x + victim->side/2) && 
		   (index->y >= victim->y - victim->side/2) && (index->y <= victim->y + victim->side/2)){																											
			victim->hp--;																																													
			if (victim->hp){																																												
				if (previous){																																												
					previous->next = index->next;																																							
					bullet_destroy(index);																																									
					index = (bullet*) previous->next;																																						
				}
				else {																																														
					killer->gun->shots = (bullet*) index->next;																																				
					bullet_destroy(index);																																									
					index = killer->gun->shots;																																								
				}
				return 0;																																													
			}
			else return 1;																																													
		}
		previous = index;																																													
	}
	return 0;																																																
}

void update_bullets(square *player, int X_SCREEN){																																										
	
	bullet *previous = NULL;																																												
	for (bullet *index = player->gun->shots; index != NULL;){																																				
		if (!index->trajectory) index->x -= BULLET_MOVE;																																					
		else if (index->trajectory == 1) index->x += BULLET_MOVE;																																			
		
		if ((index->x < 0) || (index->x > X_SCREEN)){																																						
			if (previous){																																													
				previous->next = index->next;																																								
				bullet_destroy(index);																																										
				index = (bullet*) previous->next;																																							
			}
			else {																																															
				player->gun->shots = (bullet*) index->next;																																					
				bullet_destroy(index);																																										
				index = player->gun->shots;																																									
			}
		}
		else{																																																
			previous = index;																																												
			index = (bullet*) index->next;																																									
		}
	}
}

void update_position(square *player_1, square *player_2, int X_SCREEN, int Y_SCREEN){																																					

	if (player_1->control->left){																																											
		square_move(player_1, 1, 0, X_SCREEN, Y_SCREEN);																																					
		if (collision_2D(player_1, player_2)) square_move(player_1, -1, 0, X_SCREEN, Y_SCREEN);																												
	}
	if (player_1->control->right){																																											
		square_move(player_1, 1, 1, X_SCREEN, Y_SCREEN);																																					
		if (collision_2D(player_1, player_2)) square_move(player_1, -1, 1, X_SCREEN, Y_SCREEN);																												
	}
	if (player_1->control->up) {																																											
		square_move(player_1, 1, 2, X_SCREEN, Y_SCREEN);																																					
		if (collision_2D(player_1, player_2)) square_move(player_1, -1, 2, X_SCREEN, Y_SCREEN);																												
	}
	if (player_1->control->down){																																											
		square_move(player_1, 1, 3, X_SCREEN, Y_SCREEN);																																					
		if (collision_2D(player_1, player_2)) square_move(player_1, -1, 3, X_SCREEN, Y_SCREEN);																												
	}

	if (player_2->control->left){																																											
		square_move(player_2, 1, 0, X_SCREEN, Y_SCREEN);																																					
		if (collision_2D(player_2, player_1)) square_move(player_2, -1, 0, X_SCREEN, Y_SCREEN);																												
	}
	
	if (player_2->control->right){ 																																											
		square_move(player_2, 1, 1, X_SCREEN, Y_SCREEN);																																					
		if (collision_2D(player_2, player_1)) square_move(player_2, -1, 1, X_SCREEN, Y_SCREEN);																												
	}
	
	if (player_2->control->up){																																												
		square_move(player_2, 1, 2, X_SCREEN, Y_SCREEN);																																					
		if (collision_2D(player_2, player_1)) square_move(player_2, -1, 2, X_SCREEN, Y_SCREEN);																												
	}
	if (player_2->control->down){																																											
		square_move(player_2, 1, 3, X_SCREEN, Y_SCREEN);																																					
		if (collision_2D(player_2, player_1)) square_move(player_2, -1, 3, X_SCREEN, Y_SCREEN);																												
	}
	if (player_1->control->fire){																																											
		if (!player_1->gun->timer){																																											
			square_shot(player_1); 																																											
			player_1->gun->timer = PISTOL_COOLDOWN;																																							
		} 
	}
	if (player_2->control->fire){																																											
		if (!player_2->gun->timer){																																											
			square_shot(player_2);																																											
			player_2->gun->timer = PISTOL_COOLDOWN;																																							
		}
	}
	update_bullets(player_1, X_SCREEN);																																												
	update_bullets(player_2, X_SCREEN);																																												
}