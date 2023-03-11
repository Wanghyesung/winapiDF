#include "pch.h"
#include "CSceneTowerFirst.h"

#include "CCameraMgr.h"
#include "CSkillMgr.h"
#include "CColliderMgr.h"

#include "CPlayer.h"
#include "CObject.h"

#include "CResMgr.h"
#include "CTexture.h"

#include "CPortal.h"


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

	//������� ��� �����
	tBackGround tInfo = {};
	tInfo.fRightWidth = m_pBackGround->Width();
	tInfo.fBottomHeight = m_pBackGround->Height() - 110;
	tInfo.fLeftWidth = GetStartDrawPoint().x + 40;
	tInfo.fTopHeight = GetStartDrawPoint().y;
	SetBackGroundInfo(tInfo);
	//�÷��̾� �������̽��� �� �ٲܶ� ����X
	SetInterFace();

	CObject* pObj = CreatePlayer(Vec2(300.f, 650.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);
	RegisterPlayer(pObj);
	CSkillMgr::GetInst()->SetPlayer((CPlayer*)GetPlayerObj());
	CSkillMgr::GetInst()->init(m_eType);

	//CPortal* pPortal_1 = new CPortal;
	//pPortal_1->SetName(L"Port_Portal");
	//pPortal_1->SetPos(Vec2(300.f, 850.f));
	//pPortal_1->SetNextScene(SCENE_TYPE::START_SCENE);
	////��Ż ũ��� �������� �����ڿ��� ����
	//AddObject(pPortal_1, GROUP_TYPE::PORTAL);

}

void CSceneTowerFirst::render(HDC _dc)
{
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
}

void CSceneTowerFirst::Exit()
{
	CColliderMgr::GetInst()->Reset();
}


