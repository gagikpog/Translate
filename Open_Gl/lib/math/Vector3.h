#include <cmath>

#ifndef VECTOR3_H
#define VECTOR3_H
namespace UIGL {
	template <typename T,
		typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
		struct Vector3
	{
		Vector3() {}

		Vector3(T x, T y, T z)
		{
			X = x;
			Y = y;
			Z = z;
		}

		Vector3(const Vector3 &value) = default;
		Vector3(Vector3&& value) = default;
		~Vector3() {}

		Vector3 operator+(const Vector3 &value) const
		{
			return Vector3(X + value.X, Y + value.Y, Z + value.Z);
		}

		Vector3 operator-(const Vector3 &value) const
		{
			return Vector3(X - value.X, Y - value.Y, Z + value.Z);
		}

		Vector3& operator=(const Vector3 &value)
		{
			X = value.X;
			Y = value.Y;
			Z = value.Z;
			return *this;
		}

		Vector3& operator+=(const Vector3 &value)
		{
			X += value.X;
			Y += value.Y;
			Z += value.Z;
			return *this;
		}

		Vector3& operator-=(const Vector3 &value)
		{
			X -= value.X;
			Y -= value.Y;
			Z -= value.Z;
			return *this;
		}

		Vector3 operator/(const float &value) const
		{
			return Vector3(X / value, Y / value, Z / value);
		}

		Vector3 operator*(const float &value) const
		{
			return Vector3(X * value, Y * value, Z * value);
		}

		Vector3& operator/=(const float &value)
		{
			X /= value;
			Y /= value;
			Z /= value;
			return *this;
		}

		Vector3& operator*=(const float &value)
		{
			X *= value;
			Y *= value;
			Z *= value;
			return *this;
		}
		//Векторное произведение
		Vector3 operator*(const Vector3 &value) const
		{
			Vector3 _tmp;
			_tmp.X = Y * value.Z - Z * value.Y;
			_tmp.Y = -X * value.Z + Z * value.X;
			_tmp.Z = X * value.Y - Y * value.X;
			return _tmp;
		}
		//scalar multiplication of vectors
		T ScalarMultiplication(const Vector3 &value) const
		{
			return X*value.X + Y*value.Y + Z*value.Z;
		}

		T GetLength() const
		{
			return std::sqrt(X * X + Y * Y + Z * Z);
		}

		friend std::ostream &operator<<(std::ostream &_out, const Vector3 &b)
		{
			_out << "X = " << b.X << ", Y = " << b.Y << ", Z = " << b.Z;
			return _out;
		}

		T X = 0;
		T Y = 0;
		T Z = 0;
	};
}
#endif