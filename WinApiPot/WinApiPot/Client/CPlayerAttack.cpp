#include "pch.h"
#include "CPlayerAttack.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CFSM.h"
#include "CPlayer.h"

#include "CAnimation.h"
#include "CAnimator.h"

#include "CSkillMgr.h"

UINT CPlayerAttack::m_iCurAttFrame = 0;
UINT CPlayerAttack::m_iKeyCount = 0;

CPlayerAttack::CPlayerAttack() :
	CPlayerState(PLAYER_STATE::ATTACK),
	m_fAttackTime(0.1f),
	m_fCurTime(0.f)
{
	m_vecAttMotion.push_back(3); 
	m_vecAttMotion.push_back(5); 
	m_vecAttMotion.push_back(14);
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

	if (KEY_TAP(KEY::X) && m_iKeyCount < 2)
	{
		++m_iKeyCount;
	}

	if (KEY_TAP(KEY::X) || KEY_HOLD(KEY::X))
	{
		m_fCurTime = 0.f;

		if (KEY_HOLD(KEY::DOWN))
		{
			ChangeFSMState(GetFSM(), PLAYER_STATE::ATTACK_DOWN);
			return;
		}
	}


	if (iFrame == m_vecAttMotion[0] || iFrame == m_vecAttMotion[1] || iFrame == m_vecAttMotion[2])
	{
		Fire(iFrame);
	}

	if (m_fCurTime >= m_fAttackTime && iFrame > m_vecAttMotion[m_iKeyCount])
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
	if (CSkillMgr::GetInst()->IsOnSkill())
	{
		InitMulitZeroFrame();
	}
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
	m_iKeyCount = 0;
	m_iCurAttFrame = 0;
	GetFSM()->GetPlayer()->GetAnimator()->GetCurAnimation()->SetFram(0);
	GetFSM()->GetPlayer()->GetAnimator()->GetOtherAnimation()->SetFram(0);
}

void CPlayerAttack::Fire(UINT _iFireFrame)
{
	if (m_iCurAttFrame != _iFireFrame)
	{
		CPlayer* pPlayer = GetFSM()->GetPlayer();
		m_iCurAttFrame = _iFireFrame;
		if(_iFireFrame == m_vecAttMotion[2])
			pPlayer->CreateBullet(pPlayer,ATTACK_TYPE::UPPER);
		else
			pPlayer->CreateBullet(pPlayer);
	}
}
