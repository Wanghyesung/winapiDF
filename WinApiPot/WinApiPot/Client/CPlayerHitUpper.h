#pragma once
#include "CPlayerState.h"
class CPlayerHitUpper :
    public CPlayerState
{
public:
    CPlayerHitUpper();
    virtual ~CPlayerHitUpper();

private:
    float m_fCurTime;

    float m_fDonwTime;

public:
    virtual void Exit();
    virtual void Enter();
    virtual void update();




};

