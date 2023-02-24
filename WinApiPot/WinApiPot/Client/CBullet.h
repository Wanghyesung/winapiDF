#pragma once
#include "CObject.h"

class CCollider;
class CPlayer;

class CBullet :
    public CObject
{
public:
	CBullet(CPlayer* _pPlayer, ATTACK_TYPE _eAttType);
	virtual ~CBullet();


private:
	CCollider* m_pCollider;//�� �浹ü
	CPlayer* m_pPlayer;//���� ������Ų �÷��̾ü

	Vec2 m_vDir;//����
	Vec2 m_vPos;

	Vec2 vDeadLine;//������ ��ġ

	tAttackInfo m_tAtt;

	float m_fSpeed;

	float m_fCurTime;
	float m_fDelTime;

	float m_fHitRcnt;
	float m_fUpperVluae;

public:
	virtual void render(HDC _dc);
	virtual void update();

public:
	const tAttackInfo& GetAttInfo() { return m_tAtt; }

public:
	virtual void OnColliderEnter(CCollider* _pOther);
	virtual void OnColliderExit(CCollider* _pOther);
	virtual void OnCollision(CCollider* _pOther);



};

