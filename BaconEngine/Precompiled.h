#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <time.h>



#ifndef PRECOMPILED_H
#define PRECOMPILED_H
const float FPS = 60;

int randomRange(int min,int max);

#include "ParticleSystem.h"
#include "EnemySystem.h"

extern ParticleSystem particleSystem;
extern EnemySystem enemySystem;

#endif


#define PI 3.14159265359

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 900

#define PARTICLE_MAX 150
#define ENEMY_MAX 25

#define PLAYER_SPEED 3
#define ENEMY_SPEED 4