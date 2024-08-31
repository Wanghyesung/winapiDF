#include "pch.h"
#include "CPlayerRun.h"

#include "CFSM.h"
#include "CPlayer.h"
#include "CRigidBody.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"

#include "CAnimation.h"
#include "CAnimator.h"


CPlayerRun::CPlayerRun():
	CPlayerState(PLAYER_STATE::RUN),
	m_fRunSpeed(320.f)
{

}

CPlayerRun::~CPlayerRun()
{

}

void CPlayerRun::update()
{
	CPlayer* pPlayer = GetFSM()->GetPlayer();
	CRigidBody* pRigidy = pPlayer->GetRigidBody();

	if (KEY_HOLD(KEY::RIGHT))
	{
		iDirX = 1;
		pPlayer->SetPlayerDirX(iDirX);
		pRigidy->AddForce(Vec2(m_fRunSpeed, 0.f));
	}

	if (KEY_HOLD(KEY::LEFT))
	{
		iDirX = -1;
		pPlayer->SetPlayerDirX(iDirX);
		pRigidy->AddForce(Vec2(-m_fRunSpeed, 0.f));
	}

	if (KEY_HOLD(KEY::DOWN))
		pRigidy->AddForce(Vec2(0.f, m_fRunSpeed));

	if (KEY_HOLD(KEY::UP))
		pRigidy->AddForce(Vec2(0.f, -m_fRunSpeed));
	
	if (KEY_TAP(KEY::X))
		ChangeFSMState(GetFSM(), PLAYER_STATE::ATTACK_SLIDING);

	if (!pPlayer->IsOnDobuleKey())
		ChangeFSMState(GetFSM(), PLAYER_STATE::WALK);

	if (KEY_TAP(KEY::SPACE))
		ChangeFSMState(GetFSM(), PLAYER_STATE::JUMP);
}

void CPlayerRun::Enter()
{
	
}

void CPlayerRun::Exit()
{
	CPlayerState::Exit();
	GetFSM()->GetPlayer()->GetAnimator()->GetCurAnimation()->SetFram(0);
}
