#include "pch.h"
#include "CPlayerHitUpper.h"

#include "CFSM.h"
#include "CPlayer.h"

#include "CAnimation.h"
#include "CAnimator.h"

#include "CTimeMgr.h"

#include "CGravity.h"

#define HIT_MAX_FRAME 4
#define HIT_START 2

CPlayerHitUpper::CPlayerHitUpper() :
	CPlayerState(PLAYER_STATE::UPPER_HIT),
	m_fDonwTime(0.8f)
{
}

CPlayerHitUpper::~CPlayerHitUpper()
{

}

void CPlayerHitUpper::update()
{
	CFSM* pFSM = GetFSM();
	CPlayer* pPlayer = pFSM->GetPlayer();

	int iFrame = GetCurFrame();

	if (!pPlayer->GetGravity()->IsGetGravity())
	{
		m_fCurTime += fDT;
		pPlayer->GetAnimator()->GetCurAnimation()->SetFram(HIT_MAX_FRAME);
	}


	if (m_fCurTime >= m_fDonwTime)
	{
		ChangeFSMState(pFSM, PLAYER_STATE::IDLE);
	}

}


void CPlayerHitUpper::Exit()
{
	m_fCurTime = 0.f;
	CPlayerState::Exit();
	GetFSM()->GetPlayer()->GetAnimator()->GetCurAnimation()->SetFram(0);
}

void CPlayerHitUpper::Enter()
{
	CPlayer* pPlayer = GetFSM()->GetPlayer();
	if (pPlayer->playerPrevState == PLAYER_STATE::UPPER_HIT)
	{
		pPlayer->GetAnimator()->GetCurAnimation()->SetFram(HIT_START);
	}

}

