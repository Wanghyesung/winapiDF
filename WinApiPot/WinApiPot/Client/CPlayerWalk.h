#pragma once
#include "CPlayerState.h"
class CPlayerWalk :
    public CPlayerState
{
public:
    CPlayerWalk();
    virtual ~CPlayerWalk();
    
private:
    float m_fWalkSpeed;

public:
    virtual void update();
    virtual void Enter();
    virtual void Exit();


};

