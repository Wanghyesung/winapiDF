#include "pch.h"
#include "CPlayerAttackDown.h"

#include "CFSM.h"
#include "CPlayer.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CPlayerAttack.h"
#include "CAnimation.h"
#include "CAnimator.h"



CPlayerAttackDown::CPlayerAttackDown():
	CPlayerState(PLAYER_STATE::ATTACK_DOWN),
	m_fAttackTime(0.2f),
	m_fCurTime(0.f)
{
}

CPlayerAttackDown::~CPlayerAttackDown()
{
}

void CPlayerAttackDown::update()
{
	CFSM* pFSM = GetFSM();
	CPlayer* pPlayer = pFSM->GetPlayer();
	int iFrame = GetCurFrame();

	m_fCurTime += fDT;

	if (KEY_TAP(KEY::X) || KEY_HOLD(KEY::X))
	{
		m_fCurTime = 0.f;

		if (KEY_NONE(KEY::DOWN))
		{
			ChangeFSMState(GetFSM(), PLAYER_STATE::ATTACK);
			return;
		}
	}

	if (iFrame == m_tAttFrame.first || iFrame == m_tAttFrame.second || iFrame == m_tAttFrame.third)
	{
		Fire(iFrame);
	}

	if (m_fCurTime >= m_fAttackTime)
	{
		ChangeFSMState(GetFSM(), PLAYER_STATE::IDLE);
		InitMulitZeroFrame();
	}

	if (iFrame == -1)
	{
		ChangeFSMState(GetFSM(), PLAYER_STATE::IDLE);
		InitMulitZeroFrame();
	}
}

void CPlayerAttackDown::Exit()
{
	CPlayerState::Exit();
	m_fCurTime = 0;
}

void CPlayerAttackDown::Enter()
{
	InitZeroFrame();
}

void CPlayerAttackDown::InitMulitZeroFrame()
{
	InitZeroFrame();
	GetFSM()->GetPlayer()->GetAnimator()->GetCurAnimation()->SetFram(0);
	GetFSM()->GetPlayer()->GetAnimator()->GetOtherAnimation()->SetFram(0);
}

void CPlayerAttackDown::Fire(UINT _iFireFrame)
{
	if (CPlayerAttack::m_iCurAttFrame != _iFireFrame)
	{
		CPlayer* pPlayer = GetFSM()->GetPlayer();
		CPlayerAttack::m_iCurAttFrame = _iFireFrame;
		if (_iFireFrame == m_tAttFrame.third)
			pPlayer->CreateBullet(pPlayer, ATTACK_TYPE::UPPER);
		else
			pPlayer->CreateBullet(pPlayer);
	}
}

