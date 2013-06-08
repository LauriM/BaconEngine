#ifndef PLAYER_H
#define PLAYER_H

#include "Precompiled.h"
#include "Vec2.h"

class Player {
	private:
		Vec2<float> target; //Where the mouse is pointing basically
		Vec2<float> position;

		ALLEGRO_BITMAP *player;

		int loadTicks; //How many ticks before next round
		int ammo;
		int hp;
	public:
		bool keyShoot;
		bool keyUp;
		bool keyDown;
		bool keyLeft;
		bool keyRight;

		bool init();
		void update();
		void render();

		void setMouseXY(int x,int y);
		void setMouseX(int x);
		void setMouseY(int y);

		float getAngle();

		Vec2<float> getPosition();
};

#endif