#include "pch.h"
#include "CDeadState.h"

#include "CMonster.h"

#include "CAnimation.h"
#include "CAnimator.h"

#include "CSound.h"

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
	//프레임 다 돌면 -1
	if (m_iCurFrame == -1)
	{
		GetMonster()->SetDead();
	}
}

void CDeadState::enter()
{
	GetAnimSound()->Play(false);
}

void CDeadState::exit()
{
	CState::exit();
}
