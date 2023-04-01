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

public:
	void SetAttackName(const wstring& _strName);

public:
	virtual void enter();
	virtual void exit();
	virtual void update();
};

