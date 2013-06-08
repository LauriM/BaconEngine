#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <time.h>



#ifndef PRECOMPILED_H
#define PRECOMPILED_H
const float FPS = 60;

int randomRange(int min,int max);

#include "ParticleSystem.h"

extern ParticleSystem particleSystem;

#endif


#define PI 3.14159265359

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 900

#define PARTICLE_MAX 150

#define PLAYER_SPEED 3