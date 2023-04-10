#include "pch.h"
#include "SceneTower_3.h"

#include "CResMgr.h"
#include "CTexture.h"

#include "CMonFactory.h"
#include "CMonster.h"
#include "CMonInterface.h"

#include "CGate.h"
#include "CDragonObj.h"
#include "CCrystalPillar.h"

#include "CCollider.h"

#include "CCameraMgr.h"
#include "CColliderMgr.h"
#include "CSkillMgr.h"

#include "CPlayer.h"
#include "CStoneBox.h"


#include "CInventory.h"
#include "CMPItem.h"
#include "CHPItem.h"
#include "CInventoryMgr.h"

#include "CTemWall.h"

#include "CSound.h"

SceneTower_3::SceneTower_3():
	m_eType(SCENE_TYPE::DUNGEON_3)
{

}

SceneTower_3::~SceneTower_3()
{

}

void SceneTower_3::render(HDC _dc)
{
	backgroundrender(_dc, GetBackGround(), Vec2(0.f, 0.f));

	CScene::render(_dc);
}

void SceneTower_3::Init()
{
	CTexture* m_pBackGround = CResMgr::GetInst()->LoadTextur(L"dungeon_3", L"..\\OutPut\\bin_release\\Content\\Tile\\tile_3.bmp");
	SetBackGround(m_pBackGround);

	//배경정보 담고 만들기
	tBackGround tInfo = {};
	tInfo.fRightWidth = m_pBackGround->Width();
	tInfo.fBottomHeight = m_pBackGround->Height() - 180;
	tInfo.fLeftWidth = GetStartDrawPoint().x + 40;
	tInfo.fTopHeight = GetStartDrawPoint().y;
	SetBackGroundInfo(tInfo);

	m_pBackSound
		= CResMgr::GetInst()->LoadSound(L"draconian_tower", L"..\\OutPut\\bin_release\\Content\\Sound\\draconian_tower.wav");

	CObject* pObj = CreatePlayer(Vec2(300.f, 450.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);
	RegisterPlayer(pObj);
	CSkillMgr::GetInst()->SetPlayer((CPlayer*)GetPlayerObj());
	CSkillMgr::GetInst()->init(m_eType);

	CTemWall* pTemWall = new CTemWall;
	pTemWall->SetPos(Vec2(672.f, 110.f));
	pTemWall->GetCollider()->SetScale(Vec2(1344.f, 600.f));
	AddObject(pTemWall, GROUP_TYPE::WALL);

	CCrystalPillar* pCrystal3 = new CCrystalPillar;
	pCrystal3->SetPos(Vec2(70.f, 450.f));
	pCrystal3->GetCollider()->SetScale(Vec2(50.f, 50.f));
	AddObject(pCrystal3, GROUP_TYPE::STONE_BOX);

	CCrystalPillar* pCrystal1 = new CCrystalPillar;
	pCrystal1->SetPos(Vec2(120.f, 450.f));
	pCrystal1->GetCollider()->SetScale(Vec2(50.f, 50.f));
	AddObject(pCrystal1, GROUP_TYPE::STONE_BOX);

	CCrystalPillar* pCrystal2 = new CCrystalPillar;
	pCrystal2->SetPos(Vec2(170.f, 450.f));
	pCrystal2->GetCollider()->SetScale(Vec2(50.f, 50.f));
	AddObject(pCrystal2, GROUP_TYPE::STONE_BOX);

	CMonster* pMon = CMonFactory::CraeteMonster(MON_TYPE::DRAGON, Vec2(500.f, 420.f), m_eType);
	pMon->SetName(L"CDragon_3_1");
	//내 몬스터 인터페이스에 내 몬스터 이름 넣기
	CMonInterface* dragonInterface = new CMonInterface(pMon->GetName(),15);
	dragonInterface->SetScale(Vec2(626, 29));
	dragonInterface->SetPos(Vec2(40, 20));
	AddObject(dragonInterface, GROUP_TYPE::UI);
	AddObject(pMon, GROUP_TYPE::MONSTER);

	CMonster* pBrDragon1 = CMonFactory::CraeteMonster(MON_TYPE::BROWN_DRAGON, Vec2(500.f, 500.f), m_eType);
	pBrDragon1->SetName(L"brDragon_3_1");
	CMonInterface* brdragonInterface2 = new CMonInterface(pBrDragon1->GetName(),44);
	brdragonInterface2->SetScale(Vec2(626, 29));
	brdragonInterface2->SetPos(Vec2(40, 20));
	AddObject(brdragonInterface2, GROUP_TYPE::UI);
	AddObject(pBrDragon1, GROUP_TYPE::MONSTER);


	CMonster* pBrDragon2 = CMonFactory::CraeteMonster(MON_TYPE::BROWN_DRAGON, Vec2(1000.f, 500.f), m_eType);
	pBrDragon2->SetName(L"brDragon_3_2");
	CMonInterface* brdragonInterface1 = new CMonInterface(pBrDragon2->GetName(),44);
	brdragonInterface1->SetScale(Vec2(626, 29));
	brdragonInterface1->SetPos(Vec2(40, 20));
	AddObject(brdragonInterface1, GROUP_TYPE::UI);
	AddObject(pBrDragon2, GROUP_TYPE::MONSTER);

	
	//방향 먼저 잡기
	CGate* pGate = new CGate(L"up", false);
	pGate->SetPos(Vec2(500.f, 365.f));
	pGate->GetCollider()->SetScale(Vec2(70.f, 70.f));
	pGate->SetNextScene(SCENE_TYPE::DUNGEON_4);
	AddObject(pGate, GROUP_TYPE::GATE);
}

void SceneTower_3::Enter()
{
	m_pBackSound->Play(true);


	CCameraMgr::GetInst()->SetTargetObj((CPlayer*)GetPlayerObj()); //vResolution / 2.f
	CCameraMgr::GetInst()->init();
	//현재 씬에 스킬 초기화
	CSkillMgr::GetInst()->SetPlayer((CPlayer*)GetPlayerObj());



	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::STONE_BOX);
	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::ITEM);
	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::GATE);
	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::WALL);
	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::BULLET, GROUP_TYPE::STONE_BOX);
	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::SKILL, GROUP_TYPE::STONE_BOX);
	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::STONE_PILLAR);
	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::SPINNER);
	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::CRYSTAL);
	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::BULLET, GROUP_TYPE::CRYSTAL);
	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::SKILL, GROUP_TYPE::CRYSTAL);
	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER_SKILL);
	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::BULLET, GROUP_TYPE::MONSTER);
	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::SKILL, GROUP_TYPE::MONSTER);
	//CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::MONSTER);
}

void SceneTower_3::Exit()
{
	m_pBackSound->Stop(true);

	CColliderMgr::GetInst()->Reset();
}

void SceneTower_3::update()
{
	CScene::update();
}

