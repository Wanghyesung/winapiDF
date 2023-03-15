#include "pch.h"
#include "CStandOffAttack.h"

#include "AI.h"
#include "CMonster.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CThunder.h"
#include "CLord.h"

CStandOffAttack::CStandOffAttack():
	CState(MONSTER_STATE::ATTACK_STAND),
	m_iAttackCount(0)
{
}

CStandOffAttack::~CStandOffAttack()
{
}

void CStandOffAttack::update()
{
	CMonster* pMon = GetAI()->GetCMonster();
	int iFrame = pMon->GetAnimator()->GetCurAnimation()->GetCurFrame();

	if (iFrame == m_iAttackFrame && m_iAttackCount ==0)
	{
		++m_iAttackCount;
		CThunder* pThunder = ((CLord*)pMon)->CreateThunder();
		if (pThunder == nullptr)
			assert(pThunder);

		CreateObject(pThunder,GROUP_TYPE::MONSTER_SKILL);
	}

	else if (iFrame == -1)
	{
		ChangeAIState(GetAI(), MONSTER_STATE::IDLE);
	}
	
}


void CStandOffAttack::enter()
{


}

void CStandOffAttack::exit()
{
	CState::exit();
	GetMonster()->GetAnimator()->GetCurAnimation()->SetFram(0);
	m_iAttackCount = 0;

}