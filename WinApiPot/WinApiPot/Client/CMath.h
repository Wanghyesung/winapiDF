#pragma once

// vec2(cos, sin) * vec2(-sin, cos)
inline static Vec2 Rotate(Vec2 _vVec, float _fDegree)
{
	float fRadian = (_fDegree / 180.f) * PI;
	_vVec.NormalRize();

	float x	= _vVec.x* cosf(fRadian) - _vVec.x * sinf(fRadian);
	float y = _vVec.y * sinf(fRadian) + _vVec.y * cosf(fRadian);

	return Vec2(x, y);
}

