#pragma once
#include "CPlayerState.h"
class CPlayerAttackDown :
    public CPlayerState
{
public:
    CPlayerAttackDown();
    virtual ~CPlayerAttackDown();

public:
    virtual void update();
    virtual void Exit();
    virtual void Enter();

private:
    float m_fCurTime;
    float m_fAttackTime;

private:
    void InitMulitZeroFrame();
    void Fire(UINT _iFireFrame);

    tAttackFrame m_tAttFrame;

};

