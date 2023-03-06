#include "pch.h"
#include "CTower_1.h"

#include "CResMgr.h"
#include "CTexture.h"
#include "CObject.h"
#include "CPlayer.h"
#include "CCameraMgr.h"
#include "CSkillMgr.h"

CTower_1::CTower_1()
{

}

CTower_1::~CTower_1()
{

}

void CTower_1::Enter()
{
	CTexture* m_pBackGround = CResMgr::GetInst()->LoadTextur(L"Sky1_ba", L"..\\OutPut\\bin_release\\Content\\background\\bg_03.bmp");
	SetBackGround(m_pBackGround);

	CTexture* m_pTile = CResMgr::GetInst()->LoadTextur(L"Sky1_tile", L"..\\OutPut\\bin_release\\Content\\Tile\\tile4.bmp");
	SetTile(m_pBackGround);

	//배경정보 담고 만들기
	tBackGround tInfo = {};
	tInfo.fRightWidth = m_pBackGround->Width();
	tInfo.fBottomHeight = m_pBackGround->Height() - 110;
	tInfo.fLeftWidth = GetStartDrawPoint().x + 40;
	tInfo.fTopHeight = GetStartDrawPoint().y;
	SetBackGroundInfo(tInfo);
	//플레이어 인터페이스는 씬 바꿀때 삭제X
	SetInterFace();

	CObject* pObj = CreatePlayer(Vec2(700.f, 550.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);

	RegisterPlayer(pObj);
	CCameraMgr::GetInst()->SetTargetObj(pObj); //vResolution / 2.f
	CSkillMgr::GetInst()->SetPlayer((CPlayer*)pObj);

}

void CTower_1::Exit()
{

}

void CTower_1::render(HDC _dc)
{
	Vec2 StartPos = Vec2(0.f, 0.f);//그림을 처음에 그릴 위치
	SetStartDrawPoint(StartPos);

	CScene::backgroundrender(_dc, GetBackGround(), StartPos);
	CScene::Tile_render(_dc, GetTail());

	CScene::render(_dc);
}

void CTower_1::update()
{
	CScene::update();
}
