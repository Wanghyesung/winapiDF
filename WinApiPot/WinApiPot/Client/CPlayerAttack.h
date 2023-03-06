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

public:
    void InitMulitZeroFrame();

private:
    void Fire(UINT _iFireFrame);

    tAttackFrame m_tAttFrame;
    static UINT m_iCurAttFrame;
    static UINT  m_iKeyCount;
private:
    float m_fCurTime;
    float m_fAttackTime;

    
    vector<UINT> m_vecAttMotion;

    friend class CPlayerAttackDown;
};

