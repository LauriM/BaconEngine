#ifndef VEC2_H
#define VEC2_h

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
};

#endif