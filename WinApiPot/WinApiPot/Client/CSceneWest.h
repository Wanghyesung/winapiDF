#pragma once
#include "CScene.h"
class CSceneWest :
    public CScene
{
public:
	CSceneWest();
	virtual ~CSceneWest();


public:
	virtual void render(HDC _dc);
	virtual void update();//���⼭ ������Ʈ �ϰ� ������ ������Ʈ���� update, finalupdate

	virtual void Enter();
	virtual void Exit();
	virtual void Init();

private:
	SCENE_TYPE m_eType;

};

