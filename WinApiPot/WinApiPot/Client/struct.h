#pragma once

struct Vec2
{
	//좌표와 위치의 계념으로 사용
	float x;
	float y;

	Vec2() :
		x(0.f),
		y(0.f)
	{}

	Vec2(float _x, float _y):
		x(_x),
		y(_y)
	{}

	Vec2(int _x, int _y) :
		x((float)_x),
		y((float)_y)
	{}

	Vec2(const POINT _pt) :
		x((float)_pt.x),
		y((float)_pt.y)
	{}

	Vec2 operator +(Vec2 _v)
	{
		return (Vec2(x + _v.x, y + _v.y));
	}

	Vec2 operator *(Vec2 _v)
	{
		return (Vec2(x * _v.x, y * _v.y));
	}


	Vec2 operator *(float _f)
	{
		return (Vec2(x * _f, y * _f));
	}

	Vec2 operator /(float _f)
	{
		return (Vec2(x / _f, y / _f));
	}

	void operator +=(Vec2 _v)
	{
		x += _v.x;
		y += _v.y;
	}

	Vec2 operator - (Vec2 _v)
	{
		return (Vec2(x - _v.x, y - _v.y));
	}

	void operator -= (Vec2 _v)
	{
		x -= _v.x;
		y -= _v.y;
	}

	void operator +=(float _f)
	{
		x += _f; 
		y += _f;
	}

	Vec2 operator -()
	{
		return Vec2(-x, -y);
	}

	bool operator ==(Vec2 _v)
	{
		return((int)_v.x == (int)x && (int)_v.y == (int)y);
	}

	Vec2& NormalRize()
	{
		float fLen = Length();

		assert(fLen != 0.f);

		x /= fLen;
		y /= fLen;

		return *this;
	}

	float Length()
	{
		return sqrt(x * x + y * y);
	}

	bool IsZero()
	{
		if (x == 0.f && y == 0.f)
			return true;

		return false;
	}

};



