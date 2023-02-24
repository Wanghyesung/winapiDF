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
	int iFrame = GetCurFrame();

	if (iFrame == -1)
	{
		ChangeFSMState(pFSM, PLAYER_STATE::IDLE);
	}
}

void CPlayerJumpDown::Exit()
{
	CPlayerState::Exit();
	InitZeroFrame();
	GetFSM()->GetPlayer()->GetAnimator()->GetCurAnimation()->SetFram(0);
}

void CPlayerJumpDown::Enter()
{
}


