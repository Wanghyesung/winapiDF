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
    UINT m_iEndAttackFrame;

    wstring m_strAttackName;
public:
    void SetAttackFrame(UINT _iAttack, UINT _iEnd) { m_iAttackFrame = _iAttack; m_iEndAttackFrame = _iEnd; }

    //monster update_state에서 애니메이션 움직일 때 다른 공격모션들 구분하기 위해서
    void SetAttackName(const wstring& _strName) { m_strAttackName = _strName; }
    const wstring& GetAttackName() { return m_strAttackName; }


public:
    virtual void enter();
    virtual void exit();
    virtual void update();


};

