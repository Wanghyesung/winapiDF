#include "pch.h"
#include "AI.h"

#include "CState.h"
#include "CSceneMgr.h"

#include "CObject.h"
#include "CScene.h"
AI::AI():
	m_pCurState(nullptr),
	m_pOwner(nullptr)
{

}

AI::~AI()
{
	Safe_Delete_Map(m_mapMonState);
}

void AI::update()
{
	if(m_pCurState != nullptr)
		m_pCurState->update();
}

void AI::AddState(CState* _pState)
{
	CState* pState = GetState(_pState->GetType());//중복될 수 있음
	assert(!pState);//중복된 값 안됨 nullptr이 들어와야함

	m_mapMonState.insert(make_pair(_pState->GetType(), _pState));
	_pState->m_AI = this;
}

CState* AI::GetState(MONSTER_STATE _eState)
{
	map<MONSTER_STATE, CState*>::iterator iter;

	iter = m_mapMonState.find(_eState);

	if (iter == m_mapMonState.end())
		return nullptr;

	return iter->second;;
}

void AI::SetCurState(MONSTER_STATE _eState)
{
	m_pCurState = GetState(_eState);
	assert(m_pCurState);
}

void AI::ChangeState(MONSTER_STATE _eNextState)
{
	CState* pNextState = GetState(_eNextState);

	//if (pNextState != m_pCurState)
	//{
	//	m_pCurState->exit();
	//}
	m_pCurState->exit();
	m_pCurState =pNextState;
	m_pCurState->enter();
}



