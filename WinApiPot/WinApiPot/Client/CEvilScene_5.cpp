#include "pch.h"
#include "CEvilScene_5.h"

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

#include "CSound.h"

CEvilScene_5::CEvilScene_5() :
	m_eType(SCENE_TYPE::EVIL_SCENE_5)
{

}

CEvilScene_5::~CEvilScene_5()
{

}

void CEvilScene_5::render(HDC _dc)
{
	backgroundrender(_dc, GetBackGround(), Vec2(0.f, 0.f));

	CScene::render(_dc);
}

void CEvilScene_5::Init()
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

	CObject* pObj = CreatePlayer(Vec2(300.f, 450.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);
	RegisterPlayer(pObj);
	CSkillMgr::GetInst()->SetPlayer((CPlayer*)GetPlayerObj());
	CSkillMgr::GetInst()->init(m_eType);

	SetDungeonType(DUNGEON_TYPE::EVIL);

	m_pBackSound
		= CResMgr::GetInst()->LoadSound(L"draconian_tower", L"..\\OutPut\\bin_release\\Content\\Sound\\draconian_tower.wav");

	CTemWall* pTemWall = new CTemWall;
	pTemWall->SetPos(Vec2(672.f, 110.f));
	pTemWall->GetCollider()->SetScale(Vec2(1344.f, 600.f));
	AddObject(pTemWall, GROUP_TYPE::WALL);

	//CreateInterFace();
	//
	//CInventory* pInven = new CInventory;
	//CHPItem* pItemHP = new CHPItem;
	//pInven->AddItem(pItemHP);
	//CMPItem* pItemMP = new CMPItem;
	//pInven->AddItem(pItemMP);
	//
	//AddObject(pInven, GROUP_TYPE::UI);

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


	CMonster* pRedNight_1 = CMonFactory::CraeteMonster(MON_TYPE::KNIGHT_RED, Vec2(500.f, 550.f), m_eType);
	pRedNight_1->SetName(L"redNight_5_1");
	//내 몬스터 인터페이스에 내 몬스터 이름 넣기
	CMonInterface* pRedNightInter = new CMonInterface(pRedNight_1->GetName(), 15);
	pRedNightInter->SetScale(Vec2(626, 29));
	pRedNightInter->SetPos(Vec2(40, 20));
	AddObject(pRedNightInter, GROUP_TYPE::UI);
	AddObject(pRedNight_1, GROUP_TYPE::MONSTER);

	CMonster* pRedNight_2 = CMonFactory::CraeteMonster(MON_TYPE::KNIGHT_RED, Vec2(200.f, 500.f), m_eType);
	pRedNight_2->SetName(L"redNight_5_2");
	CMonInterface* pRedNightInter_2 = new CMonInterface(pRedNight_2->GetName(), 44);
	pRedNightInter_2->SetScale(Vec2(626, 29));
	pRedNightInter_2->SetPos(Vec2(40, 20));
	AddObject(pRedNightInter_2, GROUP_TYPE::UI);
	AddObject(pRedNight_2, GROUP_TYPE::MONSTER);

	CMonster* pRedNight_3 = CMonFactory::CraeteMonster(MON_TYPE::KNIGHT_RED, Vec2(350.f, 500.f), m_eType);
	pRedNight_3->SetName(L"redNight_5_3");
	CMonInterface* pRedNightInter_3 = new CMonInterface(pRedNight_3->GetName(), 45);
	pRedNightInter_3->SetScale(Vec2(626, 29));
	pRedNightInter_3->SetPos(Vec2(40, 20));
	AddObject(pRedNightInter_3, GROUP_TYPE::UI);
	AddObject(pRedNight_3, GROUP_TYPE::MONSTER);


	//방향 먼저 잡기
	CGate* pGate = new CGate(L"up", true);
	pGate->SetPos(Vec2(500.f, 365.f));
	pGate->GetCollider()->SetScale(Vec2(70.f, 70.f));
	pGate->SetNextScene(SCENE_TYPE::EVIL_BOSS);
	AddObject(pGate, GROUP_TYPE::GATE);
}

void CEvilScene_5::InitMonster()
{
	GetPlayerObj()->SetPos(Vec2(300.f, 450.f));

	CMonster* pRedNight_1 = CMonFactory::CraeteMonster(MON_TYPE::KNIGHT_RED, Vec2(500.f, 550.f), m_eType);
	pRedNight_1->SetName(L"redNight_5_1");
	//내 몬스터 인터페이스에 내 몬스터 이름 넣기
	CMonInterface* pRedNightInter = new CMonInterface(pRedNight_1->GetName(), 15);
	pRedNightInter->SetScale(Vec2(626, 29));
	pRedNightInter->SetPos(Vec2(40, 20));
	AddObject(pRedNightInter, GROUP_TYPE::UI);
	AddObject(pRedNight_1, GROUP_TYPE::MONSTER);

	CMonster* pRedNight_2 = CMonFactory::CraeteMonster(MON_TYPE::KNIGHT_RED, Vec2(200.f, 500.f), m_eType);
	pRedNight_2->SetName(L"redNight_5_2");
	CMonInterface* pRedNightInter_2 = new CMonInterface(pRedNight_2->GetName(), 44);
	pRedNightInter_2->SetScale(Vec2(626, 29));
	pRedNightInter_2->SetPos(Vec2(40, 20));
	AddObject(pRedNightInter_2, GROUP_TYPE::UI);
	AddObject(pRedNight_2, GROUP_TYPE::MONSTER);

	CMonster* pRedNight_3 = CMonFactory::CraeteMonster(MON_TYPE::KNIGHT_RED, Vec2(350.f, 500.f), m_eType);
	pRedNight_3->SetName(L"redNight_5_3");
	CMonInterface* pRedNightInter_3 = new CMonInterface(pRedNight_3->GetName(), 45);
	pRedNightInter_3->SetScale(Vec2(626, 29));
	pRedNightInter_3->SetPos(Vec2(40, 20));
	AddObject(pRedNightInter_3, GROUP_TYPE::UI);
	AddObject(pRedNight_3, GROUP_TYPE::MONSTER);
}

void CEvilScene_5::update()
{
	CScene::update();
}

void CEvilScene_5::Enter()
{
	m_pBackSound->Play(true);

	CCameraMgr::GetInst()->SetTargetObj((CPlayer*)GetPlayerObj()); //vResolution / 2.f
	CCameraMgr::GetInst()->init();
	//현재 씬에 스킬 초기화
	CSkillMgr::GetInst()->SetPlayer((CPlayer*)GetPlayerObj());
	//CInventoryMgr::GetInst()->init();

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
	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::DROUP);
	//CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::MONSTER);
}

void CEvilScene_5::Exit()
{
	m_pBackSound->Stop(true);

	CColliderMgr::GetInst()->Reset();
}

