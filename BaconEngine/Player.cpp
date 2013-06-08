#include "Player.h"

/**
 * Init the player and load the media
 */
bool Player::init(){
	player = al_load_bitmap("player.png");

	keyShoot = false;

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
	al_draw_rotated_bitmap(player ,16 ,16 ,position.x ,position.y , position.getRadianToPoint(target) ,0);
}

/**
 * Apply physics and stuff to player
 */
void Player::update(){
	--loadTicks;

	if(keyShoot == true){
		if(loadTicks < 0){
			//Effects!
			particleSystem.addParticle(position.x,position.y,1 ,5,15,25,20,PARTICLE_CASE,false,true,(getAngle() * (180/PI)),70,100);
			particleSystem.addParticle(position.x,position.y,25,5,20,2 ,5 ,PARTICLE_DUST,false,true,(getAngle() * (180/PI)),-20,20);
			particleSystem.addParticle(position.x,position.y,45,5,20,2 ,5 ,PARTICLE_FIRE,false,false,(getAngle() * (180/PI)),-20,20);

			//Shooting interval
			loadTicks = 5;
		}
	}
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

float Player::getAngle(){
	return position.getRadianToPoint(target);
}