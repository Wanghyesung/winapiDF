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

    wstring m_strAttackName;
public:
    void SetAttackFrame(UINT _i) { m_iAttackFrame = _i; }

    //monster update_state���� �ִϸ��̼� ������ �� �ٸ� ���ݸ�ǵ� �����ϱ� ���ؼ�
    void SetAttackName(const wstring& _strName) { m_strAttackName = _strName; }
    const wstring& GetAttackName() { return m_strAttackName; }

public:
    virtual void enter();
    virtual void exit();
    virtual void update();


};

