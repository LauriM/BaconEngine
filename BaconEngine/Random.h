#ifndef RANDOM_H
#define RANDOM_H

#include 

int randomRange(int min,int max){
	return min + (rand() % (int)(max - min + 1));
}

#endif