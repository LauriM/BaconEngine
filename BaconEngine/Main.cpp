#include <stdio.h>
#include <allegro5\allegro5.h>

int main(){
	printf("BaconEngine starting\n");
	al_init();
	al_set_new_display_flags(ALLEGRO_GENERATE_EXPOSE_EVENTS);

	ALLEGRO_DISPLAY *display;

	display = al_create_display(800, 600);
	if(!display) {
		return 1;
	}

	al_install_keyboard();

	return 0;
}