#pragma once
#include "CPlayerState.h"
class CPlayerJump :
    public CPlayerState
{
public:
    CPlayerJump();
    virtual ~CPlayerJump();

private:
    virtual void update();
    virtual void Enter();
    virtual void Exit();


};

