#pragma once
#include "CState.h"

class CAttackState :
    public CState
{
private:
    UINT m_iAttCount;
    UINT m_iAttackFrame;

public:
    CAttackState();
    virtual ~CAttackState();

public:
    void SetAttackFrame(UINT _i) { m_iAttackFrame = _i; }

public:
    virtual void enter();
    virtual void exit();
    virtual void update();
};

