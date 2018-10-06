#include "../include.h"

#include "Vector.h"

namespace GameEngine
{
	Vector2::Vector2()
	{
	}

	Vector2::Vector2(const float & x, const float & y)
	{
		this->x = x;
		this->y = y;
	}

	Vector3::Vector3()
	{

	}

	Vector3::Vector3(const float &x, const float&y, const float& z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vector4::Vector4()
	{

	}

	Vector4::Vector4(const float& x, const float& y, const float& z, const float& w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}
}
