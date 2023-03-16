#pragma once
#include "CState.h"
class CUltimateState :
    public CState
{
public:
    CUltimateState();
    virtual ~CUltimateState();

private:
    float m_fRespawnTime;
    float m_fCurTime;

private:
    virtual void enter();
    virtual void exit();
    virtual void update();




};

