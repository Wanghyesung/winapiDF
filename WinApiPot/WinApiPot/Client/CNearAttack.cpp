#include "pch.h"
#include "CNearAttack.h"
#include "AI.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CMonster.h"
#include "CAttackObject.h"

CNearAttack::CNearAttack():
	CState(MONSTER_STATE::ATTACK),
	m_iAttackCount(0),
	m_iAttackFrame(0)
{

}

CNearAttack::~CNearAttack()
{

}

void CNearAttack::update()
{
	CMonster* pMon = GetAI()->GetCMonster();
	int iFrame = pMon->GetAnimator()->GetCurAnimation()->GetCurFrame();

	if (iFrame == -1)
	{
		ChangeAIState(GetAI(), MONSTER_STATE::IDLE);
		return;
	}

	if (iFrame == m_iAttackFrame && m_iAttackCount<1)
	{
		++m_iAttackCount;
		pMon->GetSKillObj()->SetColActive(true);
	}

}

void CNearAttack::enter()
{
	
}

void CNearAttack::exit()
{
	CState::exit();
	GetMonster()->GetAnimator()->GetCurAnimation()->SetFram(0);
	m_iAttackCount = 0;
	GetAI()->GetCMonster()->GetSKillObj()->SetColActive(false);
}


