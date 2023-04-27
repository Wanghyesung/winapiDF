#pragma once
#include "CScene.h"
class CSound;

class CEvilScene_2 :
    public CScene
{
public:
    CEvilScene_2();
    virtual ~CEvilScene_2();

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

