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
		GetFSM()->GetPlayer()->SetPos(Vec2(-3000.f, -3000.f));
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
	CPlayerState::Exit();
	InitZeroFrame();
	int iDir = GetFSM()->GetPlayer()->GetPlayerDirX();
	wstring strDir = iDir < 0 ? L"_left" : L"_right";
	GetFSM()->GetPlayer()->GetAnimator()->FindAnimation(L"Player_Hit" + strDir)->SetFram(0);
	
}
