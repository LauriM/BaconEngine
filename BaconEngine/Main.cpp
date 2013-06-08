#include "Precompiled.h"

#include "Player.h"

int main(){
	printf("BaconEngine starting\n");
	al_init();
	al_set_new_display_flags(ALLEGRO_OPENGL);

	/* INIT THE SYSTEM */

	ALLEGRO_DISPLAY *display;

	display = al_create_display(1000, 900);
	if(!display) {
		return 1;
	}

	if(!al_init_image_addon()){
		return false;
	}
	al_install_keyboard();

	/* SYSTEM INITS DONE */
	/* INIT GAME STUFF */

	Player player;
	player.init();

	bool gameLoop = true;
	while(gameLoop){
		al_flip_display();
		al_clear_to_color(al_map_rgb(0,0,0));

		player.render();
	}

	return 0;
}