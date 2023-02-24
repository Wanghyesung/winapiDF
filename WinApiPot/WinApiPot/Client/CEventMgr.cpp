#include "pch.h"
#include "CEventMgr.h"

#include "CObject.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "AI.h"
#include "CFSM.h"
#include "CState.h"


CEventMgr::CEventMgr()
{

}

CEventMgr::~CEventMgr()
{

}

//이벤트 매니저는 항상 매 프레임 마지막에 실행
void CEventMgr::update()
{
	if (m_vecEvent.empty() && m_vecDead.empty())
		return;

	for (int i = 0; i < m_vecDead.size(); ++i)
	{
		delete m_vecDead[i];
	}
	m_vecDead.clear();


	for (int i = 0; i < m_vecEvent.size(); ++i)
	{
		Excute(m_vecEvent[i]);
	}
	m_vecEvent.clear();
}

void CEventMgr::Excute(const tEvent& _eve)
{
	switch (_eve.eEventType)
	{
	case EVENT_TYPE::CREATE_OBJECT:
	{
		CObject* pObj = (CObject*)_eve.lParm;
		GROUP_TYPE eGroup = (GROUP_TYPE)_eve.wParm;

		SceneMgr::GetInst()->GetCurSCene()->AddObject(pObj, eGroup);
	}
	break;

	case EVENT_TYPE::DELETE_OBJECT:
	{
		CObject* pObj = (CObject*)_eve.lParm;
		pObj->setDead();
		m_vecDead.push_back(pObj);
	}
	break;

	case EVENT_TYPE::SCENE_CHANGE:
	{
		SCENE_TYPE eSCeneType = (SCENE_TYPE)_eve.lParm;

		SceneMgr::GetInst()->ChangeScene(eSCeneType);
	}
	break;

	case EVENT_TYPE::CHANGE_AI_STATE:
	{
		AI* mAI = (AI*)_eve.lParm;
		MONSTER_STATE monState = (MONSTER_STATE)_eve.wParm;
		mAI->ChangeState(monState);
	}
	break;

	case EVENT_TYPE::CHANGE_FSM_STATE:
	{
		CFSM* mFSM = (CFSM*)_eve.lParm;
		PLAYER_STATE playerState = (PLAYER_STATE)_eve.wParm;
		mFSM->ChangeState(playerState);
	}
	break;



	}
}
