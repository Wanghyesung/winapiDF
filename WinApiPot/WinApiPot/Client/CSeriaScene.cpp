#include "pch.h"
#include "CSeriaScene.h"

#include "CTexture.h"
#include "CResMgr.h"
#include "CPathMgr.h"

#include "CObject.h"
#include "CPlayer.h"

#include "CCameraMgr.h"


CSeriaScene::CSeriaScene()
{
}

CSeriaScene::~CSeriaScene()
{

}

void CSeriaScene::render(HDC _dc)
{
	Vec2 StartPos = Vec2(0.f, 0.f);//그림을 처음에 그릴 위치
	SetStartDrawPoint(StartPos);

	CScene::backgroundrender(_dc, GetBackGround(), StartPos);

	CScene::render(_dc);


	

}


void CSeriaScene::Enter()
{
	CTexture* pBackGround = CResMgr::GetInst()->LoadTextur(L"Seria", L"background//seria2.bmp");

	SetBackGround(pBackGround);

	tBackGround tInfo = {};
	tInfo.fRightWidth = pBackGround->Width();
	tInfo.fBottomHeight = pBackGround->Height(); 
	tInfo.fLeftWidth = GetStartDrawPoint().x;
	tInfo.fTopHeight = GetStartDrawPoint().y;

	SetBackGroundInfo(tInfo);


	CObject* pObj = CreatePlayer(Vec2(700.f, 550.f));
	//pObj->SetName(L"Player");
	//pObj->SetPos(Vec2(620.f, 380.f));
	//pObj->SetScale(Vec2(50.f, 50.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);

	RegisterPlayer(pObj);
	CCameraMgr::GetInst()->SetTargetObj(pObj); //vResolution / 2.f
	//CSkillMgr::GetInst()->SetPlayer(pObj);
}

void CSeriaScene::Exit()
{

}
