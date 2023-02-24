#pragma once
#include "CState.h"

class CPlayer;

class CIdleState :
    public CState
{
public:
    CIdleState();
    virtual ~CIdleState();

private:
    float m_fNavigationScope; //찾을 거리
    float m_fTtime;//지정 시간이 지나면 탐색 
    float m_fCurTime;//현재 시간
    CPlayer* m_pTarget;//타겟

    MONSTER_STATE m_eNextState;

public:
    virtual void update();
    virtual void enter();
    virtual void exit();

    void SetNavigationScope(float _f) { m_fNavigationScope = _f; }

};

