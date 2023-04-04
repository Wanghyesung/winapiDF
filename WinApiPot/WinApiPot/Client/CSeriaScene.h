#pragma once
#include "CScene.h"

class CSound;

class CSeriaScene :
    public CScene
{
public:
	CSeriaScene();
	virtual ~CSeriaScene();

public:
	virtual void render(HDC _dc);


public:
	virtual void Enter();
	virtual void Exit();
	virtual void Init();

private:
	SCENE_TYPE m_eType;

	CSound* m_pBackSound;
};

