#include "pch.h"
#include "CPlayerAttack.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CFSM.h"
#include "CPlayer.h"

#include "CAnimation.h"
#include "CAnimator.h"

UINT CPlayerAttack::m_iCurAttFrame = 0;

CPlayerAttack::CPlayerAttack() :
	CPlayerState(PLAYER_STATE::ATTACK),
	m_fAttackTime(0.2f),
	m_fCurTime(0.f)
{

}

CPlayerAttack::~CPlayerAttack()
{
}

void CPlayerAttack::update()
{
	CFSM* pFSM = GetFSM();
	CPlayer* pPlayer = pFSM->GetPlayer();
	int iFrame = GetCurFrame();

	m_fCurTime += fDT;

	if (KEY_TAP(KEY::X) || KEY_HOLD(KEY::X))
	{
		m_fCurTime = 0.f;

		if (KEY_HOLD(KEY::DOWN))
		{
			ChangeFSMState(GetFSM(), PLAYER_STATE::ATTACK_DOWN);
			return;
		}
	}

	//if (KEY_NONE(KEY::X) &&
	//	IS_HOLD_MOVE_KEY)
	//{
	//	ChangeFSMState(GetFSM(), PLAYER_STATE::WALK);
	//	InitMulitZeroFrame();
	//	return;
	//}


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

void CPlayerAttack::Exit()
{
	CPlayerState::Exit();
	m_fCurTime = 0;
}

void CPlayerAttack::Enter()
{
	InitZeroFrame();
}

void CPlayerAttack::InitMulitZeroFrame()
{
	InitZeroFrame();
	GetFSM()->GetPlayer()->GetAnimator()->GetCurAnimation()->SetFram(0);
	GetFSM()->GetPlayer()->GetAnimator()->GetOtherAnimation()->SetFram(0);
}

void CPlayerAttack::Fire(UINT _iFireFrame)
{
	if (m_iCurAttFrame != _iFireFrame)
	{
		CPlayer* pPlayer = GetFSM()->GetPlayer();
		m_iCurAttFrame = _iFireFrame;
		if(_iFireFrame == m_tAttFrame.third)
			pPlayer->CreateBullet(pPlayer,ATTACK_TYPE::UPPER);
		else
			pPlayer->CreateBullet(pPlayer);
	}
}
