#pragma once

#include "pch.h"

class CTexture;
class CAnimator;
class CRigidBody;
class CCollider;
class CSkillState;
class CGravity;
class CSkill;

struct tHitInfo
{
	float m_fHitDir; //맞는 방향
	float m_fHitRcnt;//맞으면 날라갈 양
	float m_fHitUpperRcnt; //맞으면 띄어질 양
	float m_fHitRigidityTime; //경직 시간
	UINT  m_iMaxHitFrame;
};

struct tAttackInfo
{
	float m_fAttackDamage;
	float m_fAttackTime;
	float m_fAttRcnt;//맞으면 날라갈 양
	float m_fAttUpperRcnt; //맞으면 띄어질 양
	float m_fAttUpperAcc; //추가 가속도
	float m_fAttRigidityTime; //경직 시간
	Vec2 m_fAttackRange;
	ATTACK_TYPE m_eAttType;
};


class CObject
{
public:
	CObject();
	virtual ~CObject();//소멸자 다 실행할 수 있게

private:
	Vec2 m_vPos;//내 위치
	Vec2 m_vSclae; // 내 크기

	Vec2 m_vJumpPos;//처음에 올라갈 때 계산할 양
	Vec2 m_vFinalJumPos; //내려갈 떄 계산할 양

	wstring m_strName;
	GROUP_TYPE m_tTag;

	bool m_bAlive; //내 오브젝트가 활성인지 비활성인지

	CTexture* m_pTex;
	CAnimator* m_pAnim;
	CRigidBody* m_pRigidBody;
	CCollider* m_pCollider;
	CGravity* m_pGravity;

public:
	virtual void render(HDC _dc);
	virtual void update() = 0 ;//상속
	virtual void finalupdate();

	void component_render(HDC _dc);


public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vSclae = _vScale; };

	Vec2 GetScale() { return m_vSclae; }
	Vec2 GetPos() { return m_vPos; }

	CAnimator* GetAnimator() { return m_pAnim; }
	CRigidBody* GetRigidBody() { return m_pRigidBody; }
	CCollider* GetCollider() { return m_pCollider; }
	CGravity* GetGravity() { return m_pGravity; }

	const wstring& GetName() { return m_strName; }
	void SetName(const wstring& _strName) { m_strName = _strName; }

	bool IsDead() { return !m_bAlive; }

//점프관련 함수
public:
	void SetJumPos(Vec2 _v) { m_vJumpPos = _v; } //착지할 위치 세팅
	Vec2 GetJumPos() { return m_vJumpPos; } //지금 점프중인 위치 반환

	void SetFinalJumPos(Vec2 _v) { m_vFinalJumPos = _v; }
	Vec2 GetFinalJumPos() { return m_vFinalJumPos; }

public:
	GROUP_TYPE GetTag() { return m_tTag; }
	void SetTag(GROUP_TYPE _tTag) { m_tTag = _tTag; }


public:
	void CreateAnimator();
	void CreateRigidBody();
	void CreateCollider();
	void CreateGravity();
public:
	virtual void OnColliderEnter(CCollider* _pOther) {};
	virtual void OnColliderExit(CCollider* _pOther) {};
	virtual void OnCollision(CCollider* _pOther) {};


private:
	void setDead() { m_bAlive = false; }//이벤트 매니저에서만 접근

	friend class CEventMgr;
};

