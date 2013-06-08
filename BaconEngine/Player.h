#ifndef PLAYER_H
#define PLAYER_H

#include "Vec2.h"

class Player {
	private:
		Vec2<float> position;

		ALLEGRO_BITMAP *player;

	public:
		bool init();
		void update();
		void render();
};

#endif