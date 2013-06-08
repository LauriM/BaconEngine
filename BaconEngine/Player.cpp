#include "Player.h"

/**
 * Init the player and load the media
 */
bool Player::init(){
	player = al_load_bitmap("player.png");
	al_convert_mask_to_alpha(player,al_map_rgb(255,0,255));

	keyShoot = false;
	keyUp    = false;
	keyDown  = false;
	keyLeft  = false;
	keyRight = false;

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
			if(ammo > 0){
				//FIRE!
				particleSystem.addParticle(position.x,position.y,1 ,1,15,25,20,PARTICLE_CASE,false,true,(getAngle() * (180/PI)),70,100);
				particleSystem.addParticle(position.x,position.y,5,5,20,2 ,5 ,PARTICLE_DUST,false,true,(getAngle() * (180/PI)),-20,20);
				particleSystem.addParticle(position.x,position.y,5,5,20,2 ,5 ,PARTICLE_FIRE,false,false,(getAngle() * (180/PI)),-20,20);
				--ammo;

				//Shooting interval
				loadTicks = 3;
			}else{
				//RELOAD
				ammo = 30;
				loadTicks = 60;

				particleSystem.addParticle(position.x,position.y,1 ,3,4,5,20,PARTICLE_MAG,false,true,(getAngle() * (180/PI)),70,100);
			}

		}
	}

	if(keyUp == true){
		position.y -= PLAYER_SPEED;
	}

	if(keyDown == true){
		position.y += PLAYER_SPEED;
	}

	if(keyLeft == true){
		position.x -= PLAYER_SPEED;
	}

	if(keyRight == true){
		position.x += PLAYER_SPEED;
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

Vec2<float> Player::getPosition(){
	return position;
}