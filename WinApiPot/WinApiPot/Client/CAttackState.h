#pragma once
#include "CState.h"

class CAttackState :
    public CState
{
private:
    bool m_bAttacking;
    int m_iDir;
    UINT m_iAttCount;
    vector<int> m_vAttackFrame;

public:
    CAttackState();
    virtual ~CAttackState();

public:
    void SetDir(int _iDir) { m_iDir = _iDir; }

    void AddAttackFrame(int _iAttackFrame)
    {
        m_vAttackFrame.push_back(_iAttackFrame);
    }

public:
    virtual void enter();
    virtual void exit();
    virtual void update();
};

