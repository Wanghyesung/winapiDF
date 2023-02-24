#include "pch.h"
#include "CHitState.h"

#include "CObject.h"
#include "CMonster.h"
#include "CAnimation.h"
#include "CAnimator.h"

#include "CTimeMgr.h"
#include "CRigidBody.h"

#define LASTHITMOTION 2

CHitState::CHitState():
	CState(MONSTER_STATE::HIT),
	m_iHitAnimFrame(0),
	m_fCurTime(0.f)
{

}

CHitState::~CHitState()
{

}

void CHitState::update()
{
	m_fCurTime += fDT;
	tHitInfo tMonHit = GetMonster()->GetHitInfo();

	if (tMonHit.m_fHitRigidityTime <= m_fCurTime)
	{
		m_fCurTime = 0.f;
		ChangeAIState(GetAI(), MONSTER_STATE::IDLE);
		return;
	}
	
	//°æÁ÷

	if (m_iHitAnimFrame == (tMonHit.m_iMaxHitFrame - LASTHITMOTION))
	{
		GetMonster()->GetAnimator()->GetCurAnimation()->SetFram(tMonHit.m_iMaxHitFrame - LASTHITMOTION);
	}
	
	else
	{
		Vec2 vForce = Vec2(tMonHit.m_fHitRcnt * tMonHit.m_fHitDir, 0.f);

		GetMonster()->GetRigidBody()->SetAccelA(vForce);
		GetMonster()->GetRigidBody()->AddForce(vForce);
	}
	
	//GetMonster()->GetAnimator()->Play();

}

void CHitState::enter()
{
	GetMonster()->GetAnimator()->GetCurAnimation()->SetFram(0);

	m_iHitAnimFrame = 0;
	int iHitDir = 0;
	tHitInfo tHit = GetMonster()->GetHitInfo();
	if (tHit.m_fHitDir > 0.f)
		iHitDir = -1;
	else
		iHitDir = 1;
	SetDir(iHitDir);
	GetMonster()->GetRigidBody()->SetForce(Vec2(0.f, 0.f));
}

void CHitState::exit()
{
	CState::exit();
	m_fCurTime = 0.f;
	GetMonster()->GetAnimator()->GetCurAnimation()->SetFram(0);
}


