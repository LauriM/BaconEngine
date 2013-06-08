#ifndef VEC2_H
#define VEC2_h

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
};

#endif