#include "pch.h"
#include "CPlayerState.h"

#include "CPlayer.h"
#include "CFSM.h"
CPlayerState::CPlayerState(PLAYER_STATE ePlayerState):
	m_ePlayerState(ePlayerState)
{

}

CPlayerState::~CPlayerState()
{

}

void CPlayerState::Exit()
{
	GetFSM()->SetPrevState(m_ePlayerState);
}


