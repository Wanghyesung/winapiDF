#include "pch.h"
#include "CScene_Start.h"
#include "CScene.h"
#include "CObject.h"
#include "CPlayer.h"

#include "CCore.h"

#include "CMonster.h"
#include "CWall.h"
#include "CCollider.h"
#include "CColliderMgr.h"

#include "CResMgr.h"
#include "CTexture.h"

#include "CPortal.h"

#include "CCameraMgr.h"

#include "CMonFactory.h"
#include "CSkillMgr.h"

#include "CInterFace.h"
#include "CHP.h"
#include "CMP.h"

#include "CMonInterface.h"
#include "CHP.h"

#include "CInventoryMgr.h"
#include "CInventory.h"
#include "CHPItem.h"
#include "CMPItem.h"

#include "CSound.h"

CScene_Start::CScene_Start():
	m_eType(SCENE_TYPE::START_SCENE)
{
}

CScene_Start::~CScene_Start()
{
}



void CScene_Start::render(HDC _dc)
{
	//(이거 그냥 부모 Scene에서 상속하게 만들자)
	//여기에 배경을 먼저 그린다
	Vec2 StartPos = Vec2(0.f, 0.f);//그림을 처음에 그릴 위치
	SetStartDrawPoint(StartPos);

	CScene::backgroundrender(_dc, GetBackGround(), StartPos);

	CScene::render(_dc);
}

void CScene_Start::update()
{
	CScene::update();
}

void CScene_Start::Init()
{
	//바탕화면 가져오기
	CTexture* m_pBackGround = CResMgr::GetInst()->LoadTextur(L"BackMap", L"..\\OutPut\\bin_release\\Content\\background\\mainmap.bmp");
	SetBackGround(m_pBackGround);

	//배경정보 담고 만들기
	tBackGround tInfo = {};
	tInfo.fRightWidth = m_pBackGround->Width();
	tInfo.fBottomHeight = m_pBackGround->Height() -110;
	tInfo.fLeftWidth = GetStartDrawPoint().x +40;
	tInfo.fTopHeight = GetStartDrawPoint().y;
	SetBackGroundInfo(tInfo);
	//플레이어 인터페이스는 씬 바꿀때 삭제X
	
	m_pBackSound
		= CResMgr::GetInst()->LoadSound(L"hendonmyre", L"..\\OutPut\\bin_release\\Content\\Sound\\hendonmyre.wav");

	CObject* pObj = CreatePlayer(Vec2(500.f, 550.f));
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

	
	CMonster* pMon = CMonFactory::CraeteMonster(MON_TYPE::KNIGHT_BROWN, Vec2(900.f, 650.f), m_eType);
	pMon->SetName(L"Knight_2");
	//내 몬스터 인터페이스에 내 몬스터 이름 넣기
	CMonInterface* dragonInterface = new CMonInterface(pMon->GetName());
	dragonInterface->SetScale(Vec2(626, 29));
	dragonInterface->SetPos(Vec2(40, 20));
	AddObject(dragonInterface, GROUP_TYPE::UI);
	AddObject(pMon, GROUP_TYPE::MONSTER);
	 
	//CMonster* pMon = CMonFactory::CraeteMonster(MON_TYPE::DRAGON, Vec2(1050.f, 580.f),m_eType);
	//pMon->SetName(L"CDragon_1");
	////내 몬스터 인터페이스에 내 몬스터 이름 넣기
	//CMonInterface* dragonInterface = new CMonInterface(pMon->GetName());
	//dragonInterface->SetScale(Vec2(626, 29));
	//dragonInterface->SetPos(Vec2(40, 20));
	//AddObject(dragonInterface, GROUP_TYPE::UI);
	//AddObject(pMon, GROUP_TYPE::MONSTER);
	//
	//CMonster* pBlue = CMonFactory::CraeteMonster(MON_TYPE::BLUE_DRAGON, Vec2(1400.f, 580.f), m_eType);
	//pBlue->SetName(L"BlueDragon_1");
	//CMonInterface* bdragonInterface = new CMonInterface(pBlue->GetName());
	//bdragonInterface->SetScale(Vec2(626, 29));
	//bdragonInterface->SetPos(Vec2(40, 20));
	//AddObject(bdragonInterface, GROUP_TYPE::UI);
	//AddObject(pBlue, GROUP_TYPE::MONSTER);
	//
	//CMonster* pBlue2 = CMonFactory::CraeteMonster(MON_TYPE::BLUE_DRAGON, Vec2(1200.f, 580.f), m_eType);
	//pBlue2->SetName(L"BlueDragon_2");
	//CMonInterface* bdragonInterface2 = new CMonInterface(pBlue2->GetName());
	//bdragonInterface2->SetScale(Vec2(626, 29));
	//bdragonInterface2->SetPos(Vec2(40, 20));
	//AddObject(bdragonInterface2, GROUP_TYPE::UI);
	//AddObject(pBlue2, GROUP_TYPE::MONSTER);

	CWall* pWall_2 = new CWall;
	pWall_2->SetName(L"Wall_2");
	pWall_2->SetPos(Vec2(2000.f, 320.f));
	pWall_2->GetCollider()->SetScale(Vec2(3160.f, 400.f));
	pWall_2->GetCollider()->SetColliderInfo();
	AddObject(pWall_2, GROUP_TYPE::WALL);

	CWall* pWall_1 = new CWall;
	pWall_1->SetName(L"Wall_1");
	pWall_1->SetPos(Vec2(130.f, 320.f));
	pWall_1->GetCollider()->SetScale(Vec2(255.f, 400.f));
	pWall_1->GetCollider()->SetColliderInfo();//충졸체 크기 정보 저장
	AddObject(pWall_1, GROUP_TYPE::WALL);

	//CPortal* pPortal_1 = new CPortal;
	//pPortal_1->SetName(L"Port_Portal");
	//pPortal_1->SetPos(Vec2(1260.f, 960.f));
	//pPortal_1->SetNextScene(SCENE_TYPE::SCENE_PORT);
	////포탈 크기는 고정으로 생성자에서 만듬
	//AddObject(pPortal_1, GROUP_TYPE::PORTAL);

	CPortal* pPortal_2 = new CPortal;
	pPortal_2->SetName(L"Back_Street_Portal");
	pPortal_2->SetPos(Vec2(333.f, 440.f));
	pPortal_2->GetCollider()->SetScale(Vec2(140.f, 50.f));
	pPortal_2->SetNextScene(SCENE_TYPE::SCENE_BACKSTREET);
	//포탈 크기는 고정으로 생성자에서 만듬
	AddObject(pPortal_2, GROUP_TYPE::PORTAL);

	CPortal* pPortal_3 = new CPortal;
	pPortal_3->SetName(L"Back_Street_Portal");
	pPortal_3->SetPos(Vec2(3550.f, 740.f));
	pPortal_3->GetCollider()->SetScale(Vec2(50.f, 500.f));
	pPortal_3->SetNextScene(SCENE_TYPE::WEST_COAST);
	//포탈 크기는 고정으로 생성자에서 만듬
	AddObject(pPortal_3, GROUP_TYPE::PORTAL);
}

void CScene_Start::Enter()
{
	m_pBackSound->Play(true);
	//매니져 클레스에 현재 플레이어로 세티d
	CCameraMgr::GetInst()->SetTargetObj((CPlayer*)GetPlayerObj()); 
	CCameraMgr::GetInst()->init();
	CSkillMgr::GetInst()->SetPlayer((CPlayer*)GetPlayerObj());
	
	//CInventoryMgr::GetInst()->init();


	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::WALL);
	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::PORTAL);
	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::BULLET, GROUP_TYPE::MONSTER);
	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER_SKILL);
	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::ITEM);
	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::SKILL);

}

void CScene_Start::Exit()
{
	m_pBackSound->Stop(true);
	CColliderMgr::GetInst()->Reset();
}


