#pragma once
#include "CPlayerState.h"


class CPlayerJumpAttack :
    public CPlayerState
{
public:
    CPlayerJumpAttack();
    virtual ~CPlayerJumpAttack();

private:
    virtual void update();
    virtual void Enter();
    virtual void Exit();

private:
    float m_fCurTime;
    float m_fAttackTime;

private:
    void Fire(UINT _iFireFrame);

    UINT         m_iCurAttFrame;



};

