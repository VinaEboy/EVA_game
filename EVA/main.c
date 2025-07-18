#include <allegro5/allegro5.h>																																												
#include <allegro5/allegro_font.h>																																											
#include <allegro5/allegro_primitives.h>																																									
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include "gameflow/Game_state.h"
#include "mechanics/Joystick.h"
#include <stdlib.h>
#include <time.h> //para usar no srand
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>


void destroy(game_state *state, ALLEGRO_FONT *font, ALLEGRO_DISPLAY *disp, ALLEGRO_TIMER *timer, ALLEGRO_EVENT_QUEUE *queue, game_assets *assets ) {
	if(state) game_state_destroy(state);
	if(font) al_destroy_font(font);																																													
	if(disp) al_destroy_display(disp);																																												
	if(timer) al_destroy_timer(timer);																																												
	if(queue) al_destroy_event_queue(queue);	
	if(assets) game_assets_destroy(assets);		
	
	al_uninstall_mouse();
    al_uninstall_keyboard();
    al_shutdown_ttf_addon();
    al_shutdown_font_addon();
    al_shutdown_primitives_addon();
    al_shutdown_image_addon();
    al_uninstall_audio(); 
}


int main(){
	al_init();																																																
	al_init_primitives_addon();																																												
	al_init_image_addon();
	al_install_keyboard();
	al_init_font_addon();      // necessário para qualquer tipo de fonte
	al_init_ttf_addon();       // necessário para fontes .ttf																																													
    al_install_audio() ;
    al_init_acodec_addon();
    al_reserve_samples(8) ;


	srand(time(NULL)); //inicia a aleatoriedade do jogo
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

	al_install_mouse();
	al_hide_mouse_cursor(disp); // para esconder o mouse porque não vai ser usado

	al_register_event_source(queue, al_get_keyboard_event_source());																																		
	al_register_event_source(queue, al_get_display_event_source(disp));																																		
	al_register_event_source(queue, al_get_timer_event_source(timer));

	//etapa que o jogo está na main
	game_state *state = game_state_create();
	
	//ponteiros que vão ser utilizados no jogo, como imagens e informações das etapas
	game_assets *assets = game_assets_create();
	if (!state) {
		destroy(state,font,disp,timer,queue,assets);
		return 1; 
	}

	ALLEGRO_EVENT event;																																													
	al_start_timer(timer);																																													


	while(state->running){																																																
		al_wait_for_event(queue, &event);																																									

		if (state->options) {
			if (!state->options_started) 
				start_options(state, &assets->options_info);

			show_options(&event,state,font,disp,assets,X_SCREEN,Y_SCREEN);
		}

		else if (state->pause) {
			if (!state->pause_started)
				start_pause(state, &assets->pause_info, &assets->pause_image);

			show_pause (&event,state,font, disp, assets, X_SCREEN, Y_SCREEN );
		}

		else if (state->save_game) {
			if (!state->save_game_started)
				start_save_game(state, &assets->save_game_info, &assets->save_game_image, &assets->default_slot_image );

			show_save_game(&event, state, font, disp, assets->save_game_image, assets->default_slot_image, assets->save_game_info, X_SCREEN, Y_SCREEN );
		}

		else if (state->load_game) {
			if (!state->load_game_started)
				start_load_game( state, &assets->load_game_info, &assets->load_game_image, &assets->default_slot_image);

			show_load_game(&event, state, font, disp, assets, X_SCREEN, Y_SCREEN);
		}

		else if (state->title_screen) {
			if (!state->title_screen_started) 
				start_title_screen(state,&assets->title_screen_info,&assets->title_screen_image, &assets->current_music);
			
			show_title_screen(&event, state, font, disp, assets->title_screen_image,assets->title_screen_info, X_SCREEN, Y_SCREEN);
		}

		else if (state->level_select) {
			if (!state->level_select_started)
				start_level_select(state, &assets->level_select_info, &assets->level_select_image, &assets->current_music);

			show_level_select(&event, state, font, disp, assets->level_select_image, assets->level_select_info, X_SCREEN, Y_SCREEN, &assets->current_music);
		}

		else if (state->game_over) {
			if (!state->game_over_started)
				start_game_over(state, &assets->game_over_info, &assets->game_over_image, &assets->current_music);

			show_game_over (&event,state,font, disp, assets, X_SCREEN, Y_SCREEN );
		}

		else if (state->game_end) {
			if (!state->game_end_started)
				start_game_end(state, &assets->game_end_info, &assets->game_end_image, &assets->current_music);

			show_game_end(&event,state,font,disp,assets,X_SCREEN,Y_SCREEN);
		}

		else if (state->level_1) {
			if (!state->level_1_started)
				start_level_1(state, &assets->level_1_info, assets->sprites, X_SCREEN, Y_SCREEN, state->checkpoint, &assets->current_music);

			joystick_handle(&event,state,assets->level_1_info->player, X_SCREEN, Y_SCREEN);

			if (event.type == ALLEGRO_EVENT_TIMER) {
				joystick_update(state,assets->level_1_info->player);
				level_1_update(assets->level_1_info,state, X_SCREEN, Y_SCREEN); //atualiza as posições dos inimigos e gravidade
				show_level_1 (&event, state, font, disp, assets->sprites, assets->level_1_info, X_SCREEN, Y_SCREEN);
			}
		}

		else if (state->level_2) {
			if (!state->level_2_started)
				start_level_2(state, &assets->level_2_info, assets->sprites, X_SCREEN, Y_SCREEN, state->checkpoint);

			joystick_handle(&event,state,assets->level_2_info->player, X_SCREEN, Y_SCREEN);

			if (event.type == ALLEGRO_EVENT_TIMER) {
				joystick_update(state,assets->level_2_info->player);
				level_2_update(assets->level_2_info,state, X_SCREEN, Y_SCREEN); //atualiza as posições dos inimigos e gravidade
				show_level_2 (&event, state, font, disp, assets->sprites, assets->level_2_info, X_SCREEN, Y_SCREEN);
			}
		
		}

        else if (state->level_3) {
            if (!state->level_3_started)
                start_level_3(state, &assets->level_3_info, assets->sprites, X_SCREEN, Y_SCREEN, state->checkpoint);

            joystick_handle(&event, state, assets->level_3_info->player, X_SCREEN, Y_SCREEN);

            if (event.type == ALLEGRO_EVENT_TIMER) {
                joystick_update(state, assets->level_3_info->player);
                level_3_update(assets->level_3_info, state, X_SCREEN, Y_SCREEN);
                show_level_3(&event, state, font, disp, assets->sprites, assets->level_3_info, X_SCREEN, Y_SCREEN);
            }
        }

        else if (state->level_4) {
            if (!state->level_4_started)
                start_level_4(state, &assets->level_4_info, assets->sprites, X_SCREEN, Y_SCREEN, state->checkpoint);

            joystick_handle(&event, state, assets->level_4_info->player, X_SCREEN, Y_SCREEN);

            if (event.type == ALLEGRO_EVENT_TIMER) {
                joystick_update(state, assets->level_4_info->player);
                level_4_update(assets->level_4_info, state, X_SCREEN, Y_SCREEN);
                show_level_4(&event, state, font, disp, assets->sprites, assets->level_4_info, X_SCREEN, Y_SCREEN);
            }
        }

        else if (state->level_5) {
            if (!state->level_5_started)
                start_level_5(state, &assets->level_5_info, assets->sprites, X_SCREEN, Y_SCREEN, state->checkpoint);

            joystick_handle(&event, state, assets->level_5_info->player, X_SCREEN, Y_SCREEN);

            if (event.type == ALLEGRO_EVENT_TIMER) {
                joystick_update(state, assets->level_5_info->player);
                level_5_update(assets->level_5_info, state, X_SCREEN, Y_SCREEN);
                show_level_5(&event, state, font, disp, assets->sprites, assets->level_5_info, X_SCREEN, Y_SCREEN);
            }
        }

        else if (state->level_6) {
            if (!state->level_6_started)
                start_level_6(state, &assets->level_6_info, assets->sprites, X_SCREEN, Y_SCREEN, state->checkpoint);

            joystick_handle(&event, state, assets->level_6_info->player, X_SCREEN, Y_SCREEN);

            if (event.type == ALLEGRO_EVENT_TIMER) {
                joystick_update(state, assets->level_6_info->player);
                level_6_update(assets->level_6_info, state, X_SCREEN, Y_SCREEN);
                show_level_6(&event, state, font, disp, assets->sprites, assets->level_6_info, X_SCREEN, Y_SCREEN);
            }
        }

        else if (state->level_7) {
            if (!state->level_7_started)
                start_level_7(state, &assets->level_7_info, assets->sprites, X_SCREEN, Y_SCREEN, state->checkpoint);

            joystick_handle(&event, state, assets->level_7_info->player, X_SCREEN, Y_SCREEN);

            if (event.type == ALLEGRO_EVENT_TIMER) {
                joystick_update(state, assets->level_7_info->player);
                level_7_update(assets->level_7_info, state, X_SCREEN, Y_SCREEN);
                show_level_7(&event, state, font, disp, assets->sprites, assets->level_7_info, X_SCREEN, Y_SCREEN);
            }
        }

        else if (state->level_8) {
            if (!state->level_8_started)
                start_level_8(state, &assets->level_8_info, assets->sprites, X_SCREEN, Y_SCREEN, state->checkpoint);

            joystick_handle(&event, state, assets->level_8_info->player, X_SCREEN, Y_SCREEN);

            if (event.type == ALLEGRO_EVENT_TIMER) {
                joystick_update(state, assets->level_8_info->player);
                level_8_update(assets->level_8_info, state, X_SCREEN, Y_SCREEN);
                show_level_8(&event, state, font, disp, assets->sprites, assets->level_8_info, X_SCREEN, Y_SCREEN);
            }
        }

	}

	destroy(state,font,disp,timer,queue,assets);
	return 0;
}