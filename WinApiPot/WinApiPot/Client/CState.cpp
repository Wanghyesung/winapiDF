#include "pch.h"
#include "CState.h"

#include "AI.h"
#include "CMonster.h"

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
	m_AI->SetPreState(this);
}
