#include <allegro5/allegro5.h>																																												
#include <allegro5/allegro_font.h>																																											
#include <allegro5/allegro_primitives.h>																																									
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include "gameflow/Game_state.h"

void destroy(game_state *state, ALLEGRO_FONT *font, ALLEGRO_DISPLAY *disp, ALLEGRO_TIMER *timer, ALLEGRO_EVENT_QUEUE *queue ) {

	if(state) game_state_destroy(state);
	if(font) al_destroy_font(font);																																													
	if(disp) al_destroy_display(disp);																																												
	if(timer) al_destroy_timer(timer);																																												
	if(queue) al_destroy_event_queue(queue);																																																																																						
}


int main(){
	al_init();																																																
	al_init_primitives_addon();																																												
	al_init_image_addon();
	al_install_keyboard();
	al_init_font_addon();      // necessário para qualquer tipo de fonte
	al_init_ttf_addon();       // necessário para fontes .ttf																																													


	ALLEGRO_TIMER *timer = al_create_timer(1.0 / 30.0);																																						
	ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();																																					
	ALLEGRO_FONT *font = al_create_builtin_font();		
	font = al_load_ttf_font("fonts/Press_Start_2P/PressStart2P-Regular.ttf", 24, 0);
	ALLEGRO_DISPLAY_MODE mode;
	
	al_get_display_mode(0, &mode); 

	int X_SCREEN = mode.width;
	int Y_SCREEN = mode.height;
	al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
	ALLEGRO_DISPLAY *disp = al_create_display(X_SCREEN, Y_SCREEN);																																			


	al_register_event_source(queue, al_get_keyboard_event_source());																																		
	al_register_event_source(queue, al_get_display_event_source(disp));																																		
	al_register_event_source(queue, al_get_timer_event_source(timer));																																		
	game_state *state = game_state_create();
	if (!state) {
		destroy(state,font,disp,timer,queue);
		return 1; 
	}

	ALLEGRO_EVENT event;																																													
	al_start_timer(timer);																																													

	//ponteiros que vão ser utilizados no jogo
	ALLEGRO_BITMAP *title_screen_image = NULL; //para não dar warning de usar var não inicializada
	title_screen *title_screen_info = NULL;
	options *options_info = NULL;


	while(state->running){																																																
		al_wait_for_event(queue, &event);																																									

		if (state->options) {
			if (!state->options_started)
				start_options(state, &options_info);

			show_options(&event,state,font,disp,options_info,X_SCREEN,Y_SCREEN);
		}

		else if (state->title_screen) {
			if (!state->title_screen_started) 
				start_title_screen(state, &title_screen_image,&title_screen_info);
			
			show_title_screen(&event, state, font, disp, title_screen_image,title_screen_info, X_SCREEN, Y_SCREEN);
		}

		else if (state->level_select) {
			state->level_select = 0;
			state->level_sachiel = 1;
		}

		else if (state->load_game) {
			state->running = 0;
		}

		else if (state->level_sachiel) {
			state->running = 0;
			if (!state->level_sachiel_started)
				start_level_sachiel( );

			show_level_sachiel( );
		}

		
	}

	destroy(state,font,disp,timer,queue);
	return 0;
}