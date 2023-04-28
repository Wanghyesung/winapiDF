#include "pch.h"
#include "CEvilBossScene.h"

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
#include "CDungeonMgr.h"

#include "CSceneMgr.h"
#include "CDungeonMgr.h"

#include "CTemWall.h"

#include "CEvileye.h"

#include "CSound.h"

CEvilBossScene::CEvilBossScene() :
	m_eType(SCENE_TYPE::EVIL_BOSS)
{
}

CEvilBossScene::~CEvilBossScene()
{

}

void CEvilBossScene::render(HDC _dc)
{
	backgroundrender(_dc, GetBackGround(), Vec2(0.f, 0.f));

	CScene::render(_dc);
}

void CEvilBossScene::Init()
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
		= CResMgr::GetInst()->LoadSound(L"boss_", L"..\\OutPut\\bin_release\\Content\\Sound\\boss.wav");

	SetDungeonType(DUNGEON_TYPE::EVIL);

	CObject* pObj = CreatePlayer(Vec2(300.f, 450.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);
	RegisterPlayer(pObj);
	CSkillMgr::GetInst()->SetPlayer((CPlayer*)GetPlayerObj());
	CSkillMgr::GetInst()->init(m_eType);


	CTemWall* pTemWall = new CTemWall;
	pTemWall->SetPos(Vec2(672.f, 110.f));
	pTemWall->GetCollider()->SetScale(Vec2(1644.f, 600.f));
	AddObject(pTemWall, GROUP_TYPE::WALL);


	CMonster* pEvil2 = CMonFactory::CraeteMonster(MON_TYPE::EVILEYE, Vec2(1200.f, 500.f), m_eType);
	pEvil2->SetName(L"evil_2");
	((CEvileye*)(pEvil2))->SetDir(-1);
	CMonInterface* pEvilInter2 = new CMonInterface(pEvil2->GetName(), 99, true);
	pEvilInter2->SetScale(Vec2(626, 29));
	pEvilInter2->SetPos(Vec2(40, 20));
	AddObject(pEvilInter2, GROUP_TYPE::UI);
	AddObject(pEvil2, GROUP_TYPE::MONSTER);

	CMonster* pEvil = CMonFactory::CraeteMonster(MON_TYPE::EVILEYE, Vec2(100.f, 500.f), m_eType);
	pEvil->SetName(L"evil_1");
	((CEvileye*)(pEvil))->SetDir(1);
	CMonInterface* pEvilInter = new CMonInterface(pEvil->GetName(), 99, true);
	pEvilInter->SetScale(Vec2(626, 29));
	pEvilInter->SetPos(Vec2(40, 20));
	AddObject(pEvilInter, GROUP_TYPE::UI);
	AddObject(pEvil, GROUP_TYPE::MONSTER);

	//CMonster* pLord = CMonFactory::CraeteMonster(MON_TYPE::LORD, Vec2(600.f, 300.f), m_eType);
	//pLord->SetName(L"Lord");
	//CMonInterface* pLordInterface = new CMonInterface(pLord->GetName(), 46, true);
	//pLordInterface->SetScale(Vec2(626, 29));
	//pLordInterface->SetPos(Vec2(40, 20));
	//AddObject(pLordInterface, GROUP_TYPE::UI);
	//AddObject(pLord, GROUP_TYPE::MONSTER);


	


	//방향 먼저 잡기
	//CGate* pGate = new CGate(L"up");
	//pGate->SetPos(Vec2(500.f, 365.f));
	//pGate->GetCollider()->SetScale(Vec2(70.f, 70.f));
	//pGate->SetNextScene(SCENE_TYPE::DUNGEON_BOSS);
	//AddObject(pGate, GROUP_TYPE::GATE);
}

void CEvilBossScene::InitMonster()
{
	GetPlayerObj()->SetPos(Vec2(300.f, 450.f));

	CMonster* pEvil2 = CMonFactory::CraeteMonster(MON_TYPE::EVILEYE, Vec2(1200.f, 500.f), m_eType);
	pEvil2->SetName(L"evil_2");
	((CEvileye*)(pEvil2))->SetDir(-1);
	CMonInterface* pEvilInter2 = new CMonInterface(pEvil2->GetName(), 99, true);
	pEvilInter2->SetScale(Vec2(626, 29));
	pEvilInter2->SetPos(Vec2(40, 20));
	AddObject(pEvilInter2, GROUP_TYPE::UI);
	AddObject(pEvil2, GROUP_TYPE::MONSTER);

	CMonster* pEvil = CMonFactory::CraeteMonster(MON_TYPE::EVILEYE, Vec2(100.f, 500.f), m_eType);
	pEvil->SetName(L"evil_1");
	((CEvileye*)(pEvil))->SetDir(1);
	CMonInterface* pEvilInter = new CMonInterface(pEvil->GetName(), 99, true);
	pEvilInter->SetScale(Vec2(626, 29));
	pEvilInter->SetPos(Vec2(40, 20));
	AddObject(pEvilInter, GROUP_TYPE::UI);
	AddObject(pEvil, GROUP_TYPE::MONSTER);
}

void CEvilBossScene::update()
{
	CScene::update();

	if (SceneMgr::GetInst()->GetCurSCene()->GetGroupObject(GROUP_TYPE::MONSTER).size() == 0)
	{
		CDungeonMgr::GetInst()->SetActive(m_eType, true);
	}
}

void CEvilBossScene::Enter()
{
	m_pBackSound->Play(true);

	//CDungeonMgr::GetInst()->SetActive(m_eType, true);

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
	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::ROBOT);
}

void CEvilBossScene::Exit()
{
	m_pBackSound->Stop(true);

	CColliderMgr::GetInst()->Reset();
}
