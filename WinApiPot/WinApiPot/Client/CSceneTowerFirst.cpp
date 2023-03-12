#include "pch.h"
#include "CSceneTowerFirst.h"

#include "CCameraMgr.h"
#include "CSkillMgr.h"
#include "CColliderMgr.h"
#include "CCollider.h"

#include "CPlayer.h"
#include "CObject.h"

#include "CResMgr.h"
#include "CTexture.h"

#include "CPortal.h"
#include "CStoneBox.h"
#include "CPillar.h"
#include "CSpinner.h"

CSceneTowerFirst::CSceneTowerFirst():
	m_eType(SCENE_TYPE::FIRST_DUNGEON)
{

}

CSceneTowerFirst::~CSceneTowerFirst()
{

}

void CSceneTowerFirst::Init()
{
	CTexture* m_pBackGround = CResMgr::GetInst()->LoadTextur(L"dungeon_first", L"..\\OutPut\\bin_release\\Content\\Tile\\tile2.bmp");
	SetBackGround(m_pBackGround);

	//배경정보 담고 만들기
	tBackGround tInfo = {};
	tInfo.fRightWidth = m_pBackGround->Width();
	tInfo.fBottomHeight = m_pBackGround->Height() - 110;
	tInfo.fLeftWidth = GetStartDrawPoint().x + 40;
	tInfo.fTopHeight = GetStartDrawPoint().y;
	SetBackGroundInfo(tInfo);
	//플레이어 인터페이스는 씬 바꿀때 삭제X
	SetInterFace();

	CObject* pObj = CreatePlayer(Vec2(300.f, 650.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);
	RegisterPlayer(pObj);
	CSkillMgr::GetInst()->SetPlayer((CPlayer*)GetPlayerObj());
	CSkillMgr::GetInst()->init(m_eType);

	CStoneBox* pStone = new CStoneBox;
	pStone->SetPos(Vec2(400.f, 700.f));
	pStone->GetCollider()->SetScale(Vec2(50.f, 50.f));
	AddObject(pStone, GROUP_TYPE::STONE_BOX);

	CPillar* pPillar = new CPillar;
	pPillar->SetPos(Vec2(700.f, 700.f));
	pPillar->GetCollider()->SetOffSet(Vec2(0.f, 50.f));
	pPillar->GetCollider()->SetScale(Vec2(50.f, 50.f));
	AddObject(pPillar, GROUP_TYPE::STONE_PILLAR);


	CSpinner* pSpinner = new CSpinner;
	pSpinner->SetPos(Vec2(1000.f, 700.f));
	pPillar->GetCollider()->SetOffSet(Vec2(0.f, 50.f));
	pSpinner->GetCollider()->SetScale(Vec2(50.f, 110.f));
	AddObject(pSpinner, GROUP_TYPE::SPINNER);
	//CPortal* pPortal_1 = new CPortal;
	//pPortal_1->SetName(L"Port_Portal");
	//pPortal_1->SetPos(Vec2(300.f, 850.f));
	//pPortal_1->SetNextScene(SCENE_TYPE::START_SCENE);
	////포탈 크기는 고정으로 생성자에서 만듬
	//AddObject(pPortal_1, GROUP_TYPE::PORTAL);

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
	CCameraMgr::GetInst()->SetTargetObj((CPlayer*)GetPlayerObj());
	CCameraMgr::GetInst()->init();
	CSkillMgr::GetInst()->SetPlayer((CPlayer*)GetPlayerObj());

	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::STONE_BOX);
	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::STONE_PILLAR);
	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::SPINNER);
}

void CSceneTowerFirst::Exit()
{
	CColliderMgr::GetInst()->Reset();
}


