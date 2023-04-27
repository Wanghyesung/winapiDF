#pragma once
#include "CScene.h"

class CSound;

class SceneTower_2 :
    public CScene
{
public:
	SceneTower_2();
	virtual ~SceneTower_2();

public:
	virtual void render(HDC _dc);
	virtual void update();//���⼭ ������Ʈ �ϰ� ������ ������Ʈ���� update, finalupdate

	virtual void Enter();
	virtual void Exit();
	virtual void Init();

	virtual void InitMonster();

private:
	SCENE_TYPE m_eType;

	CSound* m_pBackSound;
};

