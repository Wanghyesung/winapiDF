#include "pch.h"
#include "CEvilScene_1.h"

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

CEvilScene_1::CEvilScene_1():
	m_eType(SCENE_TYPE::EVIL_SCENE_1),
	m_pBackSound(nullptr)
{
}

CEvilScene_1::~CEvilScene_1()
{
}

void CEvilScene_1::Init()
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
	//플레이어 인터페이스는 씬 바꿀때 삭제X

	m_pBackSound
		= CResMgr::GetInst()->LoadSound(L"draconian_tower", L"..\\OutPut\\bin_release\\Content\\Sound\\draconian_tower.wav");

	//1344 790
	CTemWall* pTemWall = new CTemWall;
	pTemWall->SetPos(Vec2(672.f, 110.f));
	pTemWall->GetCollider()->SetScale(Vec2(1644.f, 600.f));
	AddObject(pTemWall, GROUP_TYPE::WALL);

	SetDungeonType(DUNGEON_TYPE::EVIL);

	CObject* pObj = CreatePlayer(Vec2(300.f, 450.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);
	RegisterPlayer(pObj);
	CSkillMgr::GetInst()->SetPlayer((CPlayer*)GetPlayerObj());
	CSkillMgr::GetInst()->init(m_eType);


	CMonster* pBrNight1 = CMonFactory::CraeteMonster(MON_TYPE::KNIGHT_BROWN, Vec2(500.f, 500.f), m_eType);
	pBrNight1->SetName(L"brownNight_1_1");
	CMonInterface* brNightInter = new CMonInterface(pBrNight1->GetName(), 96);
	brNightInter->SetScale(Vec2(626, 29));
	brNightInter->SetPos(Vec2(40, 20));
	AddObject(brNightInter, GROUP_TYPE::UI);
	AddObject(pBrNight1, GROUP_TYPE::MONSTER);


	//방향 먼저 잡기
	CGate* pGate = new CGate(L"up", false);
	pGate->SetPos(Vec2(500.f, 365.f));
	pGate->GetCollider()->SetScale(Vec2(70.f, 70.f));
	pGate->SetNextScene(SCENE_TYPE::EVIL_SCENE_2);
	AddObject(pGate, GROUP_TYPE::GATE);

}

void CEvilScene_1::render(HDC _dc)
{
	Vec2 StartPos = Vec2(0.f, 0.f);//그림을 처음에 그릴 위치
	SetStartDrawPoint(StartPos);

	CScene::backgroundrender(_dc, GetBackGround(), StartPos);

	CScene::render(_dc);
}

void CEvilScene_1::Enter()
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
}

void CEvilScene_1::Exit()
{
	m_pBackSound->Stop(true);

	CColliderMgr::GetInst()->Reset();
}


