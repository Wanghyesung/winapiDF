#pragma once

class CMonster;

enum class MON_TYPE
{
	NORMAL,
	RANGE,
	DRAGON,
	BLUE_DRAGON,
};


class CMonFactory
{
public:
	static CMonster* CraeteMonster(MON_TYPE _monType, Vec2 _vPos, SCENE_TYPE _eSceneType);


private:
	//°´Ã¼ ¼û±è
	CMonFactory();
	~CMonFactory();
};

