#include "Precompiled.h"

#include "ParticleSystem.h"
#include "EnemySystem.h"
#include "Player.h"

int main(){
	printf("BaconEngine starting\n");

	srand(time(NULL));

	al_init();
	al_set_new_display_flags(ALLEGRO_OPENGL);

	/* INIT THE SYSTEM */

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *background = NULL;
	ALLEGRO_MIXER *mixer = NULL;

	if(!al_init()){
		printf("Allegro is bugged");
		return 1;
	}

	if(!al_install_audio()){
		fprintf(stderr, "failed to initialize audio!\n");
		return -1;
	}
 
	if(!al_init_acodec_addon()){
		fprintf(stderr, "failed to initialize audio codecs!\n");
		return -1;
	}

	mixer = al_create_mixer(44100,ALLEGRO_AUDIO_DEPTH_UINT24,ALLEGRO_CHANNEL_CONF_2);

	if (!al_reserve_samples(15)){
		fprintf(stderr, "failed to reserve samples!\n");
		return -1;
	}

	display = al_create_display(SCREEN_WIDTH,SCREEN_HEIGHT);
	if(!display) {
		return 1;
	}

	al_set_window_title(display,"Lights go out, zombies come out!");

	if(!al_init_image_addon()){
		return false;
	}
	al_install_keyboard();
	al_install_mouse();

	timer = al_create_timer(1.0 / FPS);
	if(!timer) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}

	event_queue = al_create_event_queue();
	if(!event_queue) {
		printf("Something is not working... event_queue is broken");
		return 1;
	}

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	background = al_create_bitmap(SCREEN_WIDTH,SCREEN_HEIGHT);
	
	al_set_target_bitmap(background);

	al_clear_to_color(al_map_rgb(20,28,24));

	al_set_target_backbuffer(display);

	/* SYSTEM INITS DONE */
	/* INIT GAME STUFF */

	particleSystem.init(background,display);
	enemySystem.init(display,background);
	player.init();

	al_start_timer(timer);

	bool redraw = true;
	while(true){
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		/*Process input*/
		if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
			break;
		}

		if (ev.type == ALLEGRO_EVENT_TIMER) {
			/*GAME LOGIC*/
			player.update();
			redraw = true;
		}

		if (ev.type == ALLEGRO_EVENT_MOUSE_AXES || ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY){
			player.setMouseXY(ev.mouse.x, ev.mouse.y);
		}

		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
			if(ev.mouse.button == 1){
				player.keyShoot = true;
			}
		}

		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
			if(ev.mouse.button == 1){
				player.keyShoot = false;
			}
		}

		if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
			if(ev.keyboard.keycode == ALLEGRO_KEY_W){
				player.keyUp = true;
			}
			if(ev.keyboard.keycode == ALLEGRO_KEY_S){
				player.keyDown = true;
			}
			if(ev.keyboard.keycode == ALLEGRO_KEY_A){
				player.keyLeft = true;
			}
			if(ev.keyboard.keycode == ALLEGRO_KEY_D){
				player.keyRight = true;
			}
			if(ev.keyboard.keycode == ALLEGRO_KEY_R){
				player.keyReload = true;
			}
		}

		if(ev.type == ALLEGRO_EVENT_KEY_UP){
			if(ev.keyboard.keycode == ALLEGRO_KEY_W){
				player.keyUp = false;
			}
			if(ev.keyboard.keycode == ALLEGRO_KEY_S){
				player.keyDown = false;
			}
			if(ev.keyboard.keycode == ALLEGRO_KEY_A){
				player.keyLeft = false;
			}
			if(ev.keyboard.keycode == ALLEGRO_KEY_D){
				player.keyRight = false;
			}
		}

		if (redraw && al_event_queue_is_empty(event_queue)) {
			/*RENDER*/
			al_set_target_backbuffer(display);
			al_draw_bitmap(background,0,0,0);
			particleSystem.update();
			enemySystem.update(player.getPosition());
			player.render();

			/*HUD*/

			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
			redraw = false;
		}

	}

	return 0;
}
