#pragma once
#include "CState.h"
#include "CEvileye.h"

class CEvileyeAttack :
    public CState
{
public:
	CEvileyeAttack();
	virtual ~CEvileyeAttack();

private:
	EVILSKILL m_eCurSkill;

	UINT m_iAttackCount;
public:
	virtual void enter();
	virtual void exit();
	virtual void update();

public:
	void setSkill(UINT _eSkillNum) { m_eCurSkill = (EVILSKILL)m_eCurSkill; }
	void start_skill();
	

};

