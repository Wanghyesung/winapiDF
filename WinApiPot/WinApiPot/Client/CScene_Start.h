#pragma once
#include "CScene.h"

class CSound;

class CScene_Start :
    public CScene
{
public:
    CScene_Start();
    ~CScene_Start();

public:
    virtual void render(HDC _dc);
    virtual void update();

    virtual void Enter();
    virtual void Exit();
    virtual void Init();

    virtual void InitMonster();
private:
    SCENE_TYPE m_eType;

    CSound* m_pBackSound;
};

