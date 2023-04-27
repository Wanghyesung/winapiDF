#include "pch.h"
#include "CEvilScene_4.h"

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

CEvilScene_4::CEvilScene_4() :
	m_eType(SCENE_TYPE::EVIL_SCENE_4)
{
}

CEvilScene_4::~CEvilScene_4()
{
}

void CEvilScene_4::Init()
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

	CObject* pObj = CreatePlayer(Vec2(300.f, 450.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);
	RegisterPlayer(pObj);
	CSkillMgr::GetInst()->SetPlayer((CPlayer*)GetPlayerObj());
	CSkillMgr::GetInst()->init(m_eType);

	SetDungeonType(DUNGEON_TYPE::EVIL);

	CTemWall* pTemWall = new CTemWall;
	pTemWall->SetPos(Vec2(672.f, 110.f));
	pTemWall->GetCollider()->SetScale(Vec2(1344.f, 600.f));
	AddObject(pTemWall, GROUP_TYPE::WALL);

	CDragonObj* pStone = new CDragonObj;
	pStone->SetPos(Vec2(30.f, 450.f));
	pStone->GetCollider()->SetScale(Vec2(50.f, 50.f));
	AddObject(pStone, GROUP_TYPE::STONE_BOX);

	CDragonObj* pStone3 = new CDragonObj;
	pStone3->SetPos(Vec2(30.f, 550.f));
	pStone3->GetCollider()->SetScale(Vec2(50.f, 50.f));
	AddObject(pStone3, GROUP_TYPE::STONE_BOX);

	CMonster* pArdor = CMonFactory::CraeteMonster(MON_TYPE::ARDOR, Vec2(500.f, 500.f), m_eType);
	pArdor->SetName(L"ardor_4_1");
	CMonInterface* pArdorInter = new CMonInterface(pArdor->GetName(), 67);
	pArdorInter->SetScale(Vec2(626, 29));
	pArdorInter->SetPos(Vec2(40, 20));
	AddObject(pArdorInter, GROUP_TYPE::UI);
	AddObject(pArdor, GROUP_TYPE::MONSTER);

	CMonster* pNaias_1 = CMonFactory::CraeteMonster(MON_TYPE::NAIAS, Vec2(500.f, 550.f), m_eType);
	pNaias_1->SetName(L"naias_4_1");
	//내 몬스터 인터페이스에 내 몬스터 이름 넣기
	CMonInterface* pNaiasInter = new CMonInterface(pNaias_1->GetName(), 68);
	pNaiasInter->SetScale(Vec2(626, 29));
	pNaiasInter->SetPos(Vec2(40, 20));
	AddObject(pNaiasInter, GROUP_TYPE::UI);
	AddObject(pNaias_1, GROUP_TYPE::MONSTER);

	CMonster* pNaias_2 = CMonFactory::CraeteMonster(MON_TYPE::NAIAS, Vec2(800.f, 440.f), m_eType);
	pNaias_2->SetName(L"naias_4_2");
	//내 몬스터 인터페이스에 내 몬스터 이름 넣기
	CMonInterface* pNaiasInter_2 = new CMonInterface(pNaias_2->GetName(), 68);
	pNaiasInter_2->SetScale(Vec2(626, 29));
	pNaiasInter_2->SetPos(Vec2(40, 20));
	AddObject(pNaiasInter_2, GROUP_TYPE::UI);
	AddObject(pNaias_2, GROUP_TYPE::MONSTER);

	//방향 먼저 잡기
	CGate* pGate = new CGate(L"up", false);
	pGate->SetPos(Vec2(500.f, 365.f));
	pGate->GetCollider()->SetScale(Vec2(70.f, 70.f));
	pGate->SetNextScene(SCENE_TYPE::EVIL_SCENE_5);
	AddObject(pGate, GROUP_TYPE::GATE);
}

void CEvilScene_4::render(HDC _dc)
{
	backgroundrender(_dc, GetBackGround(), Vec2(0.f, 0.f));

	CScene::render(_dc);
}

void CEvilScene_4::update()
{
	CScene::update();
}

void CEvilScene_4::Enter()
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

void CEvilScene_4::Exit()
{
	m_pBackSound->Stop(true);

	CColliderMgr::GetInst()->Reset();
}
