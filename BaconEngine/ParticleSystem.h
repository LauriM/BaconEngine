#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "Precompiled.h"
#include "Vec2.h"

enum PARTICLE_TYPE{
	PARTICLE_CASE,
	PARTICLE_BLOOD,
	PARTICLE_FIRE,
	PARTICLE_DUST,
};

class Particle {
	public:
		int life;
		Vec2<float> pos;
		Vec2<float> velocity;
		bool continuousDraw;
		bool drawOnDead;
		float rot;

		ALLEGRO_BITMAP *img;

		void update();
};

class ParticleSystem {
	private:
		Particle particles[PARTICLE_MAX];
		ALLEGRO_BITMAP *background;//Referenced from the main
		ALLEGRO_DISPLAY *display;//Referenced from the main

		ALLEGRO_BITMAP *particle_case;
		ALLEGRO_BITMAP *particle_blood;
		ALLEGRO_BITMAP *particle_fire;
		ALLEGRO_BITMAP *particle_dust;
	public:
		void init(ALLEGRO_BITMAP *bg,ALLEGRO_DISPLAY *d);
		void addParticle(int x,int y,int count,int speedMin,int speedMax,int lifeTicksMin,int lifeTicksMax,PARTICLE_TYPE type,bool continuousDraw,bool drawOnDead);
		void addParticle(int x,int y,int count,int speedMin,int speedMax,int lifeTicksMin,int lifeTicksMax,PARTICLE_TYPE type,bool continuousDraw,bool drawOnDead,float angle,int spreadMin,int spreadMax);
		void update();
};

#endif