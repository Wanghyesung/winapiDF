#include "pch.h"
#include "CSceneWest.h"

#include "CResMgr.h"
#include "CTexture.h"

#include "CObject.h"
#include "CPlayer.h"

#include "CMonster.h"
#include "CMonFactory.h"
#include "CMonInterface.h"

#include "CSkillMgr.h"
#include "CColliderMgr.h"
#include "CCameraMgr.h"
#include "CPortal.h"
#include "CCollider.h"

#include "CInventoryMgr.h"
#include "CInventory.h"

#include "CInterFace.h"

#include "CHPItem.h"
#include "CMPItem.h"
#include "CItemObject.h"

#include "CTemWall.h"

#include "CPillar.h"

CSceneWest::CSceneWest():
	m_eType(SCENE_TYPE::WEST_COAST)
{
}

CSceneWest::~CSceneWest()
{
}

void CSceneWest::render(HDC _dc)
{
	Vec2 StartPos = Vec2(0.f, 0.f);//그림을 처음에 그릴 위치
	SetStartDrawPoint(StartPos);

	CScene::backgroundrender(_dc, GetBackGround(), StartPos);

	CScene::render(_dc);
}

void CSceneWest::update()
{
	CScene::update();
}
void CSceneWest::Init()
{
	CTexture* m_pBackGround = CResMgr::GetInst()->LoadTextur(L"west", L"..\\OutPut\\bin_release\\Content\\background\\WestCoast.bmp");
	SetBackGround(m_pBackGround);

	//배경정보 담고 만들기
	tBackGround tInfo = {};
	tInfo.fRightWidth = m_pBackGround->Width();
	tInfo.fBottomHeight = m_pBackGround->Height() - 95.f;
	tInfo.fLeftWidth = GetStartDrawPoint().x;
	tInfo.fTopHeight = GetStartDrawPoint().y;
	SetBackGroundInfo(tInfo);
	//플레이어 인터페이스는 씬 바꿀때 삭제X
	

	CObject* pObj = CreatePlayer(Vec2(450.f, 650.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);
	RegisterPlayer(pObj);
	CSkillMgr::GetInst()->SetPlayer((CPlayer*)GetPlayerObj());
	CSkillMgr::GetInst()->init(m_eType);

	CMonster* pMon = CMonFactory::CraeteMonster(MON_TYPE::KNIGHT_RED, Vec2(900.f, 650.f), m_eType);
	pMon->SetName(L"Knight_1");
	//내 몬스터 인터페이스에 내 몬스터 이름 넣기
	CMonInterface* dragonInterface = new CMonInterface(pMon->GetName());
	dragonInterface->SetScale(Vec2(626, 29));
	dragonInterface->SetPos(Vec2(40, 20));
	AddObject(dragonInterface, GROUP_TYPE::UI);
	AddObject(pMon, GROUP_TYPE::MONSTER);


	CreateInterFace();
	
	CInventory* pInven = new CInventory;
	CHPItem* pItemHP = new CHPItem;
	pInven->AddItem(pItemHP);
	CMPItem* pItemMP = new CMPItem;
	pInven->AddItem(pItemMP);
	
	AddObject(pInven, GROUP_TYPE::UI);

	CTemWall* pTemWall = new CTemWall;
	pTemWall->SetPos(Vec2(1232.f, 160.f));
	pTemWall->GetCollider()->SetScale(Vec2(2464.f, 600.f));
	AddObject(pTemWall, GROUP_TYPE::WALL);


	CPortal* pPortal_1 = new CPortal;
	pPortal_1->SetName(L"Port_Portal");
	pPortal_1->SetPos(Vec2(2450.f, 650.f));
	pPortal_1->GetCollider()->SetScale(Vec2(50.f, 200.f));
	pPortal_1->SetNextScene(SCENE_TYPE::FIRST_DUNGEON);
	//포탈 크기는 고정으로 생성자에서 만듬
	AddObject(pPortal_1, GROUP_TYPE::PORTAL);


	CPortal* pPortal_2 = new CPortal;
	pPortal_2->SetName(L"Port_Porta2");
	pPortal_2->SetPos(Vec2(20.f, 650.f));
	pPortal_2->GetCollider()->SetScale(Vec2(50.f, 400.f));
	pPortal_2->SetNextScene(SCENE_TYPE::START_SCENE);
	//포탈 크기는 고정으로 생성자에서 만듬
	AddObject(pPortal_2, GROUP_TYPE::PORTAL);

}

void CSceneWest::Enter()
{
	CCameraMgr::GetInst()->SetTargetObj((CPlayer*)GetPlayerObj()); //vResolution / 2.f
	CCameraMgr::GetInst()->init();
	//현재 씬에 스킬 초기화
	CSkillMgr::GetInst()->SetPlayer((CPlayer*)GetPlayerObj());

	CInventoryMgr::GetInst()->init();

	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER_SKILL);
	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::BULLET, GROUP_TYPE::MONSTER);
	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::SKILL, GROUP_TYPE::MONSTER);
	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::PORTAL);
	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::WALL);
	
}

void CSceneWest::Exit()
{
	CColliderMgr::GetInst()->Reset();
}

