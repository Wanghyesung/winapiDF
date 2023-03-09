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

    vector<UINT> m_vecAttMotion;
public:
    void InitMulitZeroFrame();

private:
    void Fire(UINT _iFireFrame);


};

