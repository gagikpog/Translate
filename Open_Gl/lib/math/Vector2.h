#ifndef VECTOR2_H
#define VECTOR2_H

#include <cmath>
#include <ostream>

namespace UIGL {

	template <typename T,
		typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
		struct Vector2
	{
		Vector2() {}

		Vector2(T x, T y)
		{
			X = x;
			Y = y;
		}

		Vector2(const Vector2& value) = default;
		Vector2(Vector2&& value) = default;
		~Vector2() {}

		Vector2 operator+(const Vector2 &value) const
		{
			return Vector2(X + value.X, Y + value.Y);
		}

		Vector2 operator-(const Vector2 &value) const
		{
			return Vector2(X - value.X, Y - value.Y);
		}

		Vector2 &operator=(const Vector2 &value)
		{
			X = value.X;
			Y = value.Y;
			return *this;
		}

		Vector2 &operator+=(const Vector2 &value)
		{
			X += value.X;
			Y += value.Y;
			return *this;
		}

		Vector2 &operator-=(const Vector2 &value)
		{
			X -= value.X;
			Y -= value.Y;
			return *this;
		}
		//scalar multiplication of vectors
		T operator*(const Vector2 &value) const
		{
			T res;
			res = value.X * X;
			res += value.Y * Y;
			return res;
		}

		Vector2& operator*(const T value) const
		{
			Vector2 res;
			res.X = X * value;
			res.Y = Y * value;
			return res;
		}

		Vector2 &operator*=(const T value)
		{
			X *= value;
			Y *= value;
			return *this;
		}

		Vector2& operator/(const T value) const
		{
			Vector2 res;
			res.X = X / value;
			res.Y = Y / value;
			return res;
		}

		Vector2 &operator/=(const T value)
		{
			X /= value;
			Y /= value;
			return *this;
		}

		float Length() const
		{
			return std::sqrt(X * X + Y * Y);
		}

		Vector2 getBasis()
		{
			T _length = Length();
			if (_length > 0)
				return Vector2<T>(X / _length, Y / _length);
			return Vector2<T>();
		}

		Vector2	getLeftOrthogonality()
		{	/*		x y 0
					0 0 -1
					i j k
			*/
			return Vector2<T>(-Y, X);
		}

		Vector2	getRightOrthogonality()
		{	/*		x y 0
					0 0 1
					i j k
			*/
			return Vector2<T>(Y, -X);
		}

		bool operator==(const Vector2 &operator2) const
		{
			return (X == operator2.X && Y == operator2.Y);
		}

		friend std::ostream &operator<<(std::ostream &_out, const Vector2 &b)
		{
			return _out << "X = " << b.X << ", Y = " << b.Y;
		}

		T X = 0;
		T Y = 0;
	};

	typedef UIGL::Vector2<float> Vector2f;
}
#endif