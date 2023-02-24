#pragma once
#include "CPlayerState.h"
class CPlayerIdle :
    public CPlayerState
{
public:
    CPlayerIdle();
    virtual ~CPlayerIdle();

private:
   
public:
    virtual void update();
    virtual void Enter();
    virtual void Exit();


};

