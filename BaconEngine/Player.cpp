#include "Precompiled.h"

#include "Player.h"

bool Player::init(){
	player = al_load_bitmap("player.png");

	if(player == NULL){
		printf("Invalid media folders!");
		return false;
	}

	position.x = 200;
	position.y = 200;

	printf("Player init done!");
	return true;
}

void Player::render(){
	al_draw_rotated_bitmap(player ,0,0 ,position.x ,position.y , 0.5 ,0);
}