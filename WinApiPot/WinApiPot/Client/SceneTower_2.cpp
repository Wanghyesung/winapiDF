#include "pch.h"
#include "SceneTower_2.h"

#include "CResMgr.h"
#include "CTexture.h"

#include "CMonFactory.h"
#include "CMonster.h"
#include "CMonInterface.h"

#include "CGate.h"

#include "CCollider.h"

#include "CCameraMgr.h"
#include "CColliderMgr.h"
#include "CSkillMgr.h"

#include "CPlayer.h"
#include "CStoneBox.h"

#include "CTemWall.h"

#include "CSound.h"

SceneTower_2::SceneTower_2():
	m_eType(SCENE_TYPE::DUNGEON_2)
{

}

SceneTower_2::~SceneTower_2()
{

}

void SceneTower_2::Init()
{
	CTexture* m_pBackGround = CResMgr::GetInst()->LoadTextur(L"dungeon_2", L"..\\OutPut\\bin_release\\Content\\Tile\\tile_2.bmp");
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

	SetDungeonType(DUNGEON_TYPE::LORD);

	CObject* pObj = CreatePlayer(Vec2(300.f, 450.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);
	RegisterPlayer(pObj);
	CSkillMgr::GetInst()->SetPlayer((CPlayer*)GetPlayerObj());
	CSkillMgr::GetInst()->init(m_eType);

	CTemWall* pTemWall = new CTemWall;
	pTemWall->SetPos(Vec2(672.f, 110.f));
	pTemWall->GetCollider()->SetScale(Vec2(1344.f, 600.f));
	AddObject(pTemWall, GROUP_TYPE::WALL);

	CStoneBox* pStone = new CStoneBox;
	pStone->SetPos(Vec2(170.f, 450.f));
	pStone->GetCollider()->SetScale(Vec2(50.f, 50.f));
	AddObject(pStone, GROUP_TYPE::STONE_BOX);

	CStoneBox* pStone2 = new CStoneBox;
	pStone2->SetPos(Vec2(100.f, 450.f));
	pStone2->GetCollider()->SetScale(Vec2(50.f, 50.f));
	AddObject(pStone2, GROUP_TYPE::STONE_BOX);

	CStoneBox* pStone3 = new CStoneBox;
	pStone3->SetPos(Vec2(30.f, 450.f));
	pStone3->GetCollider()->SetScale(Vec2(50.f, 50.f));
	AddObject(pStone3, GROUP_TYPE::STONE_BOX);

	CMonster* pBrDragon1 = CMonFactory::CraeteMonster(MON_TYPE::BROWN_DRAGON, Vec2(500.f, 500.f), m_eType);
	pBrDragon1->SetName(L"brDragon1");
	CMonInterface* brdragonInterface2 = new CMonInterface(pBrDragon1->GetName(),44);
	brdragonInterface2->SetScale(Vec2(626, 29));
	brdragonInterface2->SetPos(Vec2(40, 20));
	AddObject(brdragonInterface2, GROUP_TYPE::UI);
	AddObject(pBrDragon1, GROUP_TYPE::MONSTER);


	CMonster* pBrDragon2 = CMonFactory::CraeteMonster(MON_TYPE::BROWN_DRAGON, Vec2(1000.f, 500.f), m_eType);
	pBrDragon2->SetName(L"brDragon2");
	CMonInterface* brdragonInterface1 = new CMonInterface(pBrDragon2->GetName(),44);
	brdragonInterface1->SetScale(Vec2(626, 29));
	brdragonInterface1->SetPos(Vec2(40, 20));
	AddObject(brdragonInterface1, GROUP_TYPE::UI);
	AddObject(pBrDragon2, GROUP_TYPE::MONSTER);

	//방향 먼저 잡기
	CGate* pGate = new CGate(L"up", false);
	pGate->SetPos(Vec2(500.f, 365.f));
	pGate->GetCollider()->SetScale(Vec2(70.f, 70.f));
	pGate->SetNextScene(SCENE_TYPE::DUNGEON_3);
	AddObject(pGate, GROUP_TYPE::GATE);


}

void SceneTower_2::InitMonster()
{
	GetPlayerObj()->SetPos(Vec2(300.f, 450.f));

	CMonster* pBrDragon1 = CMonFactory::CraeteMonster(MON_TYPE::BROWN_DRAGON, Vec2(500.f, 500.f), m_eType);
	pBrDragon1->SetName(L"brDragon1");
	CMonInterface* brdragonInterface2 = new CMonInterface(pBrDragon1->GetName(), 44);
	brdragonInterface2->SetScale(Vec2(626, 29));
	brdragonInterface2->SetPos(Vec2(40, 20));
	AddObject(brdragonInterface2, GROUP_TYPE::UI);
	AddObject(pBrDragon1, GROUP_TYPE::MONSTER);


	CMonster* pBrDragon2 = CMonFactory::CraeteMonster(MON_TYPE::BROWN_DRAGON, Vec2(1000.f, 500.f), m_eType);
	pBrDragon2->SetName(L"brDragon2");
	CMonInterface* brdragonInterface1 = new CMonInterface(pBrDragon2->GetName(), 44);
	brdragonInterface1->SetScale(Vec2(626, 29));
	brdragonInterface1->SetPos(Vec2(40, 20));
	AddObject(brdragonInterface1, GROUP_TYPE::UI);
	AddObject(pBrDragon2, GROUP_TYPE::MONSTER);
}

void SceneTower_2::render(HDC _dc)
{
	backgroundrender(_dc, GetBackGround(), Vec2(0.f, 0.f));

	CScene::render(_dc);
}

void SceneTower_2::update()
{
	CScene::update();
}

void SceneTower_2::Enter()
{
	m_pBackSound->Play(true);

	CCameraMgr::GetInst()->SetTargetObj((CPlayer*)GetPlayerObj());
	CCameraMgr::GetInst()->init();
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
	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::ROBOT);
	//CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::MONSTER);
}

void SceneTower_2::Exit()
{
	m_pBackSound->Stop(true);

	CColliderMgr::GetInst()->Reset();
}


