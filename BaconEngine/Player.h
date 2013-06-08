#ifndef PLAYER_H
#define PLAYER_H

#include "Precompiled.h"
#include "Vec2.h"

class Player {
	private:
		Vec2<float> target; //Where the mouse is pointing basically

		ALLEGRO_BITMAP *player;

	public:
		bool init();
		void update();
		void render();

		Vec2<float> position;

		void setMouseXY(int x,int y);
		void setMouseX(int x);
		void setMouseY(int y);

		float getAngle();
};

#endif