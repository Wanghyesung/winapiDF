#include "pch.h"
#include "CLord.h"

#include "AI.h"
#include "CState.h"

#include "CAnimator.h"
#include "CAnimation.h"
#include "CCollider.h"

#include "CResMgr.h"

#include "CNearAttack.h"
#include "CHitState.h"
#include "CAttackObject.h"

CLord::CLord():
	m_eMonState(MONSTER_STATE::IDLE)
{
	SetTag(GROUP_TYPE::MONSTER);
	//이름은 몬팩토리에서

	CreateCollider();
	GetCollider()->SetScale(Vec2(70.f, 90.f));
	GetCollider()->SetOffSet(Vec2(0.f, -20.f));

	CreateAnimator();
	GetAnimator()->SetRBG(0, 0, 0);

	CTexture* pRightTex = CResMgr::GetInst()->LoadTextur(L"Lord_right", L"..\\OutPut\\bin_release\\Content\\Texture\\lord_right.bmp");
	CTexture* pLeftTex = CResMgr::GetInst()->LoadTextur(L"Lord_left", L"..\\OutPut\\bin_release\\Content\\Texture\\lord_left.bmp");

	//right
	GetAnimator()->CreateAnimation(L"Lord_Idle_right", pRightTex, Vec2(0.f, 750.f), Vec2(300.f, 250.f), Vec2(300.f, 0.f), Vec2(20.f, 0.f), 0.2f, 6);
	GetAnimator()->CreateAnimation(L"Lord_Skill_right", pRightTex, Vec2(0.f, 250.f), Vec2(300.f, 250.f), Vec2(300.f, 0.f), Vec2(20.f, 0.f), 0.2f, 8);
	GetAnimator()->CreateAnimation(L"Lord_Hit_right", pRightTex, Vec2(0.f, 500.f), Vec2(300.f, 250.f), Vec2(300.f, 0.f), Vec2(20.f, 0.f), 0.2f, 2);
	GetAnimator()->CreateAnimation(L"Lord_Normal_Attack_right", pRightTex, Vec2(0.f, 0.f), Vec2(300.f, 250.f), Vec2(300.f, 0.f), Vec2(20.f, 0.f), 0.2f, 11);
	GetAnimator()->CreateAnimation(L"Lord_Skill2_right", pRightTex, Vec2(0.f, 1000.f), Vec2(300.f, 250.f), Vec2(300.f, 0.f), Vec2(20.f, 0.f), 0.2f, 8);
	//스킬 마지막 공격은 druation 길게

	//left
	GetAnimator()->CreateAnimation(L"Lord_Idle_left", pLeftTex, Vec2(3000.f, 750.f), Vec2(300.f, 250.f), Vec2(-300.f, 0.f), Vec2(-20.f, 0.f), 0.2f, 6);
	GetAnimator()->CreateAnimation(L"Lord_Skill_left", pLeftTex, Vec2(3000.f, 250.f), Vec2(300.f, 250.f), Vec2(-300.f, 0.f), Vec2(-20.f, 0.f), 0.2f, 8);
	GetAnimator()->CreateAnimation(L"Lord_Hit_left", pLeftTex, Vec2(3000.f, 500.f), Vec2(300.f, 250.f), Vec2(-300.f, 0.f), Vec2(-20.f, 0.f), 0.2f, 2);
	GetAnimator()->CreateAnimation(L"Lord_Normal_Attack_left", pLeftTex, Vec2(3000.f, 0.f), Vec2(300.f, 250.f), Vec2(-300.f, 0.f), Vec2(-20.f, 0.f), 0.2f, 11);
	GetAnimator()->CreateAnimation(L"Lord_Skill2_left", pLeftTex, Vec2(3000.f, 1000.f), Vec2(300.f, 250.f), Vec2(-300.f, 0.f), Vec2(-20.f, 0.f), 0.2f, 8);
}

CLord::~CLord()
{

}

void CLord::hit(CCollider* _pOther, const tAttackInfo& _tAtt)
{
	CMonster::hit(_pOther, _tAtt);
}



void CLord::update()
{
	if (IsDead())
	{
		DeleteObject(this);
		return;
	}

	CMonster::update();
	AI* pAI = GetAI();

	MONSTER_STATE eMonState = pAI->GetCurState()->GetType();

	if (pAI != nullptr)
	{
		pAI->update();
	}

	CAttackObject* pMonSkill = GetSKillObj();
	if (pMonSkill->GetCollider()->IsActive())
	{
		pMonSkill->Skill_update();
	}

	update_state();
}

void CLord::update_state()
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
		strMotion = L"Lord_Idle" + sDir;
		pAnim->Play(strMotion,true);
	}
		break;
	case MONSTER_STATE::TRACE:
	{
		strMotion = L"Lord_Idle";
		strMotion += sDir;
		pAnim->Play(strMotion, true);
	}
		break;
	case MONSTER_STATE::ATTACK:
	{
		strMotion = ((CNearAttack*)pState)->GetAttackName();
		strMotion = L"Lord" + strMotion + sDir;
		pAnim->Play(strMotion, false);
	}
		break;;
	case MONSTER_STATE::HIT:
	{
		strMotion = L"Lord_Hit";
		strMotion += sDir;
		pAnim->Play(strMotion, false);
		int iFrame = GetAnimator()->GetCurAnimation()->GetCurFrame();
		((CHitState*)GetAI()->GetState(MONSTER_STATE::HIT))->SetAnimFrame(iFrame);
	}
		break;
	case MONSTER_STATE::DEAD:
	{

	}
		break;
	}
}

void CLord::render(HDC _dc)
{

	component_render(_dc);
}

void CLord::OnColliderEnter(CCollider* _pOther)
{

}

void CLord::OnColliderExit(CCollider* _pOther)
{

}

void CLord::OnCollision(CCollider* _pOther)
{

}
