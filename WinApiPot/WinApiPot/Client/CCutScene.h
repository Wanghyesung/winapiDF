#pragma once
#include "CScene.h"

class CSound;

class CCutScene :
    public CScene
{
public:
    CCutScene();
    virtual ~CCutScene();
private:
    SCENE_TYPE m_eType;

    CSound* pBackSound;
public:
    virtual void render(HDC _dc);

public:
    virtual void Enter();
    virtual void Exit();
    virtual void Init();




};

