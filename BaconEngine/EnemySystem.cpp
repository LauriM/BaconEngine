#include "Precompiled.h"
#include "EnemySystem.h"

EnemySystem enemySystem;

void Enemy::update(Vec2<float> target){
	//Render
	al_draw_rotated_bitmap(img ,16 ,16 ,pos.x ,pos.y , pos.getRadianToPoint(target) ,0);

	//Move
	float angle = pos.getRadianToPoint(target);

	if(player.getHP() < 0){
		pos.x += cos(angle) * -ENEMY_SPEED;
		pos.y += sin(angle) * -ENEMY_SPEED;
	}else{
		pos.x += cos(angle) * ENEMY_SPEED;
		pos.y += sin(angle) * ENEMY_SPEED;
	}

	//Hit to player

	if(pos.getDistanceToPoint(player.getPosition()) < 25){
		player.applyDamage(1);
	}

}

void EnemySystem::init(ALLEGRO_DISPLAY *d, ALLEGRO_BITMAP *bg){
	display    = d;
	background = bg;
	
	enemy = al_load_bitmap("enemy.png");
	body = al_load_bitmap("body.png");
	al_convert_mask_to_alpha(enemy,al_map_rgb(255,0,255));
	al_convert_mask_to_alpha(body,al_map_rgb(255,0,255));

	for(int i = 0;i < ENEMY_MAX;++i){
		enemies[i].hp = 0;
	}

	ticksToSpawn = 0;
	spawnSize    = 0;
}

void EnemySystem::update(Vec2<float> target){
	//Update the enemies
	for(int i = 0;i < ENEMY_MAX;++i){
		if(enemies[i].hp > 0){
			enemies[i].update(target);
		}
	}

	//Handle the spawner
	if(ticksToSpawn < 0){
		//Spawn is happening
		spawnSize += randomRange(2,4);

		ticksToSpawn = 10*FPS;//10 seconds

		int count = spawnSize;

		while(count > 0){
			for(int i = 0;i < ENEMY_MAX;++i){
				if(enemies[i].hp < 1){
					//Found empty slot!

					randomRange(0,3);

					//default
					enemies[i].pos.x = randomRange(-1000,0);
					enemies[i].pos.y = randomRange(-1000,0);

					switch(randomRange(0,3)){
					case 0:
						enemies[i].pos.x = randomRange(-1000,0);
						enemies[i].pos.y = randomRange(-1000,0);
						break;
					case 1:
						enemies[i].pos.x = randomRange(1000,2000);
						enemies[i].pos.y = randomRange(1000,2000);
						break;
					case 2:
						enemies[i].pos.x = randomRange(1000,2000);
						enemies[i].pos.y = randomRange(-1000,0);
						break;
					case 3:
						enemies[i].pos.x = randomRange(-1000,0);
						enemies[i].pos.y = randomRange(1000,2000);
						break;
					}

					enemies[i].hp    = 100;
					enemies[i].img   = enemy;

					break;
				}
			}
			--count;
		}
	}

	--ticksToSpawn;
}


void EnemySystem::calculateShot(Vec2<float> from,Vec2<float> to){
	//Tactic is to brute force the way.
	float angle = from.getRadianToPoint(to);

	Vec2<float> pos = from;
	Vec2<float> vel;

	vel.x = cos(angle) * 1;
	vel.y = sin(angle) * 1;

	int rayLen = 0;
	while(rayLen < 800){
		++rayLen;

		pos.x += vel.x;
		pos.y += vel.y;

		for(int i = 0;i < ENEMY_MAX;++i){
			//Check hits
			if(enemies[i].hp > 0){
				if(pos.getDistanceToPoint(enemies[i].pos) < 25){
					enemies[i].hp -= 8;
					//TODO: FIX THIS THING HERE NOW <<<<<<<<<<<<<<<--------------
				//	particleSystem.addParticle(enemies[i].pos.x,enemies[i].pos.y,10,-5,5,20,30,PARTICLE_BLOOD,false,true);
					particleSystem.addParticle(enemies[i].pos.x,enemies[i].pos.y,2,5,20,4 ,8 ,PARTICLE_BLOOD,true,true,(from.getRadianToPoint(to) * (180/PI)),-20,20);

					if(enemies[i].hp < 1){
						//KILL!

						//Draw body to ground first
						al_set_target_bitmap(background);
						al_draw_rotated_bitmap(body,16 ,16 ,enemies[i].pos.x ,enemies[i].pos.y , randomRange(0,360) ,0);
						al_set_target_backbuffer(display);

						particleSystem.addParticle(enemies[i].pos.x,enemies[i].pos.y,25,-10,10,5,8,PARTICLE_BLOOD,true,true);
						particleSystem.addParticle(enemies[i].pos.x,enemies[i].pos.y,10,-5,5,20,30,PARTICLE_BLOOD,false,true);
						player.addKill();
					}

					return;
				}
			}
		}
	}
}