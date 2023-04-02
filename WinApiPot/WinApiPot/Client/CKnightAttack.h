#pragma once
#include "CState.h"
class CKnightAttack :
    public CState
{
public:
	CKnightAttack();
	virtual ~CKnightAttack();

private:
	wstring m_strAttackName;
	tKnight_Attack m_tNightAttackInfo;

	UINT m_iAttackCount;

public:
	void SetAttackName(const wstring& _strName);
	const wstring& GetAttackName() { return m_strAttackName; }


public:
	virtual void enter();
	virtual void exit();
	virtual void update();
};

