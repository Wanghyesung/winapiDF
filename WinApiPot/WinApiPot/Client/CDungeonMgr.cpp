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


void CDungeonMgr::SetActive(SCENE_TYPE _eSceneType, bool _bActive)
{
	m_vecClearUI[(UINT)_eSceneType]->m_bActive = _bActive;
	m_eCurScene = _eSceneType;
}


void CDungeonMgr::init()
{
	m_vecClearUI.resize((UINT)SCENE_TYPE::END);
	
	CClearUI* pClear1 = new CClearUI;
	pClear1->init();
	m_vecClearUI[(UINT)SCENE_TYPE::DUNGEON_BOSS] = pClear1;
	SceneMgr::GetInst()->FindScene(SCENE_TYPE::DUNGEON_BOSS)->AddObject(pClear1, GROUP_TYPE::UI);

	CClearUI* pClear2 = new CClearUI;
	pClear2->init();
	m_vecClearUI[(UINT)SCENE_TYPE::EVIL_BOSS] = pClear2;
	SceneMgr::GetInst()->FindScene(SCENE_TYPE::EVIL_BOSS)->AddObject(pClear2, GROUP_TYPE::UI);

	//CClearUI* pClear3 = new CClearUI;
	//pClear3->init();
	//m_vecClearUI[(UINT)SCENE_TYPE::SERIA_SCENE] = pClear3;
	//SceneMgr::GetInst()->FindScene(SCENE_TYPE::SERIA_SCENE)->AddObject(pClear3, GROUP_TYPE::UI);
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

	reinit();

	if (m_eCurDunType == DUNGEON_TYPE::LORD)
		ChangeScene(SCENE_TYPE::FIRST_DUNGEON);
	else if(m_eCurDunType == DUNGEON_TYPE::EVIL)
		ChangeScene(SCENE_TYPE::EVIL_SCENE_1);

}

void CDungeonMgr::exit_dungeon()
{
	SetActive(m_eCurScene, false);
	//Scene에 있는 reInit호출하고 마을로
	reinit();

	m_eCurDunType = DUNGEON_TYPE::NONE;

	ChangeScene(SCENE_TYPE::WEST_COAST);
}

void CDungeonMgr::change_dungeon()
{
	// Scene에 있는 reInit호출하고 현재씬 활성 X

	SetActive(m_eCurScene, false);

	reinit();

	m_eCurDunType = DUNGEON_TYPE::NONE;

	ChangeScene(SCENE_TYPE::SELECT_SCENE);
}

void CDungeonMgr::reinit()
{
	const vector<CScene*>& vecDunScene = SceneMgr::GetInst()->GetDungeonType(m_eCurDunType);
	for (int i = 0; i < vecDunScene.size(); ++i)
	{
		vecDunScene[i]->InitMonster();
	}
}
