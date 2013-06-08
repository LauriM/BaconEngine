#include "EnemySystem.h"

void Enemy::update(Vec2<float> target){
	//Render
	al_draw_rotated_bitmap(img ,16 ,16 ,pos.x ,pos.y , pos.getRadianToPoint(target) ,0);
}

void EnemySystem::init(){
	enemy = al_load_bitmap("enemy.png");
	al_convert_mask_to_alpha(enemy,al_map_rgb(255,0,255));

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

					enemies[i].pos.x = randomRange(0,1000);
					enemies[i].pos.y = randomRange(0,1000);
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


void calculateShot(Vec2<float> from,Vec2<float> to){

}