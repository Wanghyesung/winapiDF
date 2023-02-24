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
	CCollider* m_pCollider;//내 충돌체
	CPlayer* m_pPlayer;//나를 생성시킨 플레이어객체

	Vec2 m_vDir;//방향
	Vec2 m_vPos;

	Vec2 vDeadLine;//삭제될 위치

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

