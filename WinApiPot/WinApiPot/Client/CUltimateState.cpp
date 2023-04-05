#include "pch.h"
#include "CUltimateState.h"

#include "CRigidBody.h"
#include "CAnimation.h"
#include "CAnimator.h"

#include "AI.h"
#include "CLord.h"

#include "CThunderDown.h"

#include "CTimeMgr.h"

#include "CResMgr.h"
#include "CSound.h"

CUltimateState::CUltimateState():
	CState(MONSTER_STATE::ULTIMATE),
	m_fRespawnTime(0.7f),
	m_fCurTime(0.f)
{
}

CUltimateState::~CUltimateState()
{
}

void CUltimateState::update()
{
	CMonster* pMon = GetAI()->GetCMonster();

	int iFrame = pMon->GetAnimator()->GetCurAnimation()->GetCurFrame();

	if (iFrame >= 6)
	{
		if (m_fCurTime >= m_fRespawnTime)
		{
			m_fCurTime = 0.f;
			CThunderDown* pThunder = ((CLord*)pMon)->CreateThunderDown();
			CreateObject(pThunder, GROUP_TYPE::MONSTER_SKILL);

			CSound* pThunderSound = CResMgr::GetInst()->LoadSound(L"ThunderS", L"..\\OutPut\\bin_release\\Content\\Sound\\Mon\\zieg_edie.wav");
			pThunderSound->Play(false);
		}
		else
		{
			m_fCurTime += fDT;
		}
	}

	if (iFrame == -1)
	{
		ChangeAIState(GetAI(), MONSTER_STATE::IDLE);
	}


}

void CUltimateState::enter()
{
}

void CUltimateState::exit()
{
	CState::exit();
	GetMonster()->GetAnimator()->GetCurAnimation()->SetFram(0);
	m_fCurTime = 0.f;
}

