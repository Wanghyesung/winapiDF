#include "pch.h"
#include "CMachKick.h"

#include "CCollider.h"

#include "CSkillMgr.h"
#include "CSkill.h"
#include "CPlayer.h"

#include "CAnimator.h"
#include "CAnimation.h"

CMachKick::CMachKick():
	CSkillState(SKILL_STATE::MACH_KICK),
	m_fOffSet(30.f)
{
	SetSKillName(L"Player_skill_mach_kick_");
}

CMachKick::~CMachKick()
{
}

void CMachKick::Skillupdate()
{

	CPlayer* pPlayer = GetSkill()->GetPlayer();
	Vec2 pPlayerPos = pPlayer->GetPos();
	SetPos(pPlayerPos);

	CAnimator* pAnim = pPlayer->GetAnimator();
	int iDir = pPlayer->GetPlayerDirX();

	float fFinalPos = m_vCollOffSet.x + iDir * m_fOffSet;
	wstring strSkillName = GetSkillName();
	if (iDir > 0)
	{
		GetCollider()->SetOffSet(Vec2(fFinalPos, m_vCollOffSet.y));
		strSkillName += L"right";
	}
	else
	{
		GetCollider()->SetOffSet(Vec2(fFinalPos, m_vCollOffSet.y));
		strSkillName += L"left";
	}



	if (pAnim->FindAnimation(strSkillName)->IsFinish())
	{
		pAnim->FindAnimation(strSkillName)->SetFram(0);
		exit();
		return;
	}

}

void CMachKick::init()
{

	CreateCollider();
	GetCollider()->SetActive(false);

	m_vCollSize = Vec2(100.f, 40.f);
	m_vCollOffSet = Vec2(-20.f, 70.f);
	GetCollider()->SetScale(m_vCollSize);
	GetCollider()->SetOffSet(m_vCollOffSet);
}

void CMachKick::OnColliderEnter(CCollider* _pOther)
{
}

void CMachKick::OnColliderExit(CCollider* _pOther)
{
}

void CMachKick::OnCollision(CCollider* _pOther)
{
}
