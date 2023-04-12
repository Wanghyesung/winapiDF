#pragma once

class CMonster;

enum class MON_TYPE
{
	NORMAL,
	RANGE,
	LORD,
	DRAGON,
	KNIGHT_RED,
	KNIGHT_BROWN,
	KNIGHT_GREEN,
	BLUE_DRAGON,
	BROWN_DRAGON,
	NAIAS,
	FIRE_MONSTER,
	EVL,
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

