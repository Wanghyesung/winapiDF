#pragma once
#include "CScene.h"

class CSound;

class CSceneTowerFirst :
    public CScene
{
public:
    CSceneTowerFirst();
    virtual ~CSceneTowerFirst();

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

