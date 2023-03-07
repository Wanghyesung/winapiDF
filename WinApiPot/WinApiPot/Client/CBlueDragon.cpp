#include "pch.h"
#include "CBlueDragon.h"

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
#include "CSkillState.h"
#include "CHitState.h"
#include "CHitUpper.h"
#include "CDeadState.h"
#include "CInterfaceMgr.h"

CBlueDragon::CBlueDragon():
	m_eMonState(MONSTER_STATE::IDLE),
	m_fCurTime(0.f),
	m_fDefensTime(10.f)
{

	CreateCollider();
	GetCollider()->SetScale(Vec2(70.f, 90.f));
	GetCollider()->SetOffSet(Vec2(0.f, 0.f));

	CreateAnimator();
	GetAnimator()->SetRBG(0, 0, 0);

	CreateGravity();
	
	
	//이미지

	CTexture* pRightMotion =  CResMgr::GetInst()->LoadTextur(L"BDragon_Monster_right", L"..\\OutPut\\bin_release\\Content\\Texture\\bdragon_right.bmp");
	CTexture* pLeftMotion = CResMgr::GetInst()->LoadTextur(L"BDragon_Monster_left", L"..\\OutPut\\bin_release\\Content\\Texture\\bdragon_left.bmp");
	// 308 172
	// 2156 1376
	// 1848 0
	//right 

	GetAnimator()->CreateAnimation(L"BDragon_Idle_right", pRightMotion, Vec2(0.f, 344.f), Vec2(308.f, 172.f), Vec2(308.f, 0.f), Vec2(0.f, 0.f), 0.1f, 1);
	GetAnimator()->CreateAnimation(L"BDragon_Normal_Attack_right", pRightMotion, Vec2(0.f, 0.f), Vec2(308.f, 172.f), Vec2(308.f, 0.f), Vec2(0.f, 0.f), 0.2f, 4);
	GetAnimator()->CreateAnimation(L"BDragon_Attack_right", pRightMotion, Vec2(0.f, 172.f), Vec2(308.f, 172.f), Vec2(308.f, 0.f), Vec2(0.f, 0.f), 0.1f, 7);
	GetAnimator()->CreateAnimation(L"BDragon_Defense_right", pRightMotion, Vec2(0.f, 344.f), Vec2(308.f, 172.f), Vec2(308.f, 0.f), Vec2(0.f, 0.f), 0.1f, 3);
	GetAnimator()->CreateAnimation(L"BDragon_Move_Back_right", pRightMotion, Vec2(0.f, 516.f), Vec2(308.f, 172.f), Vec2(308.f, 0.f), Vec2(0.f, 0.f), 0.1f, 7);
	GetAnimator()->CreateAnimation(L"BDragon_Move_right", pRightMotion, Vec2(0.f, 688.f), Vec2(308.f, 172.f), Vec2(308.f, 0.f), Vec2(0.f, 0.f), 0.1f, 7);
	GetAnimator()->CreateAnimation(L"BDragon_Motion_Hit_right", pRightMotion, Vec2(0.f, 1032.f), Vec2(308.f, 172.f), Vec2(308.f, 0.f), Vec2(0.f, 0.f), 0.15f, 2);
	GetAnimator()->FindAnimation(L"BDragon_Motion_Hit_right")->Create(pRightMotion, Vec2(0.f, 1204.f), Vec2(308.f, 172.f), Vec2(308.f, 0.f), Vec2(0.f, 0.f), 0.15f, 3);
	
	
	//left
	GetAnimator()->CreateAnimation(L"BDragon_Idle_left", pLeftMotion, Vec2(1848.f, 344.f), Vec2(308.f, 172.f), Vec2(-308.f, 0.f), Vec2(0.f, 0.f), 0.1f, 1);
	GetAnimator()->CreateAnimation(L"BDragon_Normal_Attack_left", pLeftMotion, Vec2(1848.f, 0.f), Vec2(308.f, 172.f), Vec2(-308.f, 0.f), Vec2(0.f, 0.f), 0.2f, 4);
	GetAnimator()->CreateAnimation(L"BDragon_Attack_left", pLeftMotion, Vec2(1848.f, 172.f), Vec2(308.f, 172.f), Vec2(-308.f, 0.f), Vec2(0.f, 0.f), 0.1f, 7);
	GetAnimator()->CreateAnimation(L"BDragon_Defense_left", pLeftMotion, Vec2(1848.f, 344.f), Vec2(308.f, 172.f), Vec2(-308.f, 0.f), Vec2(0.f, 0.f), 0.1f, 3);
	GetAnimator()->CreateAnimation(L"BDragon_Move_Back_left", pLeftMotion, Vec2(1848.f, 516.f), Vec2(308.f, 172.f), Vec2(-308.f, 0.f), Vec2(0.f, 0.f), 0.1f, 7);
	GetAnimator()->CreateAnimation(L"BDragon_Move_left", pLeftMotion, Vec2(1848.f, 688.f), Vec2(308.f, 172.f), Vec2(-308.f, 0.f), Vec2(0.f, 0.f), 0.1f, 7);
	GetAnimator()->CreateAnimation(L"BDragon_Motion_Hit_left", pLeftMotion, Vec2(1848.f, 1032.f), Vec2(308.f, 172.f), Vec2(-308.f, 0.f), Vec2(0.f, 0.f), 0.15f, 2);
	GetAnimator()->FindAnimation(L"BDragon_Motion_Hit_left")->Create(pLeftMotion, Vec2(1848.f, 1204.f), Vec2(308.f, 172.f), Vec2(-308.f, 0.f), Vec2(0.f, 0.f), 0.15f, 3);

	GetAnimator()->Play(L"BDragon_Idle_right", true);

}

CBlueDragon::~CBlueDragon()
{

}

void CBlueDragon::update()
{
	CMonster::update();
	AI* pAI = GetAI();

	MONSTER_STATE eMonState = pAI->GetCurState()->GetType();

	if (m_fDefensTime <= m_fCurTime &&
		eMonState == MONSTER_STATE::TRACE)
	{
		m_fCurTime = 0.f;
		int iDir = pAI->GetCurState()->GetDir();

		pAI->GetState(MONSTER_STATE::DEFENSE)->SetDir(iDir);
		ChangeAIState(pAI, MONSTER_STATE::DEFENSE);
	}

	else if(eMonState != MONSTER_STATE::DEFENSE)
	{
		m_fCurTime += fDT;//방어시간
	}

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

	//상태에따라 애니메이션 재생
	update_state();
}


void CBlueDragon::render(HDC _dc)
{
	component_render(_dc);
}

void CBlueDragon::hit(CCollider* _pOther, const tAttackInfo& _tAtt)
{
	if (GetAI()->GetCurState()->GetType() == MONSTER_STATE::DEFENSE)
	{
		tMonInfo m_tMonInfo = GetAI()->GetCMonster()->GetMonInfo();

		CInterfaceMgr::GetInst()->SetTargetMon(GetName());
		CInterfaceMgr::GetInst()->ChangeMonInterFaceValue(GetName(), m_tMonInfo.m_iHp);
		//m_tMonInfo.m_iHp -= (_tAtt.m_fAttackDamage/2.f);
		return;
	}

	CMonster::hit(_pOther, _tAtt);
}

void CBlueDragon::update_state()
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
		strMotion = L"BDragon_Idle" + sDir;
		pAnim->Play(strMotion, true);
	}
		break;

	case MONSTER_STATE::TRACE:
	{
		strMotion = L"BDragon_Move";
		strMotion += sDir;
		pAnim->Play(strMotion, true);
	}
		break;
	case MONSTER_STATE::ATTACK:
	{
		strMotion = ((CNearAttack*)pState)->GetAttackName();
		strMotion = L"BDragon" + strMotion + sDir;
		pAnim->Play(strMotion, false);
	}
		break;
	break;

	case MONSTER_STATE::DEFENSE:
	{
		strMotion = L"BDragon_Defense";
		strMotion += sDir;
		pAnim->Play(strMotion, false);
	}
	break;

	case MONSTER_STATE::HIT:
	{
		strMotion = L"BDragon_Motion_Hit";
		strMotion += sDir;
		pAnim->Play(strMotion, false);
		int iFrame = GetAnimator()->GetCurAnimation()->GetCurFrame();
		((CHitState*)GetAI()->GetState(MONSTER_STATE::HIT))->SetAnimFrame(iFrame);
	}
		break;
	case MONSTER_STATE::UPPER_HIT:
	{
		strMotion = L"BDragon_Motion_Hit";
		strMotion += sDir;
		pAnim->Play(strMotion, false);
		int iFrame = GetAnimator()->GetCurAnimation()->GetCurFrame();
		((CHitUpper*)GetAI()->GetState(MONSTER_STATE::UPPER_HIT))->SetAnimFrame(iFrame);
	}
		break;
	case MONSTER_STATE::DEAD:
	{
		strMotion = L"BDragon_Motion_Hit";
		strMotion += sDir;
		pAnim->Play(strMotion, false);
		SetActiv(false);//비활성화 (공격 관통하게)
		int iFrame = GetAnimator()->GetCurAnimation()->GetCurFrame();
		((CDeadState*)GetAI()->GetState(MONSTER_STATE::DEAD))->SetAnimFrame(iFrame);
	}
		break;
	}

}
void CBlueDragon::OnColliderEnter(CCollider* _pOther)
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

	if (tMonInfo.m_iHp == 0)
	{
		ChangeAIState(GetAI(), MONSTER_STATE::DEAD);
	}
};

void CBlueDragon::OnColliderExit(CCollider* _pOther)
{
	int a = 10;
};
void CBlueDragon::OnCollision(CCollider* _pOther)
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