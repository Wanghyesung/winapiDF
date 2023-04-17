#pragma once
#include "CScene.h"

class CSound;

class CEvilScene_1 :
    public CScene
{
public:
    CEvilScene_1();
    virtual ~CEvilScene_1();

private:
    SCENE_TYPE m_eType;

    CSound* m_pBackSound;
public:
    virtual void render(HDC _dc);

public:
    virtual void Enter();
    virtual void Exit();
    virtual void Init();



};

