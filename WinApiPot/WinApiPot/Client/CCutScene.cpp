#include "pch.h"
#include "CCutScene.h"

#include "CResMgr.h"
#include "CTexture.h"

#include "CCameraMgr.h"

#include "CUI.h"
#include "CDungeonUI.h"

CCutScene::CCutScene():
	m_eType(SCENE_TYPE::SELECT_SCENE),
	pBackSound(nullptr)
{

}

CCutScene::~CCutScene()
{

}

void CCutScene::render(HDC _dc)
{
	Vec2 StartPos = Vec2(0.f, 0.f);//그림을 처음에 그릴 위치
	SetStartDrawPoint(StartPos);

	CScene::render(_dc);

	//인터페이스 가리기
	CScene::backgroundrender(_dc, GetBackGround(), StartPos);

}

void CCutScene::update()
{
	CScene::update();

	Vec2 vBackGroundScale = Vec2(GetBackGround()->Width() / 2.f, GetBackGround()->Height() / 2.f);
	CCameraMgr::GetInst()->SetLookAt(vBackGroundScale);
}

void CCutScene::Enter()
{
	CCameraMgr::GetInst()->SetTargetObj(nullptr);
}

void CCutScene::Exit()
{
}

void CCutScene::Init()
{
	CTexture* pBackGround = CResMgr::GetInst()->LoadTextur(L"select", L"..\\OutPut\\bin_release\\Content\\background\\skyselect.bmp");

	SetBackGround(pBackGround);

	tBackGround tInfo = {};
	tInfo.fRightWidth = pBackGround->Width();
	tInfo.fBottomHeight = pBackGround->Height();
	tInfo.fLeftWidth = GetStartDrawPoint().x;
	tInfo.fTopHeight = GetStartDrawPoint().y;

	SetBackGroundInfo(tInfo);

	CDungeonUI* pLordDungeonUI = new CDungeonUI;
	pLordDungeonUI->SetPos(Vec2(608.f, 133.f));
	pLordDungeonUI->SetScale(Vec2(168.f,73.f));
	pLordDungeonUI->SetNextScene(SCENE_TYPE::FIRST_DUNGEON);

	AddObject(pLordDungeonUI, GROUP_TYPE::UI);

	CDungeonUI* pEyeDungeonUI = new CDungeonUI;
	pEyeDungeonUI->SetPos(Vec2(243.f, 170.f));
	pEyeDungeonUI->SetScale(Vec2(168.f, 73.f));
	pEyeDungeonUI->SetNextScene(SCENE_TYPE::EVIL_SCENE_1);

	AddObject(pEyeDungeonUI, GROUP_TYPE::UI);

}
