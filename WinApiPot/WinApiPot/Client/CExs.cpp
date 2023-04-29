#include "pch.h"
#include "CExs.h"

#include "CResMgr.h"
#include "CTimeMgr.h"

#include "CAnimator.h"
#include "CAnimation.h"

#include "CSkill.h"
#include "CPlayer.h"

#include "CCollider.h"
#include "CRobotExs.h"

CExs::CExs() :
	CSkillState(SKILL_STATE::EXS),
	m_fCurTime(0.f),
	m_fCreateTime(0.5f)
{
	SetSKillName(L"Player_skill_stand_");

	SetSkillTime(2.f);
	SetMP(5.f);

	CreateCollider();
	GetCollider()->SetScale(Vec2(200.f, 150.f));

	SetAnimSound(L"gn_viper");
}

CExs::~CExs()
{

}

void CExs::Skillupdate()
{
	m_fCurTime += fDT;
	if (m_fCurTime >= m_fCreateTime)
	{
		m_fCurTime = 0.f;
		createExs();
		exit();
	}
}

void CExs::init()
{

}

void CExs::exit()
{
	m_fCurTime = 0.f;
	GetSkill()->GetPlayer()->GetAnimator()->FindAnimation(m_strSkillName)->SetFram(0);
	CSkillState::exit();
}

void CExs::enter()
{
	CSkillState::enter();

	CPlayer* pPLayer = GetSkill()->GetPlayer();
	int iDir = pPLayer->GetPlayerDirX();

	wstring strSkillName = GetSkillName();
	wstring strDir = iDir > 0 ? L"right" : L"left";

	m_strSkillName = strSkillName + strDir;
}

void CExs::createExs()
{
	CRobotExs* CRobot = new CRobotExs;

	int iDir = GetSkill()->GetPlayer()->GetPlayerDirX();
	CRobot->init_dir(iDir);

	Vec2 vPos = GetSkill()->GetPlayer()->GetCollider()->GetFinalPos();
	CRobot->SetPos(vPos);

	CreateObject(CRobot, GROUP_TYPE::ROBOT);
}