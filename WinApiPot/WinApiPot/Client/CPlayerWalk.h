#pragma once
#include "CPlayerState.h"
class CPlayerWalk :
    public CPlayerState
{
public:
    CPlayerWalk();
    virtual ~CPlayerWalk();
    
private:


public:
    virtual void update();
    virtual void Enter();
    virtual void Exit();


};

