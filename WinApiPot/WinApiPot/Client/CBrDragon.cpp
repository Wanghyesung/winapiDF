#include "pch.h"
#include "CBrDragon.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CGravity.h"

#include "CResMgr.h"
#include "CTimeMgr.h"

#include "CTexture.h"

#include "AI.h"
#include "CState.h"
#include "CNearAttack.h"
#include "CAttackObject.h"
#include "CBullet.h"
#include "CBoom.h"
#include "CDropRobot.h"
#include "CExsFire.h"

#include "CSkillState.h"
#include "CHitState.h"
#include "CHitUpper.h"
#include "CDeadState.h"
#include "CInterfaceMgr.h"

CBrDragon::CBrDragon():
	m_eMonState(MONSTER_STATE::IDLE)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(70.f, 90.f));
	GetCollider()->SetOffSet(Vec2(0.f, 0.f));

	CreateAnimator();
	GetAnimator()->SetRBG(0, 0, 0);

	CreateGravity();


	//이미지

	CTexture* pRightMotion = CResMgr::GetInst()->LoadTextur(L"BrDragon_Monster_right", L"..\\OutPut\\bin_release\\Content\\Texture\\brdragon_right.bmp");
	CTexture* pLeftMotion = CResMgr::GetInst()->LoadTextur(L"BrDragon_Monster_left", L"..\\OutPut\\bin_release\\Content\\Texture\\brdragon_left.bmp");
	// 308 172
	// 2156 1376
	// 1848 0
	//right 

	GetAnimator()->CreateAnimation(L"BrDragon_Idle_right", pRightMotion, Vec2(0.f, 344.f), Vec2(308.f, 172.f), Vec2(308.f, 0.f), Vec2(0.f, 0.f), 0.1f, 1);
	GetAnimator()->CreateAnimation(L"BrDragon_Normal_Attack_right", pRightMotion, Vec2(0.f, 0.f), Vec2(308.f, 172.f), Vec2(308.f, 0.f), Vec2(0.f, 0.f), 0.2f, 4);
	GetAnimator()->CreateAnimation(L"BrDragon_Attack_right", pRightMotion, Vec2(0.f, 172.f), Vec2(308.f, 172.f), Vec2(308.f, 0.f), Vec2(0.f, 0.f), 0.1f, 7);
	
	GetAnimator()->CreateAnimation(L"BrDragon_Move_Back_right", pRightMotion, Vec2(0.f, 516.f), Vec2(308.f, 172.f), Vec2(308.f, 0.f), Vec2(0.f, 0.f), 0.1f, 7);
	GetAnimator()->CreateAnimation(L"BrDragon_Move_right", pRightMotion, Vec2(0.f, 688.f), Vec2(308.f, 172.f), Vec2(308.f, 0.f), Vec2(0.f, 0.f), 0.1f, 7);
	GetAnimator()->CreateAnimation(L"BrDragon_Motion_Hit_right", pRightMotion, Vec2(0.f, 1032.f), Vec2(308.f, 172.f), Vec2(308.f, 0.f), Vec2(0.f, 0.f), 0.15f, 2);
	GetAnimator()->FindAnimation(L"BrDragon_Motion_Hit_right")->Create(pRightMotion, Vec2(0.f, 1204.f), Vec2(308.f, 172.f), Vec2(308.f, 0.f), Vec2(0.f, 0.f), 0.15f, 3);


	//left
	GetAnimator()->CreateAnimation(L"BrDragon_Idle_left", pLeftMotion, Vec2(1848.f, 344.f), Vec2(308.f, 172.f), Vec2(-308.f, 0.f), Vec2(0.f, 0.f), 0.1f, 1);
	GetAnimator()->CreateAnimation(L"BrDragon_Normal_Attack_left", pLeftMotion, Vec2(1848.f, 0.f), Vec2(308.f, 172.f), Vec2(-308.f, 0.f), Vec2(0.f, 0.f), 0.2f, 4);
	GetAnimator()->CreateAnimation(L"BrDragon_Attack_left", pLeftMotion, Vec2(1848.f, 172.f), Vec2(308.f, 172.f), Vec2(-308.f, 0.f), Vec2(0.f, 0.f), 0.1f, 7);
	
	GetAnimator()->CreateAnimation(L"BrDragon_Move_Back_left", pLeftMotion, Vec2(1848.f, 516.f), Vec2(308.f, 172.f), Vec2(-308.f, 0.f), Vec2(0.f, 0.f), 0.1f, 7);
	GetAnimator()->CreateAnimation(L"BrDragon_Move_left", pLeftMotion, Vec2(1848.f, 688.f), Vec2(308.f, 172.f), Vec2(-308.f, 0.f), Vec2(0.f, 0.f), 0.1f, 7);
	GetAnimator()->CreateAnimation(L"BrDragon_Motion_Hit_left", pLeftMotion, Vec2(1848.f, 1032.f), Vec2(308.f, 172.f), Vec2(-308.f, 0.f), Vec2(0.f, 0.f), 0.15f, 2);
	GetAnimator()->FindAnimation(L"BrDragon_Motion_Hit_left")->Create(pLeftMotion, Vec2(1848.f, 1204.f), Vec2(308.f, 172.f), Vec2(-308.f, 0.f), Vec2(0.f, 0.f), 0.15f, 3);

	GetAnimator()->Play(L"BrDragon_Idle_right", true);
}

CBrDragon::~CBrDragon()
{

}

void CBrDragon::update()
{
	if (IsDead())
	{
		DeleteObject(this);
		return;
	}

	CMonster::update();
	AI* pAI = GetAI();

	MONSTER_STATE eMonState = pAI->GetCurState()->GetType();

	//상태에따라 애니메이션 재생
	update_state();

	//내 FSM업데이트
	if (pAI != nullptr)
	{
		pAI->update();
	}

	//현재 공격중이면 공격오브젝트 업데이트
	CAttackObject* pMonSkill = GetSKillObj();
	if (pMonSkill->GetCollider()->IsActive())
	{
		pMonSkill->Skill_update();
	}

	
}

void CBrDragon::render(HDC _dc)
{
	component_render(_dc);
}

void CBrDragon::hit(CCollider* _pOther, const tAttackInfo& _tAtt)
{
	CMonster::hit(_pOther, _tAtt);
}

void CBrDragon::update_state()
{
	CState* pState = GetAI()->GetCurState();
	m_eMonState = pState->GetType();

	CAnimator* pAnim = GetAnimator();

	int iDir = pState->GetDir();
	wstring sDir;
	if (iDir >= 0)
		sDir = L"_right";
	else
		sDir = L"_left";

	wstring strMotion;

	switch (m_eMonState)
	{
	case MONSTER_STATE::IDLE:
	{
		strMotion = L"BrDragon_Idle" + sDir;
		pAnim->Play(strMotion, true);
	}
	break;

	case MONSTER_STATE::TRACE:
	{
		strMotion = L"BrDragon_Move";
		strMotion += sDir;
		pAnim->Play(strMotion, true);
	}
	break;
	case MONSTER_STATE::ATTACK:
	{
		strMotion = ((CNearAttack*)pState)->GetAttackName();
		strMotion = L"BrDragon" + strMotion + sDir;
		pAnim->Play(strMotion, false);
	}
	break;

	case MONSTER_STATE::HIT:
	{
		strMotion = L"BrDragon_Motion_Hit";
		strMotion += sDir;
		pAnim->Play(strMotion, false);
		int iFrame = GetAnimator()->GetCurAnimation()->GetCurFrame();
		((CHitState*)GetAI()->GetState(MONSTER_STATE::HIT))->SetAnimFrame(iFrame);
	}
	break;
	case MONSTER_STATE::UPPER_HIT:
	{
		strMotion = L"BrDragon_Motion_Hit";
		strMotion += sDir;
		pAnim->Play(strMotion, false);
		int iFrame = GetAnimator()->GetCurAnimation()->GetCurFrame();
		((CHitUpper*)GetAI()->GetState(MONSTER_STATE::UPPER_HIT))->SetAnimFrame(iFrame);
		((CHitUpper*)GetAI()->GetState(MONSTER_STATE::UPPER_HIT))->SetAnimName(strMotion);
	}
	break;
	case MONSTER_STATE::DEAD:
	{
		strMotion = L"BrDragon_Motion_Hit";
		strMotion += sDir;
		pAnim->Play(strMotion, false);
		SetActiv(false);//비활성화 (공격 관통하게)
		int iFrame = GetAnimator()->GetCurAnimation()->GetCurFrame();
		((CDeadState*)GetAI()->GetState(MONSTER_STATE::DEAD))->SetAnimFrame(iFrame);
	}
	break;
	}
}

void CBrDragon::OnColliderEnter(CCollider* _pOther)
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
		else if (dynamic_cast<CBoom*>(pobj))
		{
			CBoom* pBoom = dynamic_cast<CBoom*>(pobj);
			hit(pBoom->GetCollider(), pBoom->GetAttInfo());
		}
		else if (dynamic_cast<CExsFire*>(pobj))
		{
			CExsFire* pFire = dynamic_cast<CExsFire*>(pobj);
			hit(pFire->GetCollider(), pFire->GetAttInfo());
		}
	}


	if (tMonInfo.m_iHp <= 0.f)
	{
		ChangeAIState(GetAI(), MONSTER_STATE::DEAD);
	}
}

void CBrDragon::OnColliderExit(CCollider* _pOther)
{
}

void CBrDragon::OnCollision(CCollider* _pOther)
{
	//CMonster::OnCollision(_pOther);

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

		else if (dynamic_cast<CDropRobot*>(pobj))
		{
			CDropRobot* pRobot = dynamic_cast<CDropRobot*>(pobj);
			if (!pRobot->IsAttackOn())
				return;

			hit(pRobot->GetCollider(), pRobot->GetAttInfo());
		}

		if (tMonInfo.m_iHp == 0)
		{
			ChangeAIState(GetAI(), MONSTER_STATE::DEAD);
		}
	}

}
