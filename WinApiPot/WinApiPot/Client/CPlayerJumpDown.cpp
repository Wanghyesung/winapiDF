#include "pch.h"
#include "CPlayerJumpDown.h"

#include "CFSM.h"
#include "CPlayer.h"

#include "CAnimation.h"
#include "CAnimator.h"


CPlayerJumpDown::CPlayerJumpDown():
	CPlayerState(PLAYER_STATE::JUMP_DOWN)
{
}

CPlayerJumpDown::~CPlayerJumpDown()
{
}

void CPlayerJumpDown::update()
{
	CFSM* pFSM = GetFSM();
	CPlayer* pPlayer = GetFSM()->GetPlayer();
	int iCurFrame = pPlayer->GetAnimator()->GetCurAnimation()->GetCurFrame();

	if (iCurFrame == -1)
	{
		ChangeFSMState(pFSM, PLAYER_STATE::IDLE);
		GetFSM()->GetPlayer()->GetAnimator()->GetCurAnimation()->SetFram(1,true);
	}
}

void CPlayerJumpDown::Exit()
{
	CPlayerState::Exit();
	InitZeroFrame();
	GetFSM()->GetPlayer()->GetAnimator()->GetCurAnimation()->SetFram(0,true);
}

void CPlayerJumpDown::Enter()
{
}


