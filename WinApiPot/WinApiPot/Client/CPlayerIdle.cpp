#include "pch.h"
#include "CPlayerIdle.h"

#include "CAnimator.h"
#include "CAnimation.h"

#include "CFSM.h"
#include "CPlayer.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

CPlayerIdle::CPlayerIdle() :
	CPlayerState(PLAYER_STATE::IDLE)
{
}

CPlayerIdle::~CPlayerIdle()
{

}

void CPlayerIdle::update()
{
	if (GetFSM()->GetPlayer()->IsOnDobuleKey())
	{
		ChangeFSMState(GetFSM(), PLAYER_STATE::RUN);
		return;
	}

	if (KEY_HOLD(KEY::RIGHT) ||
		KEY_HOLD(KEY::LEFT) ||
		KEY_HOLD(KEY::DOWN)||
		KEY_HOLD(KEY::UP))
	{
		ChangeFSMState(GetFSM(), PLAYER_STATE::WALK);
	}


	if (KEY_TAP(KEY::SPACE))
	{
		ChangeFSMState(GetFSM(), PLAYER_STATE::JUMP);
	}

	if (KEY_TAP(KEY::X) || KEY_HOLD(KEY::X))
	{
		ChangeFSMState(GetFSM(), PLAYER_STATE::ATTACK);
	}

	
}

void CPlayerIdle::Enter()
{

}

void CPlayerIdle::Exit()
{
	CPlayerState::Exit();
 	GetFSM()->GetPlayer()->GetAnimator()->GetCurAnimation()->SetFram(0);
}
