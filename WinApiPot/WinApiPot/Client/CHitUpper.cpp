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

#include "CSound.h"

#define LASTHITMOTION 2
#define HITMOTION 1

CHitUpper::CHitUpper():
	CState(MONSTER_STATE::UPPER_HIT),
	m_fDownTime(1.5f),
	m_strMotionName(L"")
{

}

CHitUpper::~CHitUpper()
{

}

void CHitUpper::enter()
{
	GetAnimSound()->Play(false);

	if (GetAI()->GetPreState()->GetType() == GetType())
	{
		GetMonster()->GetAnimator()->FindAnimation(m_strMotionName)->SetFram(HITMOTION);
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
	m_fCurTime = 0.f;
	GetMonster()->GetAnimator()->GetCurAnimation()->SetFram(0);
}

void CHitUpper::update()
{
	CMonster* pMon = GetMonster();
	tHitInfo tHit = GetMonster()->GetHitInfo();

	/*if (!pMon->GetGravity()->IsGetGravity())
	{
		m_fCurTime += fDT;
		pMon->GetAnimator()->GetCurAnimation()->SetFram(tHit.m_iMaxHitFrame-1);
	}*/

	//collider체크가 씬이 끝나고 실행되기 때문에 지금 현재 플레이 중인 애니메이션은 idle일거임
	if (pMon->GetGravity()->IsGetGravity())
	{
		pMon->GetAnimator()->FindAnimation(m_strMotionName)->SetFram(LASTHITMOTION);
	}

	//누어있는 모션 나오게
	else if (m_iHitAnimFrame == tHit.m_iMaxHitFrame - 1)
	{
		m_fCurTime += fDT;
		pMon->GetAnimator()->FindAnimation(m_strMotionName)->SetFram(tHit.m_iMaxHitFrame - 1);
	}

	

	if (m_fCurTime >= m_fDownTime)
	{
		ChangeAIState(GetAI(), MONSTER_STATE::IDLE);
	}
}
