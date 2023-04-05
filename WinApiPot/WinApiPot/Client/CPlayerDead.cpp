#include "pch.h"
#include "CPlayerDead.h"

#include "CFSM.h"
#include "CPlayer.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CRigidBody.h"
#include "CCoinMgr.h"

#include "CSound.h"

CPlayerDead::CPlayerDead():
	CPlayerState(PLAYER_STATE::DEAD)
{
	SetAnimSound(L"gn_die");
}

CPlayerDead::~CPlayerDead()
{
}

void CPlayerDead::update()
{
	int iFrame = GetCurFrame();

	if (iFrame == -1)
	{
		//부활할지
		CCoinMgr::GetInst()->StartUpdate(GetFSM()->GetPlayer()->GetPos());
		GetFSM()->GetPlayer()->SetPos(Vec2(-2000.f, -2000.f));
		GetFSM()->GetPlayer()->GetAnimator()->Play(L"Player_idle_right", true);
		ChangeFSMState(GetFSM(), PLAYER_STATE::IDLE);
	}

}

void CPlayerDead::Enter()
{
	GetAnimSound()->Play(false);
	//플레이어 강체영향 안받게
	GetFSM()->GetPlayer()->GetRigidBody()->SetVelocity(Vec2(0.f, 0.f));
	GetFSM()->GetPlayer()->GetRigidBody()->SetAccel(false);
}

void CPlayerDead::Exit()
{
	GetAnimSound()->Stop(true);
	CPlayerState::Exit();
	InitZeroFrame();
	GetFSM()->GetPlayer()->GetAnimator()->GetCurAnimation()->SetFram(0);
	GetFSM()->GetPlayer()->GetAnimator()->Play(L"Player_idle_right", true);
}
