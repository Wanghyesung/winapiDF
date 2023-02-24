#include "pch.h"
#include "CFSM.h"

#include "CPlayer.h"
#include "CPlayerState.h"

CFSM::CFSM():
	m_mapState{},
	m_pCurState(nullptr),
	m_eCurState(PLAYER_STATE::IDLE)
{

}

CFSM::~CFSM()
{
	Safe_Delete_Map(m_mapState);
}

void CFSM::update()
{
	if (m_pCurState != nullptr)
	{
		m_pCurState->update();
	}
}

void CFSM::AddState(CPlayerState* _pState)
{
	CPlayerState* pState = FindState(_pState->GetType());
	//중복 금지
	assert(!pState);

	m_mapState.insert(make_pair(_pState->GetType(), _pState));
	_pState->m_pOwner = this;
}

CPlayerState* CFSM::FindState(PLAYER_STATE _ePlayerState)
{
	map<PLAYER_STATE, CPlayerState*>::iterator iter = m_mapState.find(_ePlayerState);

	if (iter == m_mapState.end())
	{
		return nullptr;
	}

	return iter->second;
}

void CFSM::ChangeState(PLAYER_STATE _ePlayerState)
{	
	CPlayerState* pNextState = FindState(_ePlayerState);
	//assert(pNextState != m_pCurState); //같은 state면 리턴

	if (pNextState != m_pCurState)
	{
		m_pCurState->Exit();
	}
	SetCurState(_ePlayerState);
	m_pCurState->Enter();

}

void CFSM::SetCurState(PLAYER_STATE _ePlayerState)
{
	m_ePreState = m_eCurState;
	m_pCurState = FindState(_ePlayerState);
	m_eCurState = m_pCurState->GetType();
	assert(m_pCurState);
}

PLAYER_STATE CFSM::GetPrevState()
{
	return m_pOwner->GetPrevState();
}

void CFSM::SetPrevState(PLAYER_STATE _ePrevState)
{
	m_pOwner->SetPrevState(_ePrevState);
}
