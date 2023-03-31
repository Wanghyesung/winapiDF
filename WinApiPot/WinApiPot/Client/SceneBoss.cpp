#include "pch.h"
#include "SceneBoss.h"

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
#include "CSpinner.h"

#include "CInventory.h"
#include "CMPItem.h"
#include "CHPItem.h"
#include "CInventoryMgr.h"

#include "CTemWall.h"

SceneBoss::SceneBoss():
	m_eType(SCENE_TYPE::DUNGEON_BOSS)
{
}

SceneBoss::~SceneBoss()
{

}

void SceneBoss::render(HDC _dc)
{
	backgroundrender(_dc, GetBackGround(), Vec2(0.f, 0.f));

	CScene::render(_dc);
}

void SceneBoss::Init()
{
	CTexture* m_pBackGround = CResMgr::GetInst()->LoadTextur(L"dungeon_boss", L"..\\OutPut\\bin_release\\Content\\Tile\\boss_map.bmp");
	SetBackGround(m_pBackGround);

	//배경정보 담고 만들기
	tBackGround tInfo = {};
	tInfo.fRightWidth = m_pBackGround->Width();
	tInfo.fBottomHeight = m_pBackGround->Height() - 180;
	tInfo.fLeftWidth = GetStartDrawPoint().x + 40;
	tInfo.fTopHeight = GetStartDrawPoint().y;
	SetBackGroundInfo(tInfo);

	CObject* pObj = CreatePlayer(Vec2(300.f, 450.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);
	RegisterPlayer(pObj);
	CSkillMgr::GetInst()->SetPlayer((CPlayer*)GetPlayerObj());
	CSkillMgr::GetInst()->init(m_eType);

	CTemWall* pTemWall = new CTemWall;
	pTemWall->SetPos(Vec2(672.f, 110.f));
	pTemWall->GetCollider()->SetScale(Vec2(1344.f, 600.f));
	AddObject(pTemWall, GROUP_TYPE::WALL);

	CDragonObj* pStone2 = new CDragonObj;
	pStone2->SetPos(Vec2(30.f, 500.f));
	pStone2->GetCollider()->SetScale(Vec2(50.f, 50.f));
	AddObject(pStone2, GROUP_TYPE::STONE_BOX);

	CDragonObj* pStone3 = new CDragonObj;
	pStone3->SetPos(Vec2(30.f, 800.f));
	pStone3->GetCollider()->SetScale(Vec2(50.f, 50.f));
	AddObject(pStone3, GROUP_TYPE::STONE_BOX);

	CDragonObj* pStone4 = new CDragonObj;
	pStone4->SetPos(Vec2(30.f, 650.f));
	pStone4->GetCollider()->SetScale(Vec2(50.f, 50.f));
	AddObject(pStone4, GROUP_TYPE::STONE_BOX);

	CSpinner* pSpinner = new CSpinner;
	pSpinner->SetPos(Vec2(900.f, 500.f));
	pSpinner->GetCollider()->SetOffSet(Vec2(0.f, 50.f));
	pSpinner->GetCollider()->SetScale(Vec2(50.f, 110.f));
	AddObject(pSpinner, GROUP_TYPE::SPINNER);

	CSpinner* pSpinner2 = new CSpinner;
	pSpinner2->SetPos(Vec2(200.f, 500.f));
	pSpinner2->GetCollider()->SetOffSet(Vec2(0.f, 50.f));
	pSpinner2->GetCollider()->SetScale(Vec2(50.f, 110.f));
	AddObject(pSpinner2, GROUP_TYPE::SPINNER);

	CMonster* pLord = CMonFactory::CraeteMonster(MON_TYPE::LORD, Vec2(600.f, 300.f), m_eType);
	pLord->SetName(L"Lord");
	CMonInterface* pLordInterface = new CMonInterface(pLord->GetName(), true);
	pLordInterface->SetScale(Vec2(626, 29));
	pLordInterface->SetPos(Vec2(40, 20));
	AddObject(pLordInterface, GROUP_TYPE::UI);
	AddObject(pLord, GROUP_TYPE::MONSTER);


	CMonster* pDragon1 = CMonFactory::CraeteMonster(MON_TYPE::DRAGON, Vec2(500.f, 550.f), m_eType);
	pDragon1->SetName(L"CDragon_b_1");
	//내 몬스터 인터페이스에 내 몬스터 이름 넣기
	CMonInterface* dragonInterface1 = new CMonInterface(pDragon1->GetName());
	dragonInterface1->SetScale(Vec2(626, 29));
	dragonInterface1->SetPos(Vec2(40, 20));
	AddObject(dragonInterface1, GROUP_TYPE::UI);
	AddObject(pDragon1, GROUP_TYPE::MONSTER);

	CMonster* pBrDragon1 = CMonFactory::CraeteMonster(MON_TYPE::BROWN_DRAGON, Vec2(200.f, 500.f), m_eType);
	pBrDragon1->SetName(L"brDragon_b_1");
	CMonInterface* brdragonInterface2 = new CMonInterface(pBrDragon1->GetName());
	brdragonInterface2->SetScale(Vec2(626, 29));
	brdragonInterface2->SetPos(Vec2(40, 20));
	AddObject(brdragonInterface2, GROUP_TYPE::UI);
	AddObject(pBrDragon1, GROUP_TYPE::MONSTER);

	CMonster* pBDragon2 = CMonFactory::CraeteMonster(MON_TYPE::BLUE_DRAGON, Vec2(350.f, 500.f), m_eType);
	pBDragon2->SetName(L"bDragonb_1");
	CMonInterface* brdragonInterface3 = new CMonInterface(pBDragon2->GetName());
	brdragonInterface3->SetScale(Vec2(626, 29));
	brdragonInterface3->SetPos(Vec2(40, 20));
	AddObject(brdragonInterface3, GROUP_TYPE::UI);
	AddObject(pBDragon2, GROUP_TYPE::MONSTER);


	//방향 먼저 잡기
	//CGate* pGate = new CGate(L"up");
	//pGate->SetPos(Vec2(500.f, 365.f));
	//pGate->GetCollider()->SetScale(Vec2(70.f, 70.f));
	//pGate->SetNextScene(SCENE_TYPE::DUNGEON_BOSS);
	//AddObject(pGate, GROUP_TYPE::GATE);
}

void SceneBoss::update()
{
	CScene::update();
}

void SceneBoss::Enter()
{
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
}

void SceneBoss::Exit()
{
	CColliderMgr::GetInst()->Reset();
}


