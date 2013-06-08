#include "Precompiled.h"
#include "ParticleSystem.h"

ParticleSystem particleSystem;

void ParticleSystem::init(ALLEGRO_BITMAP *bg,ALLEGRO_DISPLAY *d){
	background = bg; //Reference from the main
	display    = d; //Reference from the main

	for(int i = 0;i < PARTICLE_MAX;++i){
		particles[i].life = 0;//Make sure all the particle slots are "dead"
	}

	//Lets just hope loading these works...
	particle_case = al_load_bitmap("case.png");
	particle_blood = al_load_bitmap("blood.png");
	particle_fire = al_load_bitmap("fire.png");
	particle_dust = al_load_bitmap("dust.png");
}

void ParticleSystem::addParticle(int x,int y,int count,int speedMin,int speedMax,int lifeTicksMin,int lifeTicksMax,PARTICLE_TYPE type,bool continuousDraw,bool drawOnDead){
	addParticle(x,y,count,speedMin,speedMax,lifeTicksMin,lifeTicksMax,type,continuousDraw,drawOnDead,0.f,0,0);
}

void ParticleSystem::addParticle(int x,int y,int count,int speedMin,int speedMax,int lifeTicksMin,int lifeTicksMax,PARTICLE_TYPE type,bool continuousDraw,bool drawOnDead,float angle,int spreadMin, int spreadMax){
	int added = 0;

	while(added < count){
		for(int i = 0;i < PARTICLE_MAX;++i){
			if(particles[i].life < 1){
				//Found empty particle slot! lets fill it
				particles[i].life = randomRange(lifeTicksMin,lifeTicksMax);
				particles[i].pos.x = x;
				particles[i].pos.y = y;
				
				//Add way to force direction
				
				//If particle doesn't have direction, give random direction
				if(angle == 0){
					particles[i].velocity.x = randomRange(speedMin,speedMax);
					particles[i].velocity.y = randomRange(speedMin,speedMax);
				}else{
					//The particle is directed into a direction!
					int speed = randomRange(speedMin,speedMax);

					float finalAngle = (PI*(angle + randomRange(spreadMin,spreadMax) )/180);

					particles[i].velocity.x = cos(finalAngle) * speed;
					particles[i].velocity.y = sin(finalAngle) * speed;
				}

				particles[i].continuousDraw = continuousDraw;
				particles[i].rot = 0.0;
				particles[i].drawOnDead = drawOnDead;

				//Link the correct image
				switch(type){
					case PARTICLE_CASE:
						particles[i].img = particle_case;
						break;
					case PARTICLE_BLOOD:
						particles[i].img = particle_blood;
						break;
					case PARTICLE_DUST:
						particles[i].img = particle_dust;
						break;
					case PARTICLE_FIRE:
						particles[i].img = particle_fire;
						break;
				}

				++added;
				break;
			}

			if(i == PARTICLE_MAX){
				printf("PARTICLE_MAX TOO LOW!\n");
				break;
			}

		}
	}
}

void ParticleSystem::update(){
	for(int i = 0;i < PARTICLE_MAX;++i){
		if(particles[i].life > 0){
			if(particles[i].continuousDraw){
				al_set_target_bitmap(background);
			}else{
				al_set_target_backbuffer(display);
			}

			particles[i].update();

			al_set_target_backbuffer(display);

			if(particles[i].life < 1){
				if(particles[i].drawOnDead){
					//it died! -> render the end mark
					al_set_target_bitmap(background);
					particles[i].update();
					al_set_target_backbuffer(display);
				}
			}
		}
	}
}

void Particle::update(){
	--life;

	pos.x += velocity.x;
	pos.y += velocity.y;

	rot = rot + 0.3;

	//Render also happens here
	al_draw_rotated_bitmap(img ,1 ,1 ,pos.x,pos.y,rot,0);
}