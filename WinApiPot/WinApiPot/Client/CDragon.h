#pragma once
#include "CMonster.h"


class CDragon :
	public CMonster
{
private:
	MONSTER_STATE m_tMonState;

public:
	CDragon();
	virtual ~CDragon();

private:
	void update_state();

public:
	virtual void update();
	virtual void render(HDC _dc);
	virtual void Hit(CCollider* _pOther, const tAttackInfo& _tAtt); 

public:
	virtual void OnColliderEnter(CCollider* _pOther);
	virtual void OnColliderExit(CCollider* _pOther);
	virtual void OnCollision(CCollider* _pOther);
};

