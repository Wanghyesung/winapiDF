#include "pch.h"
#include "CDragon.h"

#include "CCollider.h"
#include "CGravity.h"

#include "CTexture.h"
#include "CResMgr.h"
#include "CAnimation.h"
#include "CAnimator.h"

#include "AI.h"
#include "CState.h"
#include "CTraceState.h"
#include "CIdleState.h"
#include "CHitState.h"
#include "CHitUpper.h"
#include "CDeadState.h"

#include "CRigidBody.h"
#include "CGravity.h"
#include "CBullet.h"
#include "CSkillState.h"

CDragon::CDragon()
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(50.f, 50.f));

	CreateAnimator();
	GetAnimator()->SetRBG(0, 0, 0);

	CreateGravity();
	CTexture* m_pDragonRight = CResMgr::GetInst()->LoadTextur(L"Dragon_Monster_right", L"Texture\\dragon_right.bmp");
	CTexture* m_pDragonLeft = CResMgr::GetInst()->LoadTextur(L"Dragon_Monster_left", L"Texture\\dragon_left.bmp");

	
	GetAnimator()->CreateAnimation(L"Dragon_Motion_right", m_pDragonRight, Vec2(0.f, 0.f), Vec2(100.f, 100.f), Vec2(100.f, 0.f), Vec2(0.f, 0.f), 0.1f, 8);
	GetAnimator()->CreateAnimation(L"Dragon_Motion_left", m_pDragonLeft, Vec2(700.f, 0.f), Vec2(100.f, 100.f), Vec2(-100.f, 0.f), Vec2(0.f, 0.f), 0.1f, 8);

	GetAnimator()->CreateAnimation(L"Dragon_Attack_right", m_pDragonRight, Vec2(0.f, 100.f), Vec2(100.f, 100.f), Vec2(100.f, 0.f), Vec2(0.f, 0.f), 0.15f, 8);
	GetAnimator()->CreateAnimation(L"Dragon_Attack_left",  m_pDragonLeft, Vec2(700.f, 100.f), Vec2(100.f, 100.f), Vec2(-100.f, 0.f), Vec2(0.f, 0.f), 0.15f, 8);

	GetAnimator()->CreateAnimation(L"Dragon_Dead_right", m_pDragonRight, Vec2(0.f, 200.f), Vec2(100.f, 100.f), Vec2(100.f, 0.f), Vec2(0.f, 0.f), 0.1f, 3);
	GetAnimator()->CreateAnimation(L"Dragon_Dead_left",  m_pDragonLeft, Vec2(700.f, 200.f), Vec2(100.f, 100.f), Vec2(-100.f, 0.f), Vec2(0.f, 0.f), 0.1f, 3);

	GetAnimator()->CreateAnimation(L"Dragon_hit_right", m_pDragonRight, Vec2(0.f, 200.f), Vec2(100.f, 100.f), Vec2(100.f, 0.f), Vec2(0.f, 0.f), 0.2f, 2);
	GetAnimator()->CreateAnimation(L"Dragon_hit_left", m_pDragonLeft, Vec2(700.f, 200.f), Vec2(100.f, 100.f), Vec2(-100.f, 0.f), Vec2(0.f, 0.f), 0.2f, 2);

	GetAnimator()->CreateAnimation(L"Dragon_fullHit_right", m_pDragonRight, Vec2(0.f, 200.f), Vec2(100.f, 100.f), Vec2(100.f, 0.f), Vec2(0.f, 0.f), 0.2f, 3);
	GetAnimator()->CreateAnimation(L"Dragon_fullHit_left", m_pDragonLeft, Vec2(700.f, 200.f), Vec2(100.f, 100.f), Vec2(-100.f, 0.f), Vec2(0.f, 0.f), 0.2f, 3);

	
}

CDragon::~CDragon()
{
	
}


void CDragon::update()
{
	//맞고있는지
	//IsGettingHit();

	//if (IsHit())
	//{
	//	m_tMonState = MONSTER_STATE::HIT;
	//}
	if (IsDead())
	{
		DeleteObject(this);
		return;
	}

	if (GetAI() != nullptr)
	{
		GetAI()->update();
	}

	update_state();

//CMonster::update();
}

void CDragon::update_state()
{
	CState* pState = GetAI()->GetCurState();
	m_tMonState = pState->GetType();

	if (pState == nullptr)
		return;

	//방향 잡기
	int iDir = pState->GetDir();

	wstring sDir;
	if (iDir >= 0)
		sDir = L"_right";
	else
		sDir = L"_left";

	wstring sMtion;

	switch (m_tMonState)
	{
	case MONSTER_STATE::IDLE:
	{
		sMtion = L"Dragon_Motion" + sDir;
		GetAnimator()->Play(sMtion, true);
	}
	break;

	case MONSTER_STATE::TRACE:
	{
		sMtion = L"Dragon_Motion" + sDir;
		GetAnimator()->Play(sMtion, true);
	}
	break;

	case MONSTER_STATE::ATTACK:
	{
		wstring sMtion = L"Dragon_Attack" + sDir;
		GetAnimator()->Play(sMtion, false);
	}
	break;

	case MONSTER_STATE::HIT:
	{
		wstring sMtion = L"Dragon_hit" + sDir;
		GetAnimator()->Play(sMtion, false);
		int iFrame = GetAnimator()->GetCurAnimation()->GetCurFrame();
		((CHitState*)GetAI()->GetState(MONSTER_STATE::HIT))->SetAnimFrame(iFrame);
	}
	break;

	case MONSTER_STATE::UPPER_HIT:
	{
		wstring sMtion = L"Dragon_fullHit" + sDir;
		GetAnimator()->Play(sMtion, false);
		int iFrame = GetAnimator()->GetCurAnimation()->GetCurFrame();
		((CHitUpper*)GetAI()->GetState(MONSTER_STATE::UPPER_HIT))->SetAnimFrame(iFrame);
	}
	break;

	case MONSTER_STATE::DEAD:
	{
		wstring sMtion = L"Dragon_fullHit" + sDir;
		GetAnimator()->Play(sMtion, false);
		SetActiv(false);//비활성화
		int iFrame = GetAnimator()->GetCurAnimation()->GetCurFrame();
		((CDeadState*)GetAI()->GetState(MONSTER_STATE::DEAD))->SetAnimFrame(iFrame);
	}
	break;
	}
}

void CDragon::render(HDC _dc)
{
	component_render(_dc);
}

void CDragon::Hit(CCollider* _pOther, const tAttackInfo& _tAtt)
{
	tHitInfo& tHitInfo = GetHitInfo();
	tMonInfo& tMonInfo = GetMonInfo();
	CCollider* pCollider = GetCollider();

	tHitInfo.m_fHitRcnt = _tAtt.m_fAttRcnt;
	tHitInfo.m_fHitRigidityTime = _tAtt.m_fAttRigidityTime;
	tHitInfo.m_fHitUpperRcnt = _tAtt.m_fAttUpperRcnt;

	if (_pOther->GetObj()->GetTag() == GROUP_TYPE::SKILL
		&& tMonInfo.m_iHp != 0)
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
			tHitInfo.m_fHitDir = fDir;
			GetGravity()->SetGravity(true);
			if (GetJumPos().IsZero())
				SetJumPos(pCollider->GetFinalPos());
			GetRigidBody()->SetVelocity(Vec2(0.f, tHitInfo.m_fHitUpperRcnt));
			ChangeAIState(GetAI(), MONSTER_STATE::UPPER_HIT);
		}
		break;

		case ATTACK_TYPE::NORMAL:
		{
			tHitInfo.m_fHitDir = fDir;
			ChangeAIState(GetAI(), MONSTER_STATE::HIT);
		}
		break;
		}

		//tMonInfo.m_iHp -= _tAtt.m_fAttackDamage;
	}
}

void CDragon::OnColliderEnter(CCollider* _pOther)
{
	tMonInfo& tMonInfo = GetMonInfo();
	CObject* pobj =	_pOther->GetObj();

	if (pobj->GetTag() == GROUP_TYPE::SKILL
		&& tMonInfo.m_iHp != 0)
	{
		if (dynamic_cast<CBullet*>(pobj))
		{
			CBullet* pBullet = dynamic_cast<CBullet*>(pobj);
			Hit(pBullet->GetCollider(), pBullet->GetAttInfo());
		}
		//else if (dynamic_cast<CSkillState*>(pobj))
		//{
		//	CSkillState* pSkill = dynamic_cast<CSkillState*>(pobj);
		//	Hit(pSkill->GetCollider(), pSkill->GetAttInfo());
		//	스킬은 애니메이션에 프레임에 맞게 
		//  skillstate에서 애니메이션에 공격모션이 true이면 true상태인지 확인하고 Hit함수로
		//}
	}
	
	if (tMonInfo.m_iHp == 0)
	{
		ChangeAIState(GetAI(), MONSTER_STATE::DEAD);
	}
};

void CDragon::OnColliderExit(CCollider* _pOther)
{
	int a = 10;
};
void CDragon::OnCollision(CCollider* _pOther) 
{

};