#include "pch.h"
#include "CMonster.h"

#include "AI.h"
#include "CState.h"

#include "CCameraMgr.h"
#include "CCollider.h";

#include "CGravity.h"

#include "CRigidBody.h"

#include "CTimeMgr.h"

CMonster::CMonster() :
	m_tMonInfo{},
	m_bHit(false),
	m_bActiv(true)
	//m_fHitTime(0.5f),
	//m_fHitCurTime(0.f)
{
	//CreateCollider();
	//GetCollider()->SetScale(Vec2(40.f, 40.f));
	//
	//CreateGravity();
}

CMonster::~CMonster()
{
	if (m_AI != nullptr)
	{
		delete m_AI;
	}
}


void CMonster::update()
{

	if (m_bHit)
		return;
	
	if (m_AI != nullptr)
	{
		m_AI->update();
	}
}

void CMonster::render(HDC _dc)
{
	//Vec2 vPos = GetPos();
	//Vec2 vScale = GetScale();
	//
	//vPos = CCameraMgr::GetInst()->GetRenderPos(vPos);
	//
	//Rectangle(_dc,
	//	(int)(vPos.x - vScale.x/ 2.f),
	//	(int)(vPos.y - vScale.y / 2.f),
	//	(int)(vPos.x + vScale.x / 2.f),
	//	(int)(vPos.y + vScale.y / 2.f));

	component_render(_dc);
}

void CMonster::hit(CCollider* _pOther, const tAttackInfo& _tAtt)
{
	MONSTER_STATE m_tMonState = m_AI->m_pCurState->GetType();
	
	CCollider* pCollider = GetCollider();

	m_tHitInfo.m_fHitRcnt = _tAtt.m_fAttRcnt;
	m_tHitInfo.m_fHitRigidityTime = _tAtt.m_fAttRigidityTime;
	m_tHitInfo.m_fHitUpperRcnt = _tAtt.m_fAttUpperRcnt;

	if (_pOther->GetObj()->GetTag() == GROUP_TYPE::SKILL
		&& m_tMonInfo.m_iHp != 0)
	{
		float fDir = GetCollider()->GetFinalPos().x - _pOther->GetFinalPos().x;
		if (fDir > 0.f)
			fDir = 1.f;
		else
			fDir = -1.f;

		ATTACK_TYPE eAttackType = _tAtt.m_eAttType;
		if (m_tMonState == MONSTER_STATE::UPPER_HIT)
			eAttackType = ATTACK_TYPE::UPPER;

		switch (eAttackType)
		{
		case ATTACK_TYPE::UPPER:
		{
			m_tHitInfo.m_fHitDir = fDir;
			GetGravity()->SetGravity(true);
			if (GetJumPos().IsZero())
				SetJumPos(pCollider->GetFinalPos());
			GetRigidBody()->SetVelocity(Vec2(0.f, m_tHitInfo.m_fHitUpperRcnt));
			//GetRigidBody()->SetAccelA(Vec2(0.f, _tAtt.m_fAttUpperAcc));
			ChangeAIState(m_AI, MONSTER_STATE::UPPER_HIT);
		}
		break;

		case ATTACK_TYPE::NORMAL:
		{
			m_tHitInfo.m_fHitDir = fDir;
			ChangeAIState(m_AI, MONSTER_STATE::HIT);
		}
		break;
		}

		//tMonInfo.m_iHp -= _tAtt.m_fAttackDamage;
	}
}

void CMonster::SetAI(AI* _AI)
{
	m_AI = _AI;
	m_AI->m_pOwner = this;
}



void CMonster::OnColliderEnter(CCollider* _pOther)
{
	
}

void CMonster::OnColliderExit(CCollider* _pOther)
{
	
}

void CMonster::OnCollision(CCollider* _pOther)
{

}


