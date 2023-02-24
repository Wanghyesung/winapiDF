#pragma once
#include "CPlayerState.h"
class CPlayerJumpDown :
    public CPlayerState
{
public:
    CPlayerJumpDown();
    virtual ~CPlayerJumpDown();

private:
    virtual void update();
    virtual void Exit();
    virtual void Enter();

};

