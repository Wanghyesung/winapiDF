#include "pch.h"
#include "CPlayerHitUpper.h"

#include "CFSM.h"
#include "CPlayer.h"

#include "CAnimation.h"
#include "CAnimator.h"

#include "CTimeMgr.h"

#include "CGravity.h"
#include "CRigidBody.h"
#include "CPlayerAttack.h"

#include "CSound.h"

#define HIT_MAX_FRAME 4
#define HiT_AIR 3
#define HIT_START 2


CPlayerHitUpper::CPlayerHitUpper() :
	CPlayerState(PLAYER_STATE::UPPER_HIT),
	m_fDonwTime(0.8f)
{
	SetAnimSound(L"gn_dmg");
}

CPlayerHitUpper::~CPlayerHitUpper()
{

}

void CPlayerHitUpper::update()
{
	CFSM* pFSM = GetFSM();
	CPlayer* pPlayer = pFSM->GetPlayer();

	//int iFrame = GetCurFrame();
	wstring strDir = pPlayer->m_iDirX < 0 ? L"_left" : L"_right";
	wstring strMotion = L"Player_Hit" + strDir;
	int iFrame = pPlayer->GetAnimator()->FindAnimation(strMotion)->GetCurFrame();


	if (!pPlayer->GetGravity()->IsGetGravity())
	{
		m_fCurTime += fDT;
		pPlayer->GetAnimator()->FindAnimation(strMotion)->SetFram(4);
	}

	else if (iFrame >= 3)
	{
		pPlayer->GetAnimator()->FindAnimation(strMotion)->SetFram(3);
	}

	if (m_fCurTime >= m_fDonwTime)
	{
		ChangeFSMState(pFSM, PLAYER_STATE::IDLE);
	}

}


void CPlayerHitUpper::Exit()
{
	m_fCurTime = 0.f;
	CPlayerState::Exit();
	InitZeroFrame();
	GetFSM()->GetPlayer()->GetAnimator()->GetCurAnimation()->SetFram(0);
}

void CPlayerHitUpper::Enter()
{
	
	PLAYER_STATE prevState = GetFSM()->GetPlayer()->GetPrevState();
	if (prevState == PLAYER_STATE::ATTACK ||
		prevState == PLAYER_STATE::ATTACK_DOWN)
	{
		((CPlayerAttack*)GetFSM()->FindState(prevState))->InitMulitZeroFrame();
	}

	CPlayer* pPlayer = GetFSM()->GetPlayer();
	pPlayer->GetRigidBody()->SetAccel(false);
	wstring strDir = pPlayer->m_iDirX < 0 ? L"_left" : L"_right";
	if (pPlayer->playerPrevState == PLAYER_STATE::UPPER_HIT)
	{
		pPlayer->GetAnimator()->FindAnimation(L"Player_Hit" + strDir)->SetFram(3);
	}
	else
	{
		pPlayer->GetAnimator()->FindAnimation(L"Player_Hit" + strDir)->SetFram(0);
		GetAnimSound()->Play(false);
	}

}

