#include "pch.h"
#include "CKick.h"

#include "CSkill.h"
#include "CSkillMgr.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CObject.h"
#include "CPlayer.h"

CKick::CKick():
	CSkillState(SKILL_STATE::UPPER_KICK),
	m_fOffSet(30.f)
{
	SetSKillName(L"Player_skill_kick_");
}

CKick::~CKick()
{

}

void CKick::Skillupdate()
{

	////방향 잡기 + 방향에 따라 충돌체 offset 바꾸기
	CPlayer* pPlayer = GetSkill()->GetPlayer();
	Vec2 pPlayerPos = pPlayer->GetPos();
	SetPos(pPlayerPos);

	CAnimator* pAnim = pPlayer->GetAnimator();
	int iDir = pPlayer->GetPlayerDirX();

	float fFinalPos = m_vCollOffSet.x + iDir* m_fOffSet;
	wstring strSkillName = GetSkillName();

	if (iDir > 0)
	{
		GetCollider()->SetOffSet(Vec2(fFinalPos , m_vCollOffSet.y));
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



void CKick::init()
{
	CreateCollider();
	GetCollider()->SetActive(false);
	m_vCollSize = Vec2(60.f, 70.f);
	m_vCollOffSet = Vec2(-20.f, 70.f);
	GetCollider()->SetScale(m_vCollSize);
	GetCollider()->SetOffSet(m_vCollOffSet);
}

void CKick::OnColliderEnter(CCollider* _pOther)
{
	
}

void CKick::OnColliderExit(CCollider* _pOther)
{

}

void CKick::OnCollision(CCollider* _pOther)
{

}
