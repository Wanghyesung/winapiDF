#include "pch.h"
#include "CMonster.h"

#include "AI.h"
#include "CState.h"

#include "CCameraMgr.h"
#include "CCollider.h";

#include "CGravity.h"

#include "CRigidBody.h"

#include "CTimeMgr.h"

#include "CAttackObject.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CInterfaceMgr.h"
#include "CItemMgr.h"


CMonster::CMonster() :
	m_tMonInfo{},
	m_bHit(false),
	m_bActiv(true),
	m_pAttackObj(nullptr)
{
	
}

CMonster::~CMonster()
{
	if (m_AI != nullptr)
	{
		delete m_AI;
	}

	//이것도 Scene에서 소멸자에서 삭제
	//DeleteObject(m_pAttackObj);
	if (m_pAttackObj != nullptr && m_tMonInfo.m_iHp <= 0)
	{
		DeleteObject(m_pAttackObj);
	}
}


void CMonster::update()
{
	
	//내 스킬 쿨타임 감소
	update_skillTime();

}

void CMonster::render(HDC _dc)
{

	component_render(_dc);
}


void CMonster::update_MonInterFace()
{
	//추가 체력
	CInterfaceMgr::GetInst()->SetTargetMon(GetName());
	CInterfaceMgr::GetInst()->ChangeMonInterFaceValue(GetName(), m_tMonInfo.m_iHp);
}

void CMonster::hit(CCollider* _pOther, const tAttackInfo& _tAtt)
{
	MONSTER_STATE m_tMonState = m_AI->m_pCurState->GetType();
	
	CCollider* pCollider = GetCollider();

	//if (GetGravity()->IsGetGravity())
	//{
	//	if (!IsSameJumLoc(_pOther, GetCollider()))
	//		return;
	//}

	m_tHitInfo.m_fHitRcnt = _tAtt.m_fAttRcnt;
	m_tHitInfo.m_fHitRigidityTime = _tAtt.m_fAttRigidityTime;
	m_tHitInfo.m_fHitUpperRcnt = _tAtt.m_fAttUpperRcnt;

	if (_pOther->GetObj()->GetTag() == GROUP_TYPE::SKILL
		&& m_tMonInfo.m_iHp > 0)
	{
		float fDir = GetCollider()->GetFinalPos().x - _pOther->GetFinalPos().x;
		if (fDir > 0.f)
			fDir = 1.f;
		else
			fDir = -1.f;

		int iDir = m_AI->GetCurState()->GetDir() * -1;

		ATTACK_TYPE eAttackType = _tAtt.m_eAttType;
		if (m_tMonState == MONSTER_STATE::UPPER_HIT)
			eAttackType = ATTACK_TYPE::UPPER;

		switch (eAttackType)
		{
		case ATTACK_TYPE::UPPER:
		{
			m_tHitInfo.m_fHitDir = iDir;
			GetGravity()->SetGravity(true);
			if (GetJumPos().IsZero())
				SetJumPos(pCollider->GetFinalPos());
			GetRigidBody()->SetVelocity(Vec2(m_tHitInfo.m_fHitRcnt * iDir, m_tHitInfo.m_fHitUpperRcnt));
			//GetRigidBody()->SetAccelA(Vec2(0.f, _tAtt.m_fAttUpperAcc));
			ChangeAIState(m_AI, MONSTER_STATE::UPPER_HIT);
		}
		break;

		case ATTACK_TYPE::NORMAL:
		{
			m_tHitInfo.m_fHitDir = iDir;
			ChangeAIState(m_AI, MONSTER_STATE::HIT);
		}
		break;
		}

		
		m_tMonInfo.m_iHp-= _tAtt.m_fAttackDamage;
		if (m_tMonInfo.m_iHp <= 0.f)
		{
			m_tMonInfo.m_iHp = 0.f;
			////아이템 생성
			//CItemMgr::GetInst()->CreateItem(GetPos());
		}	
		update_MonInterFace();
	}
}

void CMonster::SetAI(AI* _AI)
{
	m_AI = _AI;
	m_AI->m_pOwner = this;
}

void CMonster::update_skillTime()
{
	for (int i = 0; i < m_vecSKill.size(); ++i)
	{
		if (m_vecSKill[i].m_fSkillTime <= 0.f)
			continue;
		m_vecSKill[i].m_fSkillTime -= fDT;
	}
}

void CMonster::set_attackobj(SCENE_TYPE _eSceneType)
{
	//몬스터 공격 오브젝트 미리 생성
	m_pAttackObj = new CAttackObject;
	m_pAttackObj->m_pOwner = this;
	SceneMgr::GetInst()->FindScene(_eSceneType)->AddObject(m_pAttackObj, GROUP_TYPE::MONSTER_SKILL);
}


bool CMonster::IsSameJumLoc(CCollider* _pOther, CCollider* _pThis)
{
	if (GetGravity()->IsGetGravity())
	{
		Vec2 vOffset = _pThis->GetOffSetPos();
		Vec2 vJumPos = GetJumPos() + vOffset;
		Vec2 vOtherPos = _pOther->GetFinalPos();
		Vec2 vScale = _pThis->GetScale();
		Vec2 vOtherScale = _pOther->GetScale();

		if (abs(vJumPos.x - vOtherPos.x) > abs((vScale.x + vOtherScale.x) / 2.f) ||
			abs(vJumPos.y - vOtherPos.y) > abs((vScale.y + vOtherScale.y) / 2.f))
		{
			return false;
		}
	}
	return true;
}

void CMonster::OnColliderEnter(CCollider* _pOther)
{
	
}

void CMonster::OnColliderExit(CCollider* _pOther)
{
	
}

void CMonster::OnCollision(CCollider* _pOther)
{
	//if (_pOther->GetObj()->GetTag() == GROUP_TYPE::MONSTER)
	//{
	//	Vec2 vFinalPos = GetCollider()->GetFinalPos();
	//	Vec2 vScale = GetCollider()->GetScale();
	//
	//	Vec2 vOtherPos = _pOther->GetFinalPos();
	//	Vec2 vOtherScale = _pOther->GetScale();
	//	
	//	float fLenX = abs(vFinalPos.x - vOtherPos.x);
	//	float fLenY = abs(vFinalPos.y - vOtherPos.y);
	//
	//	float fValueX = ((vScale.x + vOtherScale.x) / 2.f) - fLenX;
	//	float fValueY = ((vScale.y + vOtherScale.y) / 2.f) - fLenY;
	//	
	//	int iDir = 0;
	//	if (fValueX <= fValueY)
	//	{
	//		(vFinalPos.x - vOtherPos.x) > 0 ? iDir = 1 : iDir = -1;
	//		vOtherPos.x -= iDir * fValueX;
	//	}
	//	else
	//	{
	//		(vFinalPos.y - vOtherPos.y) > 0 ? iDir = 1 : iDir = -1;
	//		vOtherPos.y -= iDir * fValueY;
	//	}
	//
	//	
	//	SetPos(vOtherPos);
	//
	//}

}


