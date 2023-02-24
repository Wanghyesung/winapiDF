#include "pch.h"
#include "CHitUpper.h"

#include "AI.h"

#include "CObject.h"
#include "CMonster.h"
#include "CRigidBody.h"

#include "CGravity.h"
#include "CAnimation.h"
#include "CAnimator.h"

#include "CTimeMgr.h"


#define LASTHITMOTION 2
#define HITMOTION 1

CHitUpper::CHitUpper():
	CState(MONSTER_STATE::UPPER_HIT),
	m_fDownTime(1.5f)
{

}

CHitUpper::~CHitUpper()
{

}

void CHitUpper::enter()
{
	if (GetAI()->GetPreState()->GetType() == GetType())
	{
		GetMonster()->GetAnimator()->GetCurAnimation()->SetFram(HITMOTION);
	}

	m_fCurTime = 0.f;

	int iHitDir = 0;
	tHitInfo tHit = GetMonster()->GetHitInfo();
	if (tHit.m_fHitDir > 0.f)
		iHitDir = -1;
	else
		iHitDir = 1;
	SetDir(iHitDir);
	GetMonster()->GetRigidBody()->SetForce(Vec2(0.f, 0.f));
}

void CHitUpper::exit()
{
	CState::exit();
	m_iHitAnimFrame = 0;
	GetMonster()->GetAnimator()->GetCurAnimation()->SetFram(0);
}

void CHitUpper::update()
{
	CMonster* pMon = GetMonster();

	if (!pMon->GetGravity()->IsGetGravity())
	{
		m_fCurTime += fDT;
		pMon->GetAnimator()->GetCurAnimation()->SetFram(LASTHITMOTION);
	}

	else if (m_iHitAnimFrame == HITMOTION)
	{
		pMon->GetAnimator()->GetCurAnimation()->SetFram(HITMOTION);
	}

	if (m_fCurTime >= m_fDownTime)
	{
		ChangeAIState(GetAI(), MONSTER_STATE::IDLE);
	}
}
