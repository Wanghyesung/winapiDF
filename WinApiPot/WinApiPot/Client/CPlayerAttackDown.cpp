#include "pch.h"
#include "CPlayerAttackDown.h"

#include "CFSM.h"
#include "CPlayer.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CPlayerAttack.h"
#include "CAnimation.h"
#include "CAnimator.h"

#include "CSkillMgr.h"



CPlayerAttackDown::CPlayerAttackDown():
	CPlayerState(PLAYER_STATE::ATTACK_DOWN),
	m_fAttackTime(0.1f),
	m_fCurTime(0.f)
{
	m_vecAttMotion.push_back(3);
	m_vecAttMotion.push_back(5);
	m_vecAttMotion.push_back(14);
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

	if (KEY_TAP(KEY::X) && CPlayerAttack::m_iKeyCount < 2)
	{
		++CPlayerAttack::m_iKeyCount;
	}

	//키 누룰때마다 카운터 증가하고 그 그 값을 벡터 인덱스로 사용하여 (벡터에 공격 모션 프레임 넣음) 현재 프레임이
	//내 현재 벡터의 인덱스값을 넘겼다면 idle로
	if (KEY_TAP(KEY::X) || KEY_HOLD(KEY::X))
	{
		m_fCurTime = 0.f;

		if (KEY_NONE(KEY::DOWN))
		{
			ChangeFSMState(GetFSM(), PLAYER_STATE::ATTACK);
			return;
		}
	}

	if (iFrame == m_vecAttMotion[0] || iFrame == m_vecAttMotion[1] || iFrame == m_vecAttMotion[2])
	{
		Fire(iFrame);
	}

	if (m_fCurTime >= m_fAttackTime &&iFrame > m_vecAttMotion[CPlayerAttack::m_iKeyCount])
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
	if (CSkillMgr::GetInst()->IsOnSkill())
	{
		InitMulitZeroFrame();
	}

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
	CPlayerAttack::m_iKeyCount = 0;
	CPlayerAttack::m_iCurAttFrame = 0;
	GetFSM()->GetPlayer()->GetAnimator()->GetCurAnimation()->SetFram(0);
	GetFSM()->GetPlayer()->GetAnimator()->GetOtherAnimation()->SetFram(0);
}

void CPlayerAttackDown::Fire(UINT _iFireFrame)
{
	if (CPlayerAttack::m_iCurAttFrame != _iFireFrame)
	{
		CPlayer* pPlayer = GetFSM()->GetPlayer();
		CPlayerAttack::m_iCurAttFrame = _iFireFrame;
		if (_iFireFrame == m_vecAttMotion[2])
			pPlayer->CreateBullet(pPlayer, ATTACK_TYPE::UPPER);
		else
			pPlayer->CreateBullet(pPlayer);
	}
}

