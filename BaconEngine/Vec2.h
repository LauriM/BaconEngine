#ifndef VEC2_H
#define VEC2_H

#include <math.h>

template <typename T>
class Vec2{
	public:
		T x;
		T y;

		typedef typename T Type;

		Vec2()
			:x()
			,y()
		{}

		Vec2(Type x, Type y)
			:x(x)
			,y(y)
		{}

		float getRadianToPoint(Vec2<T> target){
			T deltaY = target.y - y;
			T deltaX = target.x - x;

			return atan2(deltaY,deltaX);
		}

		float getDistanceToPoint(Vec2<T> target){
//			return sqrt((dX1 - dX0)*(dX1 - dX0) + (dY1 - dY0)*(dY1 - dY0));
			return sqrt((target.x - x)*(target.x - x) + (target.y - y)*(target.y - y));
		}
};

#endif