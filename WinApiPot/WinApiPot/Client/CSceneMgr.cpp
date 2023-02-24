#include "pch.h"
#include "CSceneMgr.h"

#include "CScene.h"
#include "CScene_Start.h"

#include "CSeriaScene.h"

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

void SceneMgr::init()
{
	//씬 배열에 만든 씬들 넣기
	m_arrScene[(UINT)SCENE_TYPE::START_SCENE] = new CScene_Start;
	//m_arrScene[(UINT)SCENE_TYPE::START_SCENE]->SetName(L"Start Scene");

	m_arrScene[(UINT)SCENE_TYPE::SERIA_SCENE] = new CSeriaScene;
	m_pCurrScene = m_arrScene[(UINT)SCENE_TYPE::START_SCENE];//현재 씬 넣어주고
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
	m_pCurrScene->Exit();
	m_pCurrScene = m_arrScene[(UINT)_eNext];

	m_pCurrScene->Enter();
}

