#pragma once

namespace GameEngine
{
	class Vector2
	{
	public:
		/*
			�R���X�g���N�^
		*/
		Vector2();
		Vector2(const float &x, const float &y);

		/*
			�f�X�g���N�^
		*/
		~Vector2() {};

		/*
			�l�ݒ�
		*/
		Vector2& Set(const Vector2& v)
		{
			Vector2 ret;

			ret.x = v.x;
			ret.y = v.y;

			return ret;
		}

		Vector2 operator = (Vector2& v)
		{
			this->x = v.x;
			this->y = v.y;
		}

		float x = 0.f;
		float y = 0.f;
	};

	class Vector3
	{
	public:
		/*
			�R���X�g���N�^
		*/
		Vector3();
		Vector3(const float &x, const float &y, const float &z);

		/*
			�f�X�g���N�^
		*/
		~Vector3() {};

		/*
			�l�ݒ�
		*/
		Vector3& Set(const Vector3& v)
		{
			Vector3 ret;

			ret.x = v.x;
			ret.y = v.y;
			ret.z = v.z;

			return ret;
		}

		Vector3 operator = (Vector3& v)
		{
			this->x = v.x;
			this->y = v.y;
			this->z = v.z;
		}

		float x = 0.f;
		float y = 0.f;
		float z = 0.f;
	};

	class Vector4
	{
	public:
		/*
			�R���X�g���N�^
		*/
		Vector4();
		Vector4(const float& x, const float& y, const float& z, const float& w);

		/*
			�f�X�g���N�^
		*/
		~Vector4() {};

		/*
			�l�ݒ�
		*/
		Vector4& Set(const Vector4& v)
		{
			Vector4 ret;

			ret.x = v.x;
			ret.y = v.y;
			ret.z = v.z;
			ret.w = v.w;

			return ret;
		}

		Vector4 operator = (Vector4 v)
		{
			this->x = v.x;
			this->y = v.y;
			this->z = v.z;
			this->w = v.w;
		}

		float x = 0.f;
		float y = 0.f;
		float z = 0.f;
		float w = 0.f;
	};
}
