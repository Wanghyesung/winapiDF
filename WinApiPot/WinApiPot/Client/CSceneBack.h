#pragma once

#include "CScene.h"

class CSceneBack :
    public CScene
{
public:
	CSceneBack();
	virtual ~CSceneBack();


public:
	virtual void render(HDC _dc);
	virtual void update();//���⼭ ������Ʈ �ϰ� ������ ������Ʈ���� update, finalupdate

	virtual void Enter(); 
	virtual void Exit();
	virtual void Init();

private:
	SCENE_TYPE m_eType;


};

