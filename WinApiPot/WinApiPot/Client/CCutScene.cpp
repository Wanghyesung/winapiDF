#include "pch.h"
#include "CCutScene.h"

#include "CResMgr.h"
#include "CTexture.h"

CCutScene::CCutScene():
	m_eType(SCENE_TYPE::LOGO_SCENE),
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

	CScene::backgroundrender(_dc, GetBackGround(), StartPos);

	CScene::render(_dc);
}

void CCutScene::Enter()
{
}

void CCutScene::Exit()
{
}

void CCutScene::Init()
{
	CTexture* pBackGround = CResMgr::GetInst()->LoadTextur(L"logoScene", L"..\\OutPut\\bin_release\\Content\\background\\dnf_logo.bmp");

	SetBackGround(pBackGround);

	tBackGround tInfo = {};
	tInfo.fRightWidth = pBackGround->Width();
	tInfo.fBottomHeight = pBackGround->Height();
	tInfo.fLeftWidth = GetStartDrawPoint().x;
	tInfo.fTopHeight = GetStartDrawPoint().y;

	SetBackGroundInfo(tInfo);
}
