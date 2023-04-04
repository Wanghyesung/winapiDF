#pragma once
#include "CScene.h"

class CSound;

class CSceneLog :
    public CScene
{
public:
	CSceneLog();
	virtual ~CSceneLog();

private:
	SCENE_TYPE m_eType;

	CSound* pBackSound;

public:
	virtual void Enter();//현재 씬 들어갈 때 
	virtual void Exit(); //현재 씬 나갈 떄
	virtual void Init(); //한번만 실행

	virtual void update();
	virtual void render(HDC _dc);

};

