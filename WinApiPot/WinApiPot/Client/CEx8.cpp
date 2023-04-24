#include "pch.h"
#include "CEx8.h"

#include "CResMgr.h"
#include "CTimeMgr.h"

#include "CAnimator.h"
#include "CAnimation.h"

#include "CSkill.h"
#include "CPlayer.h"

#include "CCollider.h"
#include "CRobotEx8.h"

CEx8::CEx8() :
	CSkillState(SKILL_STATE::EX8),
	m_fCurTime(0.f),
	m_fCreateTime(0.5f)
{
	SetSKillName(L"Player_skill_stand_");

	//머리 위에 나올 숫자
	CResMgr::GetInst()->LoadTextur(L"ex800", L"..\\OutPut\\bin_release\\Content\\num\\00.bmp");
	for (int i = 0; i < 4; ++i)
	{
		wstring strNum = std::to_wstring(i);
		CResMgr::GetInst()->LoadTextur(L"ex8" + strNum, L"..\\OutPut\\bin_release\\Content\\num\\" + strNum + L".bmp");
	}

	for (int i = 0; i < 10; ++i)
	{
		wstring strNum = L"s" + std::to_wstring(i);
		CResMgr::GetInst()->LoadTextur(L"ex8" + strNum, L"..\\OutPut\\bin_release\\Content\\num\\" + strNum + L".bmp");
	}


	SetSkillTime(2.f);
	SetMP(5.f);

	CreateCollider();
}

CEx8::~CEx8()
{

}

void CEx8::Skillupdate()
{
	m_fCurTime += fDT;
	if (m_fCurTime >= m_fCreateTime)
	{
		m_fCurTime = 0.f;
		createEx8();
		exit();
	}
}

void CEx8::init()
{

}

void CEx8::exit()
{
	m_fCurTime = 0.f;
	GetSkill()->GetPlayer()->GetAnimator()->FindAnimation(m_strSkillName)->SetFram(0);
	CSkillState::exit();
}

void CEx8::enter()
{
	CPlayer* pPLayer = GetSkill()->GetPlayer();
	int iDir = pPLayer->GetPlayerDirX();

	wstring strSkillName = GetSkillName();
	wstring strDir = iDir > 0 ? L"right" : L"left";

	m_strSkillName = strSkillName + strDir;
}

void CEx8::createEx8()
{
	CRobotEx8* CRobot = new CRobotEx8;

	Vec2 vPos = GetSkill()->GetPlayer()->GetCollider()->GetFinalPos();
	CRobot->SetPos(vPos);

	CreateObject(CRobot, GROUP_TYPE::ROBOT);
}
