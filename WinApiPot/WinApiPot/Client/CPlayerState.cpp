#include "pch.h"
#include "CPlayerState.h"

#include "CPlayer.h"
#include "CFSM.h"

#include "CResMgr.h"
#include "CSound.h"

CPlayerState::CPlayerState(PLAYER_STATE ePlayerState) :
	m_ePlayerState(ePlayerState),
	m_pOwner(nullptr)
{

}

CPlayerState::~CPlayerState()
{

}

void CPlayerState::Exit()
{
	GetFSM()->SetPrevState(m_ePlayerState);
}

void CPlayerState::SetAnimSound(const wstring& _strPath)
{
	m_pSound
		= CResMgr::GetInst()->LoadSound(_strPath, L"..\\OutPut\\bin_release\\Content\\Sound\\" + _strPath + L".wav");
}


