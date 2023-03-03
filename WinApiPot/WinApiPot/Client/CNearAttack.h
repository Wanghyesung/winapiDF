#pragma once
#include "CState.h"
class CNearAttack :
    public CState
{
public:
    CNearAttack();
    virtual ~CNearAttack();

private:
    int m_iAttackCount;
    UINT m_iAttackFrame;

public:
    void SetAttackFrame(UINT _i) { m_iAttackFrame = _i; }

public:
    virtual void enter();
    virtual void exit();
    virtual void update();


};

