#pragma once
#include "CState.h"
#include "CMonster.h"

class CPlayer;

class CTraceState :
    public CState
{
public:
    CTraceState();
    virtual  ~CTraceState();

private:
    CPlayer* m_pTarget;//Å¸°Ù
    MONSTER_STATE m_eNextState;

    void init_attack(UINT _iDir);

public:
    virtual void update();
    virtual void exit();
    virtual void enter();
};

