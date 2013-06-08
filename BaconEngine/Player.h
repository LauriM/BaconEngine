#ifndef PLAYER_H
#define PLAYER_H

#include "Vec2.h"

class Player {
	private:
		Vec2<float> position;
		Vec2<float> target; //Where the mouse is pointing basically

		ALLEGRO_BITMAP *player;

	public:
		bool init();
		void update();
		void render();

		void setMouseXY(int x,int y);
		void setMouseX(int x);
		void setMouseY(int y);
};

#endif