#include "pch.h"
#include "CRandomFire.h"

#include "CCollider.h"

#include "CSkillMgr.h"
#include "CSkill.h"

#include "CAnimation.h"
#include "CAnimator.h"

#include "CPlayer.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

CRandomFire::CRandomFire():
	CSkillState(SKILL_STATE::RANDOM_FIRE),
	m_fAccTime(0.3f),
	m_fCurTime(0.f)
{
	SetSKillName(L"Player_skill_randomfire");
}

CRandomFire::~CRandomFire()
{
}

void CRandomFire::Skillupdate()
{
	CPlayer* pPlayer = GetSkill()->GetPlayer();
	Vec2 pPlayerPos = pPlayer->GetPos();
	SetPos(pPlayerPos);

	CAnimator* pAnim = pPlayer->GetAnimator();

	float fFinalPos = m_vCollOffSet.x + m_fOffSet;
	wstring strSkillName = GetSkillName();
	GetCollider()->SetOffSet(Vec2(fFinalPos, m_vCollOffSet.y));

	m_fCurTime += fDT;

	if (((KEY_TAP(KEY::X) || KEY_HOLD(KEY::X))) &&
		m_fCurTime>=m_fAccTime)
	{
		m_fCurTime = 0.f;
		pAnim->FindAnimation(strSkillName)->AddAccTime(0.1f);
	}

	if (pAnim->FindAnimation(strSkillName)->IsFinish())
	{
		pAnim->FindAnimation(strSkillName)->SetFram(0);
		exit();
		return;
	}
}

void CRandomFire::init()
{
	CreateCollider();
	GetCollider()->SetActive(false);

	m_vCollSize = Vec2(200.f, 150.f);
	m_vCollOffSet = Vec2(-20.f, 30.f);
	GetCollider()->SetScale(m_vCollSize);
	GetCollider()->SetOffSet(m_vCollOffSet);
}

void CRandomFire::OnColliderEnter(CCollider* _pOther)
{
}

void CRandomFire::OnColliderExit(CCollider* _pOther)
{
}

void CRandomFire::OnCollision(CCollider* _pOther)
{
}
