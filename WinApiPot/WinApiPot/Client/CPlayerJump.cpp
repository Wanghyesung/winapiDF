#include "pch.h"
#include "CPlayerJump.h"

#include "CRigidBody.h"
#include "CGravity.h"

#include "CAnimation.h"
#include "CAnimator.h"

#include "CFSM.h"
#include "CPlayer.h"
#include "CKeyMgr.h"


CPlayerJump::CPlayerJump():
	CPlayerState(PLAYER_STATE::JUMP)
{

}

CPlayerJump::~CPlayerJump()
{

}

void CPlayerJump::update()
{
	CPlayer* pPlayer = GetFSM()->GetPlayer();
	CRigidBody* pRigidy = pPlayer->GetRigidBody();
	CGravity* pGraviy = pPlayer->GetGravity();
	PLAYER_STATE ePrevState = GetFSM()->GetPrevState();

	int iDir = pPlayer->GetPlayerDirX();
	int iCurFrame = GetCurFrame();
	//전프레임 상태

	if (!pGraviy->IsGetGravity())
	{
		pGraviy->SetGravity(true);
		pPlayer->SetJumPos(pPlayer->GetPos());

		if(ePrevState == PLAYER_STATE::IDLE)
			pRigidy->SetVelocity(Vec2(0.f, -700.f));
		else if (ePrevState == PLAYER_STATE::WALK)
			pRigidy->SetVelocity(Vec2(iDir * 170.f, -700.f));
		else if (ePrevState == PLAYER_STATE::RUN)
			pRigidy->SetVelocity(Vec2(iDir * 240.f, -700.f));
	}



	if (KEY_HOLD(KEY::RIGHT))
	{
		int iDirX = 1;
		pPlayer->SetPlayerDirX(iDirX);
		pRigidy->AddForce(Vec2(70.f, 0.f));
	}
		
	if (KEY_HOLD(KEY::LEFT))
	{
		int iDirX = -1;
		pPlayer->SetPlayerDirX(iDirX);
		pRigidy->AddForce(Vec2(-70.f, 0.f));
	}

	if (KEY_HOLD(KEY::DOWN))
		pRigidy->AddForce(Vec2(0.f, 40.f));
	if (KEY_HOLD(KEY::UP))
		pRigidy->AddForce(Vec2(0.f, -40.f));



	if (iCurFrame == -1)
	{
		ChangeFSMState(GetFSM(), PLAYER_STATE::JUMP_AIR);
	}

	if (KEY_TAP(KEY::X))
	{
		ChangeFSMState(GetFSM(), PLAYER_STATE::ATTACK_AIR);
	}


}

void CPlayerJump::Enter()
{

}

void CPlayerJump::Exit()
{
	CPlayerState::Exit();
	GetFSM()->GetPlayer()->GetAnimator()->GetCurAnimation()->SetFram(0);
	GetFSM()->GetPlayer()->GetAnimator()->GetOtherAnimation()->SetFram(0);
}
