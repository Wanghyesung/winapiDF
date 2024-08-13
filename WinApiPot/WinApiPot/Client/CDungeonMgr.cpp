#include "pch.h"
#include "CDungeonMgr.h"

#include "CMonster.h"

#include "CClearUI.h"
#include "CSceneMgr.h"
#include "CScene.h"

#include "CPlayer.h"

#include "CResMgr.h"
#include "CTexture.h"

CDungeonMgr::CDungeonMgr() :
	m_eCurDunType(DUNGEON_TYPE::NONE),
	m_vecVisited{},
	m_bRenderOn(false),
	m_vIconPos(Vec2(1115.f, 204.f)),
	m_vCurPos(Vec2(0.f, 0.f))
{
	m_pPlayerIconTex = CResMgr::GetInst()->LoadTextur(L"playerIcon", L"..\\OutPut\\bin_release\\Content\\Minimap\\player.bmp");
	m_pBossIconTex = CResMgr::GetInst()->LoadTextur(L"bossIcon", L"..\\OutPut\\bin_release\\Content\\Minimap\\boss.bmp");
	m_pMiniMapTex = CResMgr::GetInst()->LoadTextur(L"Minimap", L"..\\OutPut\\bin_release\\Content\\Minimap\\minmap.bmp");
	m_pLineTex = CResMgr::GetInst()->LoadTextur(L"up_1", L"..\\OutPut\\bin_release\\Content\\Minimap\\up_1.bmp");
	m_pLineLastTex = CResMgr::GetInst()->LoadTextur(L"up1", L"..\\OutPut\\bin_release\\Content\\Minimap\\up1.bmp");
	m_pminMap_ = CResMgr::GetInst()->LoadTextur(L"minimapLight", L"..\\OutPut\\bin_release\\Content\\Minimap\\minmap_.bmp");
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
	pClear1->Create();
	m_vecClearUI[(UINT)SCENE_TYPE::DUNGEON_BOSS] = pClear1;
	SceneMgr::GetInst()->FindScene(SCENE_TYPE::DUNGEON_BOSS)->AddObject(pClear1, GROUP_TYPE::UI);

	CClearUI* pClear2 = new CClearUI;
	pClear2->Create();
	m_vecClearUI[(UINT)SCENE_TYPE::EVIL_BOSS] = pClear2;
	SceneMgr::GetInst()->FindScene(SCENE_TYPE::EVIL_BOSS)->AddObject(pClear2, GROUP_TYPE::UI);
}

void CDungeonMgr::init_map()
{
	//던전 들어가고 맵 확인
	m_bRenderOn = true;
	m_vIconPos = Vec2(1115.f, 204.f);
	const vector<CScene*> vecDun =  SceneMgr::GetInst()->GetDungeonType(m_eCurDunType);
	m_vecVisited.resize(vecDun.size());
	m_vecVisited[0] = 1;
	m_vCurPos = Vec2(0.f, 0.f);
	for (int i = 1; i<m_vecVisited.size(); ++i)
	{
		m_vecVisited[i] = 0;
	}
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

void CDungeonMgr::render(HDC _dc)
{
	if (!m_bRenderOn)
		return;

	Vec2 vPos = Vec2(1100.f, 100.f);

	TransparentBlt(_dc,
		(int)(vPos.x),
		(int)(vPos.y),
		(int)(m_pMiniMapTex->Width()),
		(int)(m_pMiniMapTex->Height()),
		m_pMiniMapTex->GetDC(),
		(int)0,
		(int)0,
		(int)(m_pMiniMapTex->Width()),
		(int)(m_pMiniMapTex->Height()),
		RGB(255, 255, 255));

	
	//길 render
	Vec2 vStartPos = Vec2(1106.f, 177.f);
	for (int i = 1; i< m_vecVisited.size() - 1; ++i)
	{
		if (m_vecVisited[i] == 1)
		{
			TransparentBlt(_dc,
				(int)(vStartPos.x),
				(int)(vStartPos.y),
				(int)(m_pLineTex->Width()),
				(int)(m_pLineTex->Height()),
				m_pLineTex->GetDC(),
				(int)0,
				(int)0,
				(int)(m_pLineTex->Width()),
				(int)(m_pLineTex->Height()),
				RGB(255, 255, 255));
		}
		vStartPos.y -= 18.f;
	}

	if (m_vecVisited[m_vecVisited.size() - 1] == 1)
	{
		TransparentBlt(_dc,
			(int)(vStartPos.x),
			(int)(vStartPos.y),
			(int)(m_pLineLastTex->Width()),
			(int)(m_pLineLastTex->Height()),
			m_pLineLastTex->GetDC(),
			(int)0,
			(int)0,
			(int)(m_pLineLastTex->Width()),
			(int)(m_pLineLastTex->Height()),
			RGB(255, 255, 255));
	}

	//플레이어 
	TransparentBlt(_dc,
		(int)(m_vIconPos.x - m_pPlayerIconTex->Width() / 2.f),
		(int)(m_vIconPos.y - m_pPlayerIconTex->Height() / 2.f),
		(int)(m_pPlayerIconTex->Width()),
		(int)(m_pPlayerIconTex->Height()),
		m_pPlayerIconTex->GetDC(),
		(int)0,
		(int)0,
		(int)(m_pPlayerIconTex->Width()),
		(int)(m_pPlayerIconTex->Height()),
		RGB(255, 255, 255));
	//보스
	TransparentBlt(_dc,
		(int)(1115 - m_pBossIconTex->Width()/2),
		(int)(113 - m_pBossIconTex->Height()/2),
		(int)(m_pBossIconTex->Width()),
		(int)(m_pBossIconTex->Height()),
		m_pBossIconTex->GetDC(),
		(int)0,
		(int)0,
		(int)(m_pBossIconTex->Width()),
		(int)(m_pBossIconTex->Height()),
		RGB(255, 255, 255));

}


void CDungeonMgr::restart_scene()
{
	//Scene에 있는 reInit호출하고 다시 처음 던전으로
	reinit();

	//init_map();

	SetActive(m_eCurScene, false);

	CObject* pPlayer = SceneMgr::GetInst()->GetCurSCene()->GetPlayerObj();
	((CPlayer*)pPlayer)->resetvalue();


	if (m_eCurDunType == DUNGEON_TYPE::LORD)
		ChangeScene(SCENE_TYPE::FIRST_DUNGEON);
	else if(m_eCurDunType == DUNGEON_TYPE::EVIL)
		ChangeScene(SCENE_TYPE::EVIL_SCENE_1);

}

void CDungeonMgr::exit_dungeon()
{
	reinit();

	m_bRenderOn = false;
	SetActive(m_eCurScene, false);
	//Scene에 있는 reInit호출하고 마을로

	CObject* pPlayer = SceneMgr::GetInst()->GetCurSCene()->GetPlayerObj();
	((CPlayer*)pPlayer)->resetvalue();

	m_eCurDunType = DUNGEON_TYPE::NONE;

	ChangeScene(SCENE_TYPE::WEST_COAST);
}

void CDungeonMgr::change_dungeon()
{
	// Scene에 있는 reInit호출하고 현재씬 활성 X
	
	reinit();

	m_bRenderOn = false;
	SetActive(m_eCurScene, false);

	CObject* pPlayer = SceneMgr::GetInst()->GetCurSCene()->GetPlayerObj();
	((CPlayer*)pPlayer)->resetvalue();


	m_eCurDunType = DUNGEON_TYPE::NONE;

	ChangeScene(SCENE_TYPE::SELECT_SCENE);
}

void CDungeonMgr::reinit()
{
	SceneMgr::GetInst()->reinit(m_eCurDunType);
}

void CDungeonMgr::move_icon(Vec2 _vDir)
{
	m_vIconPos += Vec2(0.f, 18.f * _vDir.y);
	m_vCurPos.y -= _vDir.y;

	for (int i = 1; i < m_vecVisited.size(); ++i)
	{
		if (m_vCurPos.y == i)
		{
			m_vecVisited[i] = 1;
		}
	}
}
