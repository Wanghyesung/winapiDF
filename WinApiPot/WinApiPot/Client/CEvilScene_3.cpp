#include "pch.h"
#include "CEvilScene_3.h"

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

CEvilScene_3::CEvilScene_3() :
	m_eType(SCENE_TYPE::EVIL_SCENE_3)
{

}

CEvilScene_3::~CEvilScene_3()
{

}

void CEvilScene_3::render(HDC _dc)
{
	backgroundrender(_dc, GetBackGround(), Vec2(0.f, 0.f));

	CScene::render(_dc);
}

void CEvilScene_3::Init()
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

	SetDungeonType(DUNGEON_TYPE::EVIL);

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

	CMonster* pGrNight1 = CMonFactory::CraeteMonster(MON_TYPE::KNIGHT_GREEN, Vec2(500.f, 420.f), m_eType);
	pGrNight1->SetName(L"grNight_3_1");
	//내 몬스터 인터페이스에 내 몬스터 이름 넣기
	CMonInterface* pGrNightInter = new CMonInterface(pGrNight1->GetName(), 97);
	pGrNightInter->SetScale(Vec2(626, 29));
	pGrNightInter->SetPos(Vec2(40, 20));
	AddObject(pGrNightInter, GROUP_TYPE::UI);
	AddObject(pGrNight1, GROUP_TYPE::MONSTER);

	CMonster* pGrNight2 = CMonFactory::CraeteMonster(MON_TYPE::KNIGHT_GREEN, Vec2(500.f, 500.f), m_eType);
	pGrNight2->SetName(L"grNight_3_2");
	CMonInterface* pGrNightInter2 = new CMonInterface(pGrNight2->GetName(), 97);
	pGrNightInter2->SetScale(Vec2(626, 29));
	pGrNightInter2->SetPos(Vec2(40, 20));
	AddObject(pGrNightInter2, GROUP_TYPE::UI);
	AddObject(pGrNight2, GROUP_TYPE::MONSTER);


	CMonster* pGrNight3 = CMonFactory::CraeteMonster(MON_TYPE::KNIGHT_GREEN, Vec2(1000.f, 500.f), m_eType);
	pGrNight3->SetName(L"grNight_3_3");
	CMonInterface* pGrNightInter3 = new CMonInterface(pGrNight3->GetName(), 97);
	pGrNightInter3->SetScale(Vec2(626, 29));
	pGrNightInter3->SetPos(Vec2(40, 20));
	AddObject(pGrNightInter3, GROUP_TYPE::UI);
	AddObject(pGrNight3, GROUP_TYPE::MONSTER);


	//방향 먼저 잡기
	CGate* pGate = new CGate(L"up", false);
	pGate->SetPos(Vec2(500.f, 365.f));
	pGate->GetCollider()->SetScale(Vec2(70.f, 70.f));
	pGate->SetNextScene(SCENE_TYPE::EVIL_SCENE_4);
	AddObject(pGate, GROUP_TYPE::GATE);
}

void CEvilScene_3::InitMonster()
{
	GetPlayerObj()->SetPos(Vec2(300.f, 450.f));

	CMonster* pGrNight1 = CMonFactory::CraeteMonster(MON_TYPE::KNIGHT_GREEN, Vec2(500.f, 420.f), m_eType);
	pGrNight1->SetName(L"grNight_3_1");
	//내 몬스터 인터페이스에 내 몬스터 이름 넣기
	CMonInterface* pGrNightInter = new CMonInterface(pGrNight1->GetName(), 97);
	pGrNightInter->SetScale(Vec2(626, 29));
	pGrNightInter->SetPos(Vec2(40, 20));
	AddObject(pGrNightInter, GROUP_TYPE::UI);
	AddObject(pGrNight1, GROUP_TYPE::MONSTER);

	CMonster* pGrNight2 = CMonFactory::CraeteMonster(MON_TYPE::KNIGHT_GREEN, Vec2(500.f, 500.f), m_eType);
	pGrNight2->SetName(L"grNight_3_2");
	CMonInterface* pGrNightInter2 = new CMonInterface(pGrNight2->GetName(), 97);
	pGrNightInter2->SetScale(Vec2(626, 29));
	pGrNightInter2->SetPos(Vec2(40, 20));
	AddObject(pGrNightInter2, GROUP_TYPE::UI);
	AddObject(pGrNight2, GROUP_TYPE::MONSTER);


	CMonster* pGrNight3 = CMonFactory::CraeteMonster(MON_TYPE::KNIGHT_GREEN, Vec2(1000.f, 500.f), m_eType);
	pGrNight3->SetName(L"grNight_3_3");
	CMonInterface* pGrNightInter3 = new CMonInterface(pGrNight3->GetName(), 97);
	pGrNightInter3->SetScale(Vec2(626, 29));
	pGrNightInter3->SetPos(Vec2(40, 20));
	AddObject(pGrNightInter3, GROUP_TYPE::UI);
	AddObject(pGrNight3, GROUP_TYPE::MONSTER);
}

void CEvilScene_3::Enter()
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

void CEvilScene_3::Exit()
{
	m_pBackSound->Stop(true);

	CColliderMgr::GetInst()->Reset();
}

void CEvilScene_3::update()
{
	CScene::update();
}

