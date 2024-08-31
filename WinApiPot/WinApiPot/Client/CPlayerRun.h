#pragma once
#include "CPlayerState.h"
class CPlayerRun :
    public CPlayerState
{
public:
    CPlayerRun();
    virtual ~CPlayerRun();

private:
    int iDirX;
              
    float m_fRunSpeed;

private:
    virtual void update();
    virtual void Enter();
    virtual void Exit();



};

