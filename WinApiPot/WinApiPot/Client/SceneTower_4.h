#pragma once
#include "CScene.h"
class SceneTower_4 :
    public CScene
{
public:
	SceneTower_4();
	virtual ~SceneTower_4();

public:
	virtual void render(HDC _dc);
	virtual void update();//���⼭ ������Ʈ �ϰ� ������ ������Ʈ���� update, finalupdate

	virtual void Enter();
	virtual void Exit();
	virtual void Init();

private:
	SCENE_TYPE m_eType;

};

