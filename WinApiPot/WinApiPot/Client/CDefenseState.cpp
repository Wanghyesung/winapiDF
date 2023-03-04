#include "pch.h"
#include "CDefenseState.h"

#include "CAnimation.h"
#include "CAnimator.h"

#include "AI.h"
#include "CState.h"
#include "CMonster.h"
#include "CTimeMgr.h"

#define DEFENS_ON 2

CDefenseState::CDefenseState():
	CState(MONSTER_STATE::DEFENSE),
	m_fDefDuration(3.f),
	m_fCurTime(0.f)
{

}

CDefenseState::~CDefenseState()
{

}

void CDefenseState::update()
{
	CMonster* pMon = GetMonster();

	int iFrame = pMon->GetAnimator()->GetCurAnimation()->GetCurFrame();
	if (iFrame == DEFENS_ON)
	{
		m_fCurTime += fDT;
		pMon->GetAnimator()->GetCurAnimation()->SetFram(DEFENS_ON);
	}

	if (m_fCurTime>= m_fDefDuration)
	{
		ChangeAIState(pMon->GetAI(), MONSTER_STATE::IDLE);
	}
}

void CDefenseState::enter()
{

}

void CDefenseState::exit()
{
	m_fCurTime = 0.f;
	GetMonster()->GetAnimator()->GetCurAnimation()->SetFram(0);
	CState::exit();
}
