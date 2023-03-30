#include "pch.h"
#include "CPlayerDead.h"

#include "CFSM.h"
#include "CPlayer.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CRigidBody.h"
#include "CCoinMgr.h"

CPlayerDead::CPlayerDead():
	CPlayerState(PLAYER_STATE::DEAD)
{
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
		DeleteObject(GetFSM()->GetPlayer());
		return;
	}

}

void CPlayerDead::Enter()
{
	//플레이어 강체영향 안받게
	GetFSM()->GetPlayer()->GetRigidBody()->SetVelocity(Vec2(0.f, 0.f));
	GetFSM()->GetPlayer()->GetRigidBody()->SetAccel(false);
}

void CPlayerDead::Exit()
{
	CPlayerState::Exit();
	GetFSM()->GetPlayer()->GetAnimator()->GetCurAnimation()->SetFram(0);
}
