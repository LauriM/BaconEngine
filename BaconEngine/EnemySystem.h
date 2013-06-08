#ifndef ENEMYSYSTEM_H
#define ENEMYSYSTEM_H

#include "Precompiled.h"

class Enemy {
	public:
		ALLEGRO_BITMAP *img;
		Vec2<float> pos;
		int hp;

		void update(Vec2<float> target);
};

class EnemySystem {
	private:
		ALLEGRO_BITMAP *enemy;
		Enemy enemies[ENEMY_MAX];

		int ticksToSpawn;
		int spawnSize;

	public:
		void init();
		void update(Vec2<float> target); //Target is the position of the player

		void calculateShot(Vec2<float> from,Vec2<float> to);
};

#endif