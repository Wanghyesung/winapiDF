#pragma once
#include "CScene.h"
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
};

