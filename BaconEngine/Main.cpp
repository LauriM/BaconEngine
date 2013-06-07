#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

int main(){
	printf("BaconEngine starting\n");
	al_init();
	al_set_new_display_flags(ALLEGRO_OPENGL);

	ALLEGRO_DISPLAY *display;

	display = al_create_display(800, 600);
	if(!display) {
		return 1;
	}

	if(!al_init_image_addon()){
		return false;
	}

	al_install_keyboard();

	ALLEGRO_BITMAP *player;

	player = al_load_bitmap("player.png");

	if(player == NULL){
		printf("Invalid media folders!");
		return 1;
	}

	bool gameLoop = true;
	gameLoop = true;
	while(gameLoop){
		al_draw_rotated_bitmap(player,0,0,0,0, 0 ,0);

		//Flip the screen
		al_flip_display();

		//And then clear it for the next round of drawing events.
		al_clear_to_color(al_map_rgb(0,0,0));
	}

	return 0;
}