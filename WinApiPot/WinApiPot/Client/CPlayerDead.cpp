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
		//��Ȱ����
		CCoinMgr::GetInst()->StartUpdate(GetFSM()->GetPlayer()->GetPos());
		GetFSM()->GetPlayer()->SetPos(Vec2(-2000.f, -2000.f));
		ChangeFSMState(GetFSM(), PLAYER_STATE::IDLE);
	}

}

void CPlayerDead::Enter()
{
	//�÷��̾� ��ü���� �ȹް�
	GetFSM()->GetPlayer()->GetRigidBody()->SetVelocity(Vec2(0.f, 0.f));
	GetFSM()->GetPlayer()->GetRigidBody()->SetAccel(false);
}

void CPlayerDead::Exit()
{
	CPlayerState::Exit();
	InitZeroFrame();
	GetFSM()->GetPlayer()->GetAnimator()->GetCurAnimation()->SetFram(0);
	GetFSM()->GetPlayer()->GetAnimator()->Play(L"Player_idle_right", true);
}
