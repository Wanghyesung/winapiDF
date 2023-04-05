#include "pch.h"
#include "CState.h"

#include "AI.h"
#include "CMonster.h"

#include "CResMgr.h"
#include "CSound.h"

CState::CState(MONSTER_STATE m_eMonState) :
	m_AI(nullptr),
	m_eMonState(m_eMonState),
	m_iDir(-1)
{
}

CState::~CState()
{
}

CMonster* CState::GetMonster()
{
	return m_AI->GetCMonster();
}

void CState::exit()
{
	CSound* pSound = GetAnimSound();
	if (pSound != nullptr)
	{
		pSound->Stop(true);
	}

	m_AI->SetPreState(this);
}

void CState::SetAnimSound(const wstring& _strPath)
{
	m_pAnimSound
		= CResMgr::GetInst()->LoadSound(_strPath, L"..\\OutPut\\bin_release\\Content\\Sound\\Mon\\" + _strPath + L".wav");
}
