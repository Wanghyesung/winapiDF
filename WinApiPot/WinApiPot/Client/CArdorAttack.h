#pragma once
#include "CState.h"
#include "CMonster.h"

class CArdorAttack :
    public CState
{
public:
	CArdorAttack();
	virtual ~CArdorAttack();

private:
	wstring m_strAttackName;
	tNew_Attack m_tNightAttackInfo;

	UINT m_iAttackCount;

public:
	void SetAttackName(const wstring& _strName);
	const wstring& GetAttackName() { return m_strAttackName; }


public:
	virtual void enter();
	virtual void exit();
	virtual void update();

};

