#include "pch.h"
#include "CSceneMgr.h"

#include "CScene.h"
#include "CScene_Start.h"

#include "CSeriaScene.h"
#include "CSceneBack.h"
#include "CSceneWest.h"
#include "CSceneTowerFirst.h"

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
	m_arrScene[(UINT)SCENE_TYPE::START_SCENE] = new CScene_Start;
	//m_arrScene[(UINT)SCENE_TYPE::START_SCENE]->SetName(L"Start Scene");
	m_arrScene[(UINT)SCENE_TYPE::SCENE_BACKSTREET] = new CSceneBack;
	m_arrScene[(UINT)SCENE_TYPE::SERIA_SCENE] = new CSeriaScene;
	m_arrScene[(UINT)SCENE_TYPE::WEST_COAST] = new CSceneWest;
	m_arrScene[(UINT)SCENE_TYPE::FIRST_DUNGEON] = new CSceneTowerFirst;


	for (UINT i = 0; i < (UINT)SCENE_TYPE::END; ++i)
	{
		if (m_arrScene[i] == nullptr)
			continue;
		m_arrScene[i]->Init();
	}

	m_pCurrScene = m_arrScene[(UINT)SCENE_TYPE::FIRST_DUNGEON];//현재 씬 넣어주고
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
	//플레이어만 가져오기
	//vector<CObject*> vecPlayer = m_pCurrScene->GetGroupObject(GROUP_TYPE::PLAYER);
	m_pCurrScene->Exit();

	m_pCurrScene = m_arrScene[(UINT)_eNext];
	//m_pCurrScene->AddObject(vecPlayer[0],GROUP_TYPE::PLAYER);

	m_pCurrScene->Enter();
}

