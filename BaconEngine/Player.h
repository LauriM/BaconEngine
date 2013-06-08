#ifndef PLAYER_H
#define PLAYER_H

#include "Precompiled.h"
#include "Vec2.h"

class Player {
	private:
		Vec2<float> target; //Where the mouse is pointing basically
		Vec2<float> position;

		ALLEGRO_BITMAP *player;
	public:
		bool keyShoot;

		bool init();
		void update();
		void render();

		void setMouseXY(int x,int y);
		void setMouseX(int x);
		void setMouseY(int y);

		float getAngle();
};

#endif