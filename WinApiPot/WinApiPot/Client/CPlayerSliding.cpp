#include "pch.h"
#include "CPlayerSliding.h"

#include "CFSM.h"
#include "CPlayer.h"

#include "CAnimation.h"
#include "CAnimator.h"

#include "CRigidBody.h"

#include "CSound.h"

CPlayerSliding::CPlayerSliding():
	CPlayerState(PLAYER_STATE::ATTACK_SLIDING),
	m_bSliding(false)
{
	SetAnimSound(L"gn_sliding");
}

CPlayerSliding::~CPlayerSliding()
{
}

void CPlayerSliding::update()
{
	CPlayer* pPlayer = GetFSM()->GetPlayer();
	CRigidBody* pRigidy = pPlayer->GetRigidBody();
	if (!m_bSliding)
	{
		m_bSliding = true;
		int iDir = pPlayer->GetPlayerDirX();
		pRigidy->SetVelocity(Vec2(iDir * 700.f, 0.f));
	}
	

	if (!pRigidy->IsAccelNow())
	{
		ChangeFSMState(GetFSM(), PLAYER_STATE::IDLE);
	}



}

void CPlayerSliding::Exit()
{
	GetAnimSound()->Stop(true);
	m_bSliding = false;
	CPlayerState::Exit();
	GetFSM()->GetPlayer()->GetAnimator()->GetCurAnimation()->SetFram(0);
}

void CPlayerSliding::Enter()
{
	GetAnimSound()->Play(false);
	GetFSM()->GetPlayer()->GetRigidBody()->SetAccel(true);
}
