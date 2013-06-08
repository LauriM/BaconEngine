#include "Precompiled.h"

#include "Player.h"

int main(){
	printf("BaconEngine starting\n");
	al_init();
	al_set_new_display_flags(ALLEGRO_OPENGL);

	/* INIT THE SYSTEM */

	ALLEGRO_DISPLAY *display;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;

	display = al_create_display(1000, 900);
	if(!display) {
		return 1;
	}

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

	/* SYSTEM INITS DONE */
	/* INIT GAME STUFF */

	Player player;
	player.init();

	bool gameLoop = true;
	while(gameLoop){
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		/*Process input*/
		if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
			gameLoop = false;
		}

		/*Rendering stuff*/
		player.render();

		al_flip_display();
		al_clear_to_color(al_map_rgb(0,0,0));
	}

	return 0;
}
