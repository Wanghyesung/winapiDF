#include "pch.h"
#include "CDeadState.h"

#include "CMonster.h"

#include "CAnimation.h"
#include "CAnimator.h"

CDeadState::CDeadState():
	CState(MONSTER_STATE::DEAD),
	m_iCurFrame(0)
{

}

CDeadState::~CDeadState()
{

}

void CDeadState::update()
{
	if (m_iCurFrame == -1)
	{
		GetMonster()->SetDead();
	}
}

void CDeadState::enter()
{

}

void CDeadState::exit()
{
	CState::exit();
}
