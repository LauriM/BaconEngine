#include "Precompiled.h"

#include "Player.h"

/**
 * Init the player and load the media
 */
bool Player::init(){
	player = al_load_bitmap("player.png");

	if(player == NULL){
		printf("Invalid media folders!");
		return false;
	}

	position.x = 200;
	position.y = 200;
	target.x = 0;
	target.y = 0;

	printf("Player init done!");
	return true;
}

/**
 * Render the player
 */
void Player::render(){
	al_draw_rotated_bitmap(player ,10 ,10 ,position.x ,position.y , 0.5 ,0);
}

/**
 * Apply physics and stuff to player
 */
void Player::update(){
	printf("target: %i %i\n",target.x,target.y);
}


void Player::setMouseXY(int x,int y){
	target.x = x;
	target.y = y;
}

void Player::setMouseX(int x){
	target.x = x;
}

void Player::setMouseY(int y){
	target.y = y;
}