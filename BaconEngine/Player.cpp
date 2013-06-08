#include "Precompiled.h"
#include "Player.h"

Player player;

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

	hp = 100;

	printf("Player init done!");
	return true;
}

/**
 * Render the player
 */
void Player::render(){
	if(hp < 0){
		return;
	}
	al_draw_rotated_bitmap(player ,16 ,16 ,position.x ,position.y , position.getRadianToPoint(target) ,0);
}

/**
 * Apply physics and stuff to player
 */
void Player::update(){
	--loadTicks;

	if(hp < 0){
		return;
	}

	if(keyShoot == true){
		if(loadTicks < 0){
			if(ammo > 0){
				//FIRE!
				particleSystem.addParticle(position.x,position.y,1 ,1,15,25,20,PARTICLE_CASE,false,true,(getAngle() * (180/PI)),70,100);
				particleSystem.addParticle(position.x,position.y,2,5,20,2 ,5 ,PARTICLE_DUST,false,true,(getAngle() * (180/PI)),-20,20);
				particleSystem.addParticle(position.x,position.y,2,5,20,2 ,5 ,PARTICLE_FIRE,false,false,(getAngle() * (180/PI)),-20,20);
				--ammo;

				//Calculate the effect
				enemySystem.calculateShot(position,target);

				//Shooting interval
				loadTicks = 5;
			}else{
				//RELOAD
				ammo = 30;
				loadTicks = 38;

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

	if(position.x > SCREEN_WIDTH){
		position.x = SCREEN_WIDTH;
	}

	if(position.x < 0){
		position.x = 0;
	}

	if(position.y > SCREEN_HEIGHT){
		position.y = SCREEN_HEIGHT;
	}

	if(position.y < 0){
		position.y = 0;
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

void Player::applyDamage(int amount){
	if(hp < 0){
		return;//Player is already dead
	}

	hp = hp - amount;

	if(hp < 0){
		printf("GAME OVER!\n");
		particleSystem.addParticle(position.x,position.y,45,-10,10,15,40,PARTICLE_BLOOD,true,true);
	}
}