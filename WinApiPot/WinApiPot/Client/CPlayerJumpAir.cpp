#include "pch.h"
#include "CPlayerJumpAir.h"

#include "CFSM.h"
#include "CPlayer.h"

#include "CKeyMgr.h"

#include "CGravity.h"
#include "CRigidBody.h"

#include "CAnimation.h"
#include "CAnimator.h"

CPlayerJumpAir::CPlayerJumpAir():
	CPlayerState(PLAYER_STATE::JUMP_AIR)
{
}

CPlayerJumpAir::~CPlayerJumpAir()
{
}

void CPlayerJumpAir::update()
{
	CPlayer* pPlayer = GetFSM()->GetPlayer();
	CRigidBody* pRigidy = pPlayer->GetRigidBody();
	CFSM* pFSM = GetFSM();
	PLAYER_STATE ePrevState = pFSM->GetPrevState();
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

	//이전 상태가 공중사격이 아니면
	if (KEY_TAP(KEY::X) && ePrevState != PLAYER_STATE::ATTACK_AIR)
	{
		ChangeFSMState(pFSM, PLAYER_STATE::ATTACK_AIR);
	}

	if (!pPlayer->GetGravity()->IsGetGravity())
	{
		ChangeFSMState(pFSM, PLAYER_STATE::JUMP_DOWN);
	}

}

void CPlayerJumpAir::Enter()
{
	m_iDirX = GetFSM()->GetPlayer()->GetPlayerDirX();
}

void CPlayerJumpAir::Exit()
{
	CPlayerState::Exit();
	GetFSM()->GetPlayer()->GetAnimator()->GetCurAnimation()->SetFram(0);
}
