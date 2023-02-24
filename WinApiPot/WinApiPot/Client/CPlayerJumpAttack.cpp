#include "pch.h"
#include "CPlayerJumpAttack.h"

#include "CFSM.h"
#include "CPlayer.h"

#include "CAnimation.h"
#include "CAnimator.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CGravity.h"
#include "CRigidBody.h"

CPlayerJumpAttack::CPlayerJumpAttack() :
	CPlayerState(PLAYER_STATE::ATTACK_AIR),
	m_fAttackTime(0.3f),
	m_fCurTime(0.f)
{
}

CPlayerJumpAttack::~CPlayerJumpAttack()
{
}

void CPlayerJumpAttack::update()
{
	CFSM* pFSM = GetFSM();
	CPlayer* pPlayer = pFSM->GetPlayer();
	CRigidBody* pRigidy = pPlayer->GetRigidBody();
	int iFrame = GetCurFrame();

	m_fCurTime += fDT;

	if (KEY_TAP(KEY::X) || KEY_HOLD(KEY::X))
	{
		m_fCurTime = 0.f;
	}

	if (KEY_NONE(KEY::X))
	{
		GetFSM()->GetPlayer()->GetAnimator()->GetCurAnimation()->SetFram(iFrame);
	}


	if (KEY_HOLD(KEY::RIGHT))
		pRigidy->AddForce(Vec2(70.f, 0.f));
	if (KEY_HOLD(KEY::LEFT))
		pRigidy->AddForce(Vec2(-70.f, 0.f));
	if (KEY_HOLD(KEY::DOWN))
		pRigidy->AddForce(Vec2(0.f, 40.f));
	if (KEY_HOLD(KEY::UP))
		pRigidy->AddForce(Vec2(0.f, -40.f));

	if (iFrame>=1 && iFrame<=4)
	{
		Fire(iFrame);
	}


	if (m_fCurTime >= m_fAttackTime ||
		iFrame == -1)
	{
		ChangeFSMState(pFSM, PLAYER_STATE::JUMP_AIR);
	}

	if (!pPlayer->GetGravity()->IsGetGravity())
	{
		ChangeFSMState(pFSM, PLAYER_STATE::JUMP_DOWN);
	}

}

void CPlayerJumpAttack::Enter()
{
	InitZeroFrame();
}

void CPlayerJumpAttack::Exit()
{
	CPlayerState::Exit();
	GetFSM()->GetPlayer()->GetAnimator()->GetCurAnimation()->SetFram(0);
	m_fCurTime = 0;
}

void CPlayerJumpAttack::Fire(UINT _iFireFrame)
{
	if (m_iCurAttFrame != _iFireFrame)
	{
		CPlayer* pPlayer = GetFSM()->GetPlayer();
		m_iCurAttFrame = _iFireFrame;
		pPlayer->CreateBullet(pPlayer);
	}
}
