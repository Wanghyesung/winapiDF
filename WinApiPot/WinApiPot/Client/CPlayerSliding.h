#pragma once
#include "CPlayerState.h"
class CPlayerSliding :
    public CPlayerState
{
public:
    CPlayerSliding();
    virtual ~CPlayerSliding();

public:
    virtual void update();
    virtual void Exit();
    virtual void Enter();

private:
    bool m_bSliding;

};

