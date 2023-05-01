#include "pch.h"
#include "CSceneTowerFirst.h"

#include "CCameraMgr.h"
#include "CSkillMgr.h"
#include "CColliderMgr.h"
#include "CCollider.h"

#include "CPlayer.h"
#include "CObject.h"
#include "CMonster.h"

#include "CBrDragon.h"
#include "CEvileye.h"
#include "CInterFace.h"
#include "CMonFactory.h"
#include "CMonInterface.h"
#include "CMonHP.h"

#include "CResMgr.h"
#include "CTexture.h"

#include "CPortal.h"
#include "CStoneBox.h"
#include "CPillar.h"
#include "CSpinner.h"
#include "CGate.h"
#include "CCrystalPillar.h"
#include "CDragonObj.h"
#include "CThunder.h"

#include "CTemWall.h"

#include "CInventoryMgr.h"
#include "CInventory.h"
#include "CHPItem.h"
#include "CMPItem.h"

#include "CSound.h"

CSceneTowerFirst::CSceneTowerFirst():
	m_eType(SCENE_TYPE::FIRST_DUNGEON)
{
	
}

CSceneTowerFirst::~CSceneTowerFirst()
{

}

void CSceneTowerFirst::Init()
{
	CTexture* m_pBackGround = CResMgr::GetInst()->LoadTextur(L"dungeon_first", L"..\\OutPut\\bin_release\\Content\\Tile\\tile_1.bmp");
	SetBackGround(m_pBackGround);

	//배경정보 담고 만들기
	tBackGround tInfo = {};
	tInfo.fRightWidth = m_pBackGround->Width();
	tInfo.fBottomHeight = m_pBackGround->Height() - 180;
	tInfo.fLeftWidth = GetStartDrawPoint().x + 40;
	tInfo.fTopHeight = GetStartDrawPoint().y;
	SetBackGroundInfo(tInfo);
	//플레이어 인터페이스는 씬 바꿀때 삭제X
	
	m_pBackSound
		= CResMgr::GetInst()->LoadSound(L"draconian_tower", L"..\\OutPut\\bin_release\\Content\\Sound\\draconian_tower.wav");

	SetDungeonType(DUNGEON_TYPE::LORD);

	//1344 790
	CTemWall* pTemWall = new CTemWall;
	pTemWall->SetPos(Vec2(672.f, 110.f));
	pTemWall->GetCollider()->SetScale(Vec2(1344.f, 600.f));
	AddObject(pTemWall, GROUP_TYPE::WALL);


	CObject* pObj = CreatePlayer(Vec2(300.f, 450.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);
	RegisterPlayer(pObj);
	CSkillMgr::GetInst()->SetPlayer((CPlayer*)GetPlayerObj());
	CSkillMgr::GetInst()->init(m_eType);

	//CreateInterFace();
	//
	//CInventory* pInven = new CInventory;
	//CHPItem* pItemHP = new CHPItem;
	//pInven->AddItem(pItemHP);
	//CMPItem* pItemMP = new CMPItem;
	//pInven->AddItem(pItemMP);
	//
	//AddObject(pInven, GROUP_TYPE::UI);

	CStoneBox* pStone = new CStoneBox;
	pStone->SetPos(Vec2(150.f, 450.f));
	pStone->GetCollider()->SetScale(Vec2(50.f, 50.f));
	AddObject(pStone, GROUP_TYPE::STONE_BOX);
	
	//CPillar* pPillar = new CPillar;
	//pPillar->SetPos(Vec2(700.f, 700.f));
	//pPillar->GetCollider()->SetOffSet(Vec2(0.f, 50.f));
	//pPillar->GetCollider()->SetScale(Vec2(50.f, 50.f));
	//AddObject(pPillar, GROUP_TYPE::STONE_PILLAR);
	//
	//
	//CSpinner* pSpinner = new CSpinner;
	//pSpinner->SetPos(Vec2(1000.f, 700.f));
	//pSpinner->GetCollider()->SetOffSet(Vec2(0.f, 50.f));
	//pSpinner->GetCollider()->SetScale(Vec2(50.f, 110.f));
	//AddObject(pSpinner, GROUP_TYPE::SPINNER);

	//CMonster* pLord = CMonFactory::CraeteMonster(MON_TYPE::LORD, Vec2(1200.f, 580.f), m_eType);
	//pLord->SetName(L"Lord");
	//CMonInterface* pLordInterface = new CMonInterface(pLord->GetName(),true);
	//pLordInterface->SetScale(Vec2(626, 29));
	//pLordInterface->SetPos(Vec2(40, 20));
	//AddObject(pLordInterface, GROUP_TYPE::UI);
	//AddObject(pLord, GROUP_TYPE::MONSTER);

	CMonster* pBDragon1 = CMonFactory::CraeteMonster(MON_TYPE::BLUE_DRAGON, Vec2(500.f, 500.f), m_eType);
	pBDragon1->SetName(L"bDragon1");
	CMonInterface* brdragonInterface2 = new CMonInterface(pBDragon1->GetName(),45);
	brdragonInterface2->SetScale(Vec2(626, 29));
	brdragonInterface2->SetPos(Vec2(40, 20));
	AddObject(brdragonInterface2, GROUP_TYPE::UI);
	AddObject(pBDragon1, GROUP_TYPE::MONSTER);
	
	
	//CMonster* pBDragon2 = CMonFactory::CraeteMonster(MON_TYPE::EVILEYE, Vec2(200.f, 500.f), m_eType);
	//pBDragon2->SetName(L"evil_1");
	//CMonInterface* brdragonInterface1 = new CMonInterface(pBDragon2->GetName(), 99, true);
	//brdragonInterface1->SetScale(Vec2(626, 29));
	//brdragonInterface1->SetPos(Vec2(40, 20));
	//AddObject(brdragonInterface1, GROUP_TYPE::UI);
	//AddObject(pBDragon2, GROUP_TYPE::MONSTER);
	//

	//방향 먼저 잡기
	CGate* pGate = new CGate(L"up", false);
	pGate->SetPos(Vec2(500.f, 365.f));
	pGate->GetCollider()->SetScale(Vec2(70.f, 70.f));
	pGate->SetNextScene(SCENE_TYPE::DUNGEON_2);
	AddObject(pGate, GROUP_TYPE::GATE);
	
	////크기는 생성장에서
	//CCrystalPillar* pCryStal = new CCrystalPillar;
	//pCryStal->SetPos(Vec2(500.f, 500.f));
	//AddObject(pCryStal, GROUP_TYPE::STONE_BOX);
	//
	//CDragonObj* pDragonObj = new CDragonObj;
	//pDragonObj->SetPos(Vec2(200.f, 600.f));
	//AddObject(pDragonObj, GROUP_TYPE::STONE_BOX);

	//CPortal* pPortal_1 = new CPortal;
	//pPortal_1->SetName(L"Port_Portal");
	//pPortal_1->SetPos(Vec2(300.f, 850.f));
	//pPortal_1->SetNextScene(SCENE_TYPE::START_SCENE);
	////포탈 크기는 고정으로 생성자에서 만듬
	//AddObject(pPortal_1, GROUP_TYPE::PORTAL);

}

void CSceneTowerFirst::InitMonster()
{
	GetPlayerObj()->SetPos(Vec2(300.f, 450.f));
	
	CMonster* pBDragon1 = CMonFactory::CraeteMonster(MON_TYPE::BLUE_DRAGON, Vec2(500.f, 500.f), m_eType);
	pBDragon1->SetName(L"bDragon1");
	CMonInterface* brdragonInterface2 = new CMonInterface(pBDragon1->GetName(), 45);
	brdragonInterface2->SetScale(Vec2(626, 29));
	brdragonInterface2->SetPos(Vec2(40, 20));
	AddObject(brdragonInterface2, GROUP_TYPE::UI);
	AddObject(pBDragon1, GROUP_TYPE::MONSTER);
}

void CSceneTowerFirst::render(HDC _dc)
{
	Vec2 StartPos = Vec2(0.f, 0.f);//그림을 처음에 그릴 위치
	SetStartDrawPoint(StartPos);

	CScene::backgroundrender(_dc, GetBackGround(), StartPos);

	CScene::render(_dc);
}

void CSceneTowerFirst::update()
{
	CScene::update();
}

void CSceneTowerFirst::Enter()
{
	m_pBackSound->Play(true);

	//키 누른 횟수 초기화
	((CPlayer*)GetPlayerObj())->InitKeyStack();

	CCameraMgr::GetInst()->SetTargetObj((CPlayer*)GetPlayerObj()); //vResolution / 2.f
	CCameraMgr::GetInst()->init();
	//현재 씬에 스킬 초기화
	CSkillMgr::GetInst()->SetPlayer((CPlayer*)GetPlayerObj());

	//CInventoryMgr::GetInst()->init();

	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::STONE_BOX);
	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::ITEM);
	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::GATE);
	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::WALL);
	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::WALL);
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
	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::DROUP);
	//CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::MONSTER);
}

void CSceneTowerFirst::Exit()
{
	m_pBackSound->Stop(true);

	CColliderMgr::GetInst()->Reset();
}


