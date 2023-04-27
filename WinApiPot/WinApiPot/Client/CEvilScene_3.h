#pragma once
#include "CScene.h"
class CEvilScene_3 :
    public CScene
{
public:
    CEvilScene_3();
    virtual ~CEvilScene_3();

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

