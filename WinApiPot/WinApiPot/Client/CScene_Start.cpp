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

CScene_Start::CScene_Start()
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

void CScene_Start::Enter()
{
	//바탕화면 가져오기
	CTexture* m_pBackGround = CResMgr::GetInst()->LoadTextur(L"BackMap", L"background//mainmap.bmp");
	SetBackGround(m_pBackGround);

	//배경정보 담고 만들기
	tBackGround tInfo = {}; 
	tInfo.fRightWidth =  m_pBackGround->Width();
	tInfo.fBottomHeight = m_pBackGround->Height() - 110; 
	tInfo.fLeftWidth = GetStartDrawPoint().x + 40;
	tInfo.fTopHeight = GetStartDrawPoint().y; 

	SetBackGroundInfo(tInfo);

	CObject* pObj = CreatePlayer(Vec2(700.f, 550.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);
	
	RegisterPlayer(pObj);
	CCameraMgr::GetInst()->SetTargetObj(pObj); //vResolution / 2.f
	CSkillMgr::GetInst()->SetPlayer((CPlayer*)pObj);
	

	
	CMonster* pMon = CMonFactory::CraeteMonster(MON_TYPE::DRAGON, Vec2(1050.f, 580.f));
	pMon->SetName(L"CDragon");
	AddObject(pMon, GROUP_TYPE::MONSTER);

	CWall* pWall_2 = new CWall;
	pWall_2->SetName(L"Wall_2");
	pWall_2->SetPos(Vec2(2000.f, 320.f));
	pWall_2->GetCollider()->SetScale(Vec2(3160.f, 400.f));
	pWall_2->GetCollider()->SetColliderInfo();
	AddObject(pWall_2, GROUP_TYPE::WALL);

	CWall* pWall_1 = new CWall;
	pWall_1->SetName(L"Wall_1");
	pWall_1->SetPos(Vec2(130.f, 320.f));
	pWall_1->GetCollider()->SetScale(Vec2(255.f,400.f));
	pWall_1->GetCollider()->SetColliderInfo();//충졸체 크기 정보 저장
	AddObject(pWall_1, GROUP_TYPE::WALL);

	CPortal* pPortal_1 = new CPortal;
	pPortal_1->SetName(L"Port_Portal");
	pPortal_1->SetPos(Vec2(1260.f, 960.f));
	pPortal_1->SetNextScene(SCENE_TYPE::SCENE_PORT);
	//포탈 크기는 고정으로 생성자에서 만듬
	AddObject(pPortal_1, GROUP_TYPE::PORTAL);

	CPortal* pPortal_2 = new CPortal;
	pPortal_2->SetName(L"Back_Street_Portal");
	pPortal_2->SetPos(Vec2(333.f, 440.f));
	pPortal_2->GetCollider()->SetScale(Vec2(140.f, 50.f));
	pPortal_2->SetNextScene(SCENE_TYPE::SCENE_BACKSTREET);
	//포탈 크기는 고정으로 생성자에서 만듬
	AddObject(pPortal_2, GROUP_TYPE::PORTAL);

	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::WALL);
	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::PORTAL);
	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::BULLET, GROUP_TYPE::MONSTER);
	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::FIREBALL);
	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::SKILL);

	//스킬 충돌 확인
	//CColliderMgr::GetInst()->ChekSkillGroup(GROUP_TYPE::MONSTER);

	//CCameraMgr::GetInst()->FadeOut(1.f);
}

void CScene_Start::Exit()
{
	DeleteAll();

	CColliderMgr::GetInst()->Reset();
}
