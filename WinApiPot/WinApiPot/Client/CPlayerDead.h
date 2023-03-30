#pragma once
#include "CPlayerState.h"
class CPlayerDead :
    public CPlayerState
{

public:
    CPlayerDead();
    virtual ~CPlayerDead();


public:
    virtual void update();
    virtual void Enter();
    virtual void Exit();
};

