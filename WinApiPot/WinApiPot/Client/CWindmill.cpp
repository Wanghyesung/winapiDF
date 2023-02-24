#include "pch.h"
#include "CWindmill.h"


#include "CAnimation.h"


#include "CCollider.h"

#include "CTimeMgr.h"
#include "CSkillMgr.h"

#include "CSkill.h"
#include "CPlayer.h"
#include "CObject.h"

CWindmill::CWindmill():
	CSkillState(SKILL_STATE::WINDMILL)
{
	//내 스킬 이름 정하기
	SetSKillName(L"Player_skill_windmill");

	tAttackInfo tAtt = {};
	tAtt.m_eAttType = ATTACK_TYPE::NORMAL;
	tAtt.m_fAttackDamage = 20.f;
	tAtt.m_fAttRcnt = 30.f;
	tAtt.m_fAttRigidityTime = 0.8f;
	tAtt.m_fAttUpperRcnt = -30.f;

	SetAttInfo(tAtt);
}

CWindmill::~CWindmill()
{
}

void CWindmill::Skillupdate()
{

	CPlayer* pPlayer = GetSkill()->GetPlayer();
	Vec2 pPlayerPos = pPlayer->GetPos();
	SetPos(pPlayerPos);

	CAnimator* pAnim = pPlayer->GetAnimator();
	wstring strSkillName = GetSkillName();

	if (pAnim->FindAnimation(strSkillName)->IsFinish())
	{
		pAnim->FindAnimation(strSkillName)->SetFram(0);
		exit();
		return;
	}

}


void CWindmill::init()
{
	CreateCollider();
	GetCollider()->SetActive(false);

	m_vCollSize = Vec2(100.f, 50.f);
	m_vCollOffSet = Vec2(-20.f, 75.f);
	GetCollider()->SetScale(m_vCollSize);
	GetCollider()->SetOffSet(m_vCollOffSet);
}

void CWindmill::OnColliderEnter(CCollider* _pOther)
{
	
}

void CWindmill::OnColliderExit(CCollider* _pOther)
{
	
}

void CWindmill::OnCollision(CCollider* _pOther)
{

}
