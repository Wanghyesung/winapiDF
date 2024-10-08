#pragma once
#include "CScene.h"

class CSound;

class SceneTower_4 :
    public CScene
{
public:
	SceneTower_4();
	virtual ~SceneTower_4();

public:
	virtual void render(HDC _dc);
	virtual void update();//여기서 업데이트 하고 각각의 오브젝트에서 update, finalupdate

	virtual void Enter();
	virtual void Exit();
	virtual void Init();

	virtual void InitMonster();

private:
	SCENE_TYPE m_eType;

	CSound* m_pBackSound;

};

