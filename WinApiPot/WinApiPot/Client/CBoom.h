#pragma once
#include "CObject.h"
class CBoom :
    public CObject
{
public:
	CBoom();
	virtual ~CBoom();

private:
	tAttackInfo m_tAtt;

	unordered_map<UINT,UINT> m_hashTargetCollId;

	bool m_bAttackOn;



public:
	virtual void render(HDC _dc);
	virtual void update();//»ó¼Ó
	virtual void finalupdate();

public:
	virtual void OnColliderEnter(CCollider* _pOther);
	virtual void OnColliderExit(CCollider* _pOther);
	virtual void OnCollision(CCollider* _pOther);

public:
	const tAttackInfo& GetAttInfo() { return m_tAtt; }
	void SetAttackInfo(const tAttackInfo _tAtt) { m_tAtt = _tAtt; }

	bool IsAttackOn() { return m_bAttackOn; }

};

