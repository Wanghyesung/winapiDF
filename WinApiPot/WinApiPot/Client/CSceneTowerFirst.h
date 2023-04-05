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
	virtual void update();//여기서 업데이트 하고 각각의 오브젝트에서 update, finalupdate

	virtual void Enter();
	virtual void Exit();
	virtual void Init();

private:
	SCENE_TYPE m_eType;

	CSound* m_pBackSound;


};

