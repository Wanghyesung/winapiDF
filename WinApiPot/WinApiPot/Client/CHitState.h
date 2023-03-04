#pragma once
#include "CState.h"
class CHitState :
    public CState
{
private:
    bool m_bHit;
    int m_iHitAnimFrame;
    float m_fCurTime;
    int   m_iLastMotion;

public:
    CHitState();
    virtual ~CHitState();

public:
    void SetAnimFrame(int _iCurFrame) { m_iHitAnimFrame = _iCurFrame; }

public:
    virtual void update();
    virtual void enter();
    virtual void exit();


    
};

