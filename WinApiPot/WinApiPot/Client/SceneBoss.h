#pragma once
#include "CScene.h"
class SceneBoss :
    public CScene
{
public:
	SceneBoss();
	virtual ~SceneBoss();

public:
	virtual void render(HDC _dc);
	virtual void update();//���⼭ ������Ʈ �ϰ� ������ ������Ʈ���� update, finalupdate

	virtual void Enter();
	virtual void Exit();
	virtual void Init();

private:
	SCENE_TYPE m_eType;

};

