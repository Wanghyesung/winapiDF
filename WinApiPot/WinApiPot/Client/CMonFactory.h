#pragma once

class CMonster;

enum class MON_TYPE
{
	NORMAL,
	RANGE,
	DRAGON,
};


class CMonFactory
{
public:
	static CMonster* CraeteMonster(MON_TYPE _monType, Vec2 _vPos);


private:
	//°´Ã¼ ¼û±è
	CMonFactory();
	~CMonFactory();
};

