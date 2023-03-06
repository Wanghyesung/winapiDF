#pragma once
#include "CState.h"

class CAttackState :
    public CState
{
private:
    UINT m_iAttCount;
    UINT m_iAttackFrame;
    wstring m_strAttackName;

public:
    CAttackState();
    virtual ~CAttackState();

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

