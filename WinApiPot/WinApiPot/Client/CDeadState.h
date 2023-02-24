#pragma once
#include "CState.h"
class CDeadState :
    public CState
{
private:
    int m_iCurFrame;

public:
    CDeadState();
    virtual ~CDeadState();

public:
    void SetAnimFrame(int _iFrame) { m_iCurFrame = _iFrame; }

public:
    virtual void update();
    virtual void enter();
    virtual void exit();

};

