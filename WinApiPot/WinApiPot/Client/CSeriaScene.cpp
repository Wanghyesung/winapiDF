#include "pch.h"
#include "CSeriaScene.h"

#include "CTexture.h"
#include "CResMgr.h"
#include "CPathMgr.h"

#include "CObject.h"
#include "CPlayer.h"

#include "CCameraMgr.h"
#include "CSkillMgr.h"
#include "CColliderMgr.h"

CSeriaScene::CSeriaScene():
	m_eType(SCENE_TYPE::SERIA_SCENE)
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
void CSeriaScene::Init()
{
	CTexture* pBackGround = CResMgr::GetInst()->LoadTextur(L"Seria", L"..\\OutPut\\bin_release\\Content\\background//seria2.bmp");

	SetBackGround(pBackGround);

	tBackGround tInfo = {};
	tInfo.fRightWidth = pBackGround->Width();
	tInfo.fBottomHeight = pBackGround->Height();
	tInfo.fLeftWidth = GetStartDrawPoint().x;
	tInfo.fTopHeight = GetStartDrawPoint().y;

	SetBackGroundInfo(tInfo);


	CPlayer* pObj = CreatePlayer(Vec2(700.f, 550.f));
	//pObj->SetName(L"Player");
	//pObj->SetPos(Vec2(620.f, 380.f));
	//pObj->SetScale(Vec2(50.f, 50.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);

	RegisterPlayer(pObj);
	CCameraMgr::GetInst()->SetTargetObj(pObj); //vResolution / 2.f

}

void CSeriaScene::Enter()
{
	
	CSkillMgr::GetInst()->SetPlayer((CPlayer*)GetPlayerObj());
	CSkillMgr::GetInst()->init(m_eType);

}

void CSeriaScene::Exit()
{
	DeleteGroup(GROUP_TYPE::SKILL);

	CColliderMgr::GetInst()->Reset();
}


