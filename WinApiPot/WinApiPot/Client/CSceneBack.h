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
	virtual void update();//여기서 업데이트 하고 각각의 오브젝트에서 update, finalupdate

	virtual void Enter(); 
	virtual void Exit();
	virtual void Init();

private:
	SCENE_TYPE m_eType;


};

