#include "pch.h"
#include "CPlayerWalk.h"

#include "CFSM.h"

#include "CPlayer.h"
#include "CRigidBody.h"

#include "CAnimation.h"
#include "CAnimator.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

CPlayerWalk::CPlayerWalk():
	CPlayerState(PLAYER_STATE::WALK)
{
}

CPlayerWalk::~CPlayerWalk()
{

}

void CPlayerWalk::update()
{
	CPlayer* pPlayer = GetFSM()->GetPlayer();
	CRigidBody* pRigidy = pPlayer->GetRigidBody();

	int iCurDirX = 0;
	int iCurDirY = 0;

	if (GetFSM()->GetPlayer()->IsOnDobuleKey())
	{
		ChangeFSMState(GetFSM(), PLAYER_STATE::RUN);
	}

	if (KEY_HOLD(KEY::RIGHT))
	{
		iCurDirX = 1;
		pPlayer->SetPlayerDirX(iCurDirX);
		pRigidy->AddForce(Vec2(200.f, 0.f));
	}
	else if (KEY_AWAY(KEY::RIGHT))
	{
		iCurDirX = 0;
	}

	if (KEY_HOLD(KEY::LEFT))
	{
		iCurDirX = -1;
		pPlayer->SetPlayerDirX(iCurDirX);
		pRigidy->AddForce(Vec2(-200.f, -0.f));
	}
	else if (KEY_AWAY(KEY::LEFT))
	{
		iCurDirX = 0;
	}

	if (KEY_HOLD(KEY::DOWN))
	{
		iCurDirY = 1;
		pPlayer->SetPlayerDirY(iCurDirY);
		pRigidy->AddForce(Vec2(0.f, 200.f));

	}
	else if (KEY_AWAY(KEY::DOWN))
	{
		iCurDirY = 0;
	}

	if (KEY_HOLD(KEY::UP))
	{
		iCurDirY = -1;
		pPlayer->SetPlayerDirY(iCurDirY);
		pRigidy->AddForce(Vec2(0.f, -200.f));
	}

	else if (KEY_AWAY(KEY::UP))
	{
		iCurDirY = 0;
	}
	
	if (iCurDirX == 0 && iCurDirY == 0)
	{
		GetFSM()->ChangeState(PLAYER_STATE::IDLE);
		return;
	}


	if (KEY_TAP(KEY::X))
	{
		GetFSM()->ChangeState(PLAYER_STATE::ATTACK);
		return;
	}

	if (KEY_TAP(KEY::SPACE))
	{
		GetFSM()->ChangeState(PLAYER_STATE::JUMP);
	}
}

void CPlayerWalk::Enter()
{

}

void CPlayerWalk::Exit()
{
	CPlayerState::Exit();
	GetFSM()->GetPlayer()->GetAnimator()->GetCurAnimation()->SetFram(0);
}
