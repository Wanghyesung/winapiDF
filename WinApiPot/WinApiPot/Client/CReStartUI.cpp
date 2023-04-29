#include "pch.h"
#include "CReStartUI.h"

#include "CResMgr.h"
#include "CTexture.h"
#include "CDungeonMgr.h"

#include "CSound.h"

CReStartUI::CReStartUI()
{
	SetTag(GROUP_TYPE::UI);

	pMouseNoneTex = CResMgr::GetInst()->LoadTextur(L"restart0", L"..\\OutPut\\bin_release\\Content\\Interface\\re_0.bmp");
	pMouseOnTex = CResMgr::GetInst()->LoadTextur(L"restart1", L"..\\OutPut\\bin_release\\Content\\Interface\\re_1.bmp");
	pMousePushTex = CResMgr::GetInst()->LoadTextur(L"restart2", L"..\\OutPut\\bin_release\\Content\\Interface\\re_2.bmp");

	SetScale(Vec2(45.f, 18.f));
}

CReStartUI::~CReStartUI()
{

}

void CReStartUI::MouseOn()
{

}

void CReStartUI::MouseLbtnDown()
{
	m_bMousePush = true;
	m_bMouseOn = false;
}

void CReStartUI::MouseLbtnUp()
{

}

void CReStartUI::MouseLbtnClicked()
{
	//여기다가 기능
	CResMgr::GetInst()->LoadSound(L"click2", L"..\\OutPut\\bin_release\\Content\\Sound\\click2.wav")->Play(false);
	CDungeonMgr::GetInst()->restart_scene();
}

void CReStartUI::render(HDC _dc)
{
	Vec2 vPos = GetFinalPos();

	CTexture* pTex = CResMgr::GetInst()->FindTexture(L"restart0");

	if (m_bMouseOn)
		pTex = CResMgr::GetInst()->FindTexture(L"restart1");
	else if (m_bMousePush)
		pTex = CResMgr::GetInst()->FindTexture(L"restart2");

	TransparentBlt(_dc,
		(int)(vPos.x),
		(int)(vPos.y),
		(int)(pTex->Width() + 20),
		(int)(pTex->Height() + 8),
		pTex->GetDC(),
		(int)0,
		(int)0,
		(int)(pTex->Width()),
		(int)(pTex->Height()),
		RGB(255, 255, 255));


	CUI::render(_dc);
}

void CReStartUI::update()
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

void CReStartUI::finalupdate()
{
	CUI::finalupdate();
}
