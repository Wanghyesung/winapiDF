#include "pch.h"
#include "CSceneLog.h"

#include "CTexture.h"
#include "CResMgr.h"

#include "CSound.h"
#include "CKeyMgr.h"
#include "CCameraMgr.h"

CSceneLog::CSceneLog():
	m_eType(SCENE_TYPE::LOGO_SCENE),
	pBackSound(nullptr)
{
}

CSceneLog::~CSceneLog()
{
}

void CSceneLog::Enter()
{
	//사운드
	pBackSound->Play(true);
}

void CSceneLog::Exit()
{
	pBackSound->Stop(true);
}

void CSceneLog::Init()
{
	CTexture* pBackGround = CResMgr::GetInst()->LoadTextur(L"logoScene", L"..\\OutPut\\bin_release\\Content\\background\\dnf_logo.bmp");

	SetBackGround(pBackGround);

	tBackGround tInfo = {};
	tInfo.fRightWidth = pBackGround->Width();
	tInfo.fBottomHeight = pBackGround->Height();
	tInfo.fLeftWidth = GetStartDrawPoint().x;
	tInfo.fTopHeight = GetStartDrawPoint().y;

	SetBackGroundInfo(tInfo);

	pBackSound
		= CResMgr::GetInst()->LoadSound(L"logo", L"..\\OutPut\\bin_release\\Content\\Sound\\logo.wav");
}

void CSceneLog::update()
{
	if (KEY_TAP(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::SERIA_SCENE);
		return;
	}

	CScene::update();

	Vec2 vBackGroundScale = Vec2(GetBackGround()->Width() / 2.f, GetBackGround()->Height() / 2.f);
	CCameraMgr::GetInst()->SetLookAt(vBackGroundScale);

}

void CSceneLog::render(HDC _dc)
{
	Vec2 StartPos = Vec2(0.f, 0.f);//그림을 처음에 그릴 위치
	SetStartDrawPoint(StartPos);

	CScene::backgroundrender(_dc, GetBackGround(), StartPos);

	CScene::render(_dc);
}
