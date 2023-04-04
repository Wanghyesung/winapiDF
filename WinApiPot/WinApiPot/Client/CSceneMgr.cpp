#include "pch.h"
#include "CSceneMgr.h"

#include "CScene.h"
#include "CScene_Start.h"

#include "CSceneLog.h"
#include "CSeriaScene.h"
#include "CSceneBack.h"
#include "CSceneWest.h"
#include "CSceneTowerFirst.h"
#include "SceneTower_2.h"
#include "SceneTower_3.h"
#include "SceneTower_4.h"
#include "SceneTower5.h"
#include "SceneBoss.h"

#include "CInterfaceMgr.h"

#include "CInventoryMgr.h"

SceneMgr::SceneMgr():
	m_pCurrScene(nullptr),
	m_arrScene{}
{

}

SceneMgr::~SceneMgr()
{
	for (UINT i = 0; i < (UINT)SCENE_TYPE::END; ++i) {
		
		if (nullptr != m_arrScene[i])
		{
			delete m_arrScene[i];
		}
	}
}

CScene* SceneMgr::FindScene(SCENE_TYPE _eSceneType)
{
	if (m_arrScene[(UINT)_eSceneType] != nullptr)
		return m_arrScene[(UINT)_eSceneType];

	return nullptr;
}

void SceneMgr::init()
{
	//씬 배열에 만든 씬들 넣기
	m_arrScene[(UINT)SCENE_TYPE::LOGO_SCENE] = new CSceneLog;
	m_arrScene[(UINT)SCENE_TYPE::START_SCENE] = new CScene_Start;
	//m_arrScene[(UINT)SCENE_TYPE::START_SCENE]->SetName(L"Start Scene");
	m_arrScene[(UINT)SCENE_TYPE::SCENE_BACKSTREET] = new CSceneBack;
	m_arrScene[(UINT)SCENE_TYPE::SERIA_SCENE] = new CSeriaScene;
	m_arrScene[(UINT)SCENE_TYPE::WEST_COAST] = new CSceneWest;
	m_arrScene[(UINT)SCENE_TYPE::FIRST_DUNGEON] = new CSceneTowerFirst;
	m_arrScene[(UINT)SCENE_TYPE::DUNGEON_2] = new  SceneTower_2;
	m_arrScene[(UINT)SCENE_TYPE::DUNGEON_3] = new  SceneTower_3;
	m_arrScene[(UINT)SCENE_TYPE::DUNGEON_4] = new SceneTower_4;
	m_arrScene[(UINT)SCENE_TYPE::DUNGEON_5] = new SceneTower5;
	m_arrScene[(UINT)SCENE_TYPE::DUNGEON_BOSS] = new SceneBoss;

	for (UINT i = 0; i < (UINT)SCENE_TYPE::END; ++i)
	{
		if (m_arrScene[i] == nullptr)
			continue;
		m_arrScene[i]->Init();
	}

	m_pCurrScene = m_arrScene[(UINT)SCENE_TYPE::LOGO_SCENE];//현재 씬 넣어주고
	m_pCurrScene->Enter();
}

void SceneMgr::render(HDC _dc)
{
	m_pCurrScene->render(_dc);
}

void SceneMgr::update()
{
	m_pCurrScene->update();

	m_pCurrScene->finalupdate();
}


void SceneMgr::ChangeScene(SCENE_TYPE _eNext)
{
	//인벤토리, 인터페이스 객체 다른씬으로 옮기기
	m_pCurrScene->Exit();
	CInterFace* pInter = CInterfaceMgr::GetInst()->Exit();
	CInventory* pInven = CInventoryMgr::GetInst()->Exit();

	m_pCurrScene = m_arrScene[(UINT)_eNext];
	//m_pCurrScene->AddObject(vecPlayer[0],GROUP_TYPE::PLAYER);

	m_pCurrScene->Enter();

	if (pInter != nullptr)
		CInterfaceMgr::GetInst()->Enter(pInter);

	if (pInven != nullptr)
		CInventoryMgr::GetInst()->Enter(pInven);
}

