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

	//Ű ���궧���� ī���� �����ϰ� �� �� ���� ���� �ε����� ����Ͽ� (���Ϳ� ���� ��� ������ ����) ���� ��������
	//�� ���� ������ �ε������� �Ѱ�ٸ� idle��
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

