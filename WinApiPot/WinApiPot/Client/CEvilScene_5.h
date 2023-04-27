#pragma once
#include "CScene.h"

class CSound;

class CEvilScene_5 :
    public CScene
{
public:
    CEvilScene_5();
    virtual ~CEvilScene_5();

private:
    SCENE_TYPE m_eType;

    CSound* m_pBackSound;
public:
    virtual void render(HDC _dc);
    virtual void update();

public:
    virtual void Enter();
    virtual void Exit();
    virtual void Init();

    virtual void InitMonster();
};


