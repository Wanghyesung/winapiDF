#include "pch.h"
#include "CRx78.h"

#include "CTimeMgr.h"

#include "CAnimator.h"
#include "CAnimation.h"

#include "CSkill.h"
#include "CPlayer.h"

#include "CCollider.h"
#include "CRobotRx78.h"

CRx78::CRx78():
	CSkillState(SKILL_STATE::RX),
	m_fCurTime(0.f),
	m_fCreateTime(0.5f)
{
	SetSKillName(L"Player_skill_stand_");

	SetSkillTime(2.f);
	SetMP(5.f);

	CreateCollider();

	SetAnimSound(L"gn_lrunner");
}

CRx78::~CRx78()
{

}

void CRx78::Skillupdate()
{
	m_fCurTime += fDT;
	if (m_fCurTime >= m_fCreateTime)
	{
		m_fCurTime = 0.f;
		createRx78();
		exit();
	}
}

void CRx78::init()
{

}

void CRx78::exit()
{
	m_fCurTime = 0.f;
	GetSkill()->GetPlayer()->GetAnimator()->FindAnimation(m_strSkillName)->SetFram(0);
	CSkillState::exit();
}

void CRx78::enter()
{
	CSkillState::enter();

	CPlayer* pPLayer = GetSkill()->GetPlayer();
	int iDir = pPLayer->GetPlayerDirX();

	wstring strSkillName = GetSkillName();
	wstring strDir = iDir > 0 ? L"right" : L"left";
	
	m_strSkillName = strSkillName + strDir;
}

void CRx78::createRx78()
{
	CRobotRx78* CRobot = new CRobotRx78;

	Vec2 vPos = GetSkill()->GetPlayer()->GetCollider()->GetFinalPos();
	CRobot->SetPos(vPos);

	CreateObject(CRobot, GROUP_TYPE::ROBOT);
}
