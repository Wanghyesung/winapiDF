#include "pch.h"
#include "CEvileyeAttack.h"

#include "CAnimator.h"
#include "CAnimation.h"

#include "CEvileye.h"

CEvileyeAttack::CEvileyeAttack():
	CState(MONSTER_STATE::ATTACK),
	m_iAttackCount(0)
{

}

CEvileyeAttack::~CEvileyeAttack()
{

}

void CEvileyeAttack::update()
{
	CEvileye* pEvil = (CEvileye*)GetMonster();
	int iFrame = GetMonster()->GetAnimator()->GetCurAnimation()->GetCurFrame();
	
	//스킬 시작 시간
	UINT iStartFrame = pEvil->m_hashSkillTime[(UINT)m_eCurSkill].m_iStartFrame;

	if (iStartFrame <= iFrame && m_iAttackCount == 0)
	{
		++m_iAttackCount;
		start_skill();
	}

	if (iFrame < 0)
	{
		ChangeAIState(GetAI(), MONSTER_STATE::IDLE);
		return;
	}
}

void CEvileyeAttack::start_skill()
{
	CEvileye* pEvil = (CEvileye*)GetMonster();

	switch (m_eCurSkill)
	{
	case EVILSKILL::LASER:
	{
		pEvil->createLaser();
	}
	break;
	case EVILSKILL::SHOT:
	{
		pEvil->shotEye();
	}
	break;
	}
}

void CEvileyeAttack::enter()
{
	
}

void CEvileyeAttack::exit()
{
	CState::exit();
	m_iAttackCount = 0;
	GetMonster()->GetAnimator()->GetCurAnimation()->SetFram(0);
}


