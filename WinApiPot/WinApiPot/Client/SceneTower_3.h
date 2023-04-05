#pragma once
#include "CScene.h"

class CSound;

class SceneTower_3 :
    public CScene
{
public:
	SceneTower_3();
	virtual ~SceneTower_3();

public:
	virtual void render(HDC _dc);
	virtual void update();//���⼭ ������Ʈ �ϰ� ������ ������Ʈ���� update, finalupdate

	virtual void Enter();
	virtual void Exit();
	virtual void Init();

private:
	SCENE_TYPE m_eType;

	CSound* m_pBackSound;
};

