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
	virtual void Enter();//���� �� �� �� 
	virtual void Exit(); //���� �� ���� ��
	virtual void Init(); //�ѹ��� ����

	virtual void update();
	virtual void render(HDC _dc);

};

