#pragma once
#include "CState.h"
class CStandOffAttack :
    public CState
{
public:
	CStandOffAttack();
	virtual ~CStandOffAttack();

private:
    int m_iAttackCount;
    UINT m_iAttackFrame;
    UINT m_iEndAttackFrame;
    wstring m_strAttackName;

public:
	virtual void enter();
	virtual void exit();
	virtual void update();


public:
    void SetAttackFrame(UINT _iAttack, UINT _iEnd) { m_iAttackFrame = _iAttack; m_iEndAttackFrame = _iEnd; }

    //monster update_state���� �ִϸ��̼� ������ �� �ٸ� ���ݸ�ǵ� �����ϱ� ���ؼ�
    void SetAttackName(const wstring& _strName) { m_strAttackName = _strName; }
    const wstring& GetAttackName() { return m_strAttackName; }


};
