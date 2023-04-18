#pragma once
#include "CScene.h"

class CSound;

class CEvilBossScene :
    public CScene
{
public:
	CEvilBossScene();
	virtual ~CEvilBossScene();

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
