#include "pch.h"
#include "CChangeUI.h"

#include "CResMgr.h"
#include "CTexture.h"
#include "CDungeonMgr.h"

#include "CSound.h"

CChangeUI::CChangeUI()
{
	SetTag(GROUP_TYPE::UI);

	pMouseNoneTex = CResMgr::GetInst()->LoadTextur(L"changeDungeon0", L"..\\OutPut\\bin_release\\Content\\Interface\\ch_0.bmp");
	pMouseOnTex = CResMgr::GetInst()->LoadTextur(L"changeDungeon1", L"..\\OutPut\\bin_release\\Content\\Interface\\ch_1.bmp");
	pMousePushTex = CResMgr::GetInst()->LoadTextur(L"changeDungeon2", L"..\\OutPut\\bin_release\\Content\\Interface\\ch_2.bmp");

	SetScale(Vec2(129.f, 26.f));
}

CChangeUI::~CChangeUI()
{

}

void CChangeUI::MouseOn()
{

}

void CChangeUI::MouseLbtnDown()
{
	m_bMousePush = true;
	m_bMouseOn = false;
}

void CChangeUI::MouseLbtnUp()
{

}

void CChangeUI::MouseLbtnClicked()
{
	//여기다가 기능
	CResMgr::GetInst()->LoadSound(L"click2", L"..\\OutPut\\bin_release\\Content\\Sound\\click2.wav")->Play(false);
	CDungeonMgr::GetInst()->change_dungeon();
}

void CChangeUI::render(HDC _dc)
{
	Vec2 vPos = GetFinalPos();
	Vec2 vSclae = GetScale();

	CTexture* pTex = CResMgr::GetInst()->FindTexture(L"changeDungeon0");

	if (m_bMouseOn)
		pTex = CResMgr::GetInst()->FindTexture(L"changeDungeon1");
	else if (m_bMousePush)
		pTex = CResMgr::GetInst()->FindTexture(L"changeDungeon2");

	TransparentBlt(_dc,
		(int)(vPos.x),
		(int)(vPos.y),
		(int)(vSclae.x),
		(int)(vSclae.y),
		pTex->GetDC(),
		(int)0,
		(int)0,
		(int)(pTex->Width()),
		(int)(pTex->Height()),
		RGB(255, 255, 255));


	CUI::render(_dc);
}

void CChangeUI::update()
{
	if (IsMosueOn())
	{
		if (m_bMousePush)
			return;
		m_bMouseOn = true;
	}
	else
	{
		m_bMousePush = false;
		m_bMouseOn = false;
	}



	CUI::update();
}

void CChangeUI::finalupdate()
{
	CUI::finalupdate();
}