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
	CTexture* m_pDragonRight = CResMgr::GetInst()->LoadTextur(L"Dragon_Monster_right", L"..\\OutPut\\bin_release\\Content\\Texture\\dragon_right.bmp");
	CTexture* m_pDragonLeft = CResMgr::GetInst()->LoadTextur(L"Dragon_Monster_left", L"..\\OutPut\\bin_release\\Content\\Texture\\dragon_left.bmp");


	GetAnimator()->CreateAnimation(L"Dragon_Motion_right", m_pDragonRight, Vec2(0.f, 0.f), Vec2(100.f, 100.f), Vec2(100.f, 0.f), Vec2(0.f, 0.f), 0.1f, 8);
	GetAnimator()->CreateAnimation(L"Dragon_Motion_left", m_pDragonLeft, Vec2(700.f, 0.f), Vec2(100.f, 100.f), Vec2(-100.f, 0.f), Vec2(0.f, 0.f), 0.1f, 8);

	GetAnimator()->CreateAnimation(L"Dragon_Attack_right", m_pDragonRight, Vec2(0.f, 100.f), Vec2(100.f, 100.f), Vec2(100.f, 0.f), Vec2(0.f, 0.f), 0.15f, 8);
	GetAnimator()->CreateAnimation(L"Dragon_Attack_left", m_pDragonLeft, Vec2(700.f, 100.f), Vec2(100.f, 100.f), Vec2(-100.f, 0.f), Vec2(0.f, 0.f), 0.15f, 8);

	GetAnimator()->CreateAnimation(L"Dragon_Dead_right", m_pDragonRight, Vec2(0.f, 200.f), Vec2(100.f, 100.f), Vec2(100.f, 0.f), Vec2(0.f, 0.f), 0.1f, 3);
	GetAnimator()->CreateAnimation(L"Dragon_Dead_left", m_pDragonLeft, Vec2(700.f, 200.f), Vec2(100.f, 100.f), Vec2(-100.f, 0.f), Vec2(0.f, 0.f), 0.1f, 3);

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

	//if (IsHit())
	//{
	//	m_tMonState = MONSTER_STATE::HIT;
	//}
	//스킬 쿨다임 감소
	CMonster::update();

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
		SetActiv(false);//비활성화 (공격 관통하게)
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

void CDragon::hit(CCollider* _pOther, const tAttackInfo& _tAtt)
{
	CMonster::hit(_pOther, _tAtt);
}

void CDragon::OnColliderEnter(CCollider* _pOther)
{
	tMonInfo& tMonInfo = GetMonInfo();
	CObject* pobj = _pOther->GetObj();

	if (pobj->GetTag() == GROUP_TYPE::SKILL
		&& tMonInfo.m_iHp != 0)
	{
		if (dynamic_cast<CBullet*>(pobj))
		{
			CBullet* pBullet = dynamic_cast<CBullet*>(pobj);
			hit(pBullet->GetCollider(), pBullet->GetAttInfo());
		}
	}

	if (tMonInfo.m_iHp <= 0.f)
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
	tMonInfo& tMonInfo = GetMonInfo();
	CObject* pobj = _pOther->GetObj();
	
	if (pobj->GetTag() == GROUP_TYPE::SKILL
		&& tMonInfo.m_iHp != 0)
	{
		if (dynamic_cast<CSkillState*>(pobj))
		{
			CSkillState* pSkill = dynamic_cast<CSkillState*>(pobj);

			if (!pSkill->IsAttackOn())
				return;

			hit(pSkill->GetCollider(), pSkill->GetAttInfo());
		}

		if (tMonInfo.m_iHp == 0)
		{
			ChangeAIState(GetAI(), MONSTER_STATE::DEAD);
		}
	}

};