#include "pch.h"
#include "CDungeonMgr.h"

#include "CMonster.h"

#include "CClearUI.h"
#include "CSceneMgr.h"
#include "CScene.h"

CDungeonMgr::CDungeonMgr()
{

}
CDungeonMgr::~CDungeonMgr()
{

}


void CDungeonMgr::init()
{
	m_vecClearUI.resize((UINT)SCENE_TYPE::END);
	//어느 씬에 넣을지 결정
	CClearUI* pClear1 = new CClearUI;
	pClear1->init();
	m_vecClearUI[(UINT)SCENE_TYPE::EVIL_BOSS] = pClear1;
	SceneMgr::GetInst()->FindScene(SCENE_TYPE::EVIL_BOSS)->AddObject(pClear1, GROUP_TYPE::UI);


	//CClearUI* pClear2 = new CClearUI;
	//pClear2->init();
	//m_vecClearUI[(UINT)SCENE_TYPE::SERIA_SCENE] = pClear2;
	//SceneMgr::GetInst()->FindScene(SCENE_TYPE::WEST_COAST)->AddObject(pClear2, GROUP_TYPE::UI);
}

void CDungeonMgr::map_clear()
{
	vector<CObject*> vecMon = SceneMgr::GetInst()->GetCurSCene()->GetGroupObject(GROUP_TYPE::MONSTER);
	if (vecMon.size() == 0)
		return;

	for (int i = 0; i < vecMon.size(); ++i)
	{
		ChangeAIState(((CMonster*)vecMon[i])->m_AI, MONSTER_STATE::DEAD);
	}
}


void CDungeonMgr::restart_scene()
{
	//Scene에 있는 reInit호출하고 다시 처음 던전으로
	SetActive(m_eCurScene, false);
}

void CDungeonMgr::exit_dungeon()
{
	SetActive(m_eCurScene, false);
	//Scene에 있는 reInit호출하고 마을로
}

void CDungeonMgr::change_dungeon()
{
	// Scene에 있는 reInit호출하고 현재씬 활성 X
	SetActive(m_eCurScene, false);

	ChangeScene(SCENE_TYPE::SELECT_SCENE);
}
