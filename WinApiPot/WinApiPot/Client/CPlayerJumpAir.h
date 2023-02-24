#pragma once
#include "CPlayerState.h"
class CPlayerJumpAir :
    public CPlayerState
{
public:
    CPlayerJumpAir();
    virtual ~CPlayerJumpAir();

private:
    int m_iDirX;

public:
    virtual void update();
    virtual void Enter();
    virtual void Exit();

};

