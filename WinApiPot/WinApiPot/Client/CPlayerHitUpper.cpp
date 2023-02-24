#include "pch.h"
#include "CPlayerHitUpper.h"

#include "CFSM.h"
#include "CPlayer.h"

#include "CAnimation.h"
#include "CAnimator.h"

#include "CTimeMgr.h"


#define HIT_MAX_FRAME 4

CPlayerHitUpper::CPlayerHitUpper() :
	CPlayerState(PLAYER_STATE::UPPER_HIT)
{
}

CPlayerHitUpper::~CPlayerHitUpper()
{

}

void CPlayerHitUpper::update()
{
	m_fCurTime += fDT;


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
		//pPlayer->m_
	}
}

