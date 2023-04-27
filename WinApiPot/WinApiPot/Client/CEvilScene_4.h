#pragma once
#include "CScene.h"

class CSound;

class CEvilScene_4 :
    public CScene
{
public:
    CEvilScene_4();
    virtual ~CEvilScene_4();

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

