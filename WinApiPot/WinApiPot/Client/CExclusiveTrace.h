#pragma once
#include "CState.h"

class CPlayer;

class CExclusiveTrace :
    public CState
{
public:
    CExclusiveTrace();
    virtual  ~CExclusiveTrace();

private:
    CPlayer* m_pTarget;//Å¸°Ù

    MONSTER_STATE m_eNextState;

    float m_fCurAttackTime;



public:
    virtual void update();
    virtual void exit();
    virtual void enter();
};

