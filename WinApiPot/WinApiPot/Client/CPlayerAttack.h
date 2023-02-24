#pragma once
#include "CPlayerState.h"

#include "CPlayerAttackDown.h"

class CPlayerAttack :
    public CPlayerState
{
public:
    CPlayerAttack();
    virtual ~CPlayerAttack();

public:
    virtual void update();
    virtual void Exit();
    virtual void Enter();

private:
    void InitMulitZeroFrame();
    void Fire(UINT _iFireFrame);

    tAttackFrame m_tAttFrame;
    static UINT m_iCurAttFrame;

private:
    float m_fCurTime;
    float m_fAttackTime;

    friend class CPlayerAttackDown;
};

