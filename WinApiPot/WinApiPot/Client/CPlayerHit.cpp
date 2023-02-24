#include "pch.h"
#include "CPlayerHit.h"

#include "CPlayer.h"
#include "CFSM.h"

#include "CAnimation.h"
#include "CAnimator.h"

#include "CRigidBody.h"

#include "CTimeMgr.h"

#define MAX_HIT_FRAME 1

CPlayerHit::CPlayerHit() :
	CPlayerState(PLAYER_STATE::HIT),
	m_fCurTime(0.f)
{

}

CPlayerHit::~CPlayerHit()
{

}

void CPlayerHit::update()
{
	m_fCurTime += fDT;

	CPlayer* pPlayer = GetFSM()->GetPlayer();
	tHitInfo& tPlayerHit = pPlayer->m_tPlayerHit;

	int iCurFrame = GetCurFrame();

	if (tPlayerHit.m_fHitRigidityTime <= m_fCurTime)
	{
		ChangeFSMState(pPlayer->m_pFSM, PLAYER_STATE::IDLE);
		return;
	}

	if (iCurFrame == MAX_HIT_FRAME)
	{
		pPlayer->GetAnimator()->GetCurAnimation()->SetFram(MAX_HIT_FRAME);
	}
	else
	{
		Vec2 vForce = Vec2(tPlayerHit.m_fHitRcnt * tPlayerHit.m_fHitDir, 0.f);
		pPlayer->GetRigidBody()->AddForce(vForce);
	}

}

void CPlayerHit::Enter()
{

}

void CPlayerHit::Exit()
{
	m_fCurTime = 0.f;
	CPlayerState::Exit();
	GetFSM()->GetPlayer()->GetAnimator()->GetCurAnimation()->SetFram(0);
}


