#include "pch.h"
#include "CTownUI.h"

#include "CResMgr.h"
#include "CTexture.h"
#include "CDungeonMgr.h"

CTownUI::CTownUI()
{
	SetTag(GROUP_TYPE::UI);

	pMouseNoneTex = CResMgr::GetInst()->LoadTextur(L"changeTown0", L"..\\OutPut\\bin_release\\Content\\Interface\\to_0.bmp");
	pMouseOnTex = CResMgr::GetInst()->LoadTextur(L"changeTown1", L"..\\OutPut\\bin_release\\Content\\Interface\\to_1.bmp");
	pMousePushTex = CResMgr::GetInst()->LoadTextur(L"changeTown2", L"..\\OutPut\\bin_release\\Content\\Interface\\to_2.bmp");

	SetScale(Vec2(149.f ,25.f));
}

CTownUI::~CTownUI()
{

}

void CTownUI::MouseOn()
{

}

void CTownUI::MouseLbtnDown()
{
	m_bMousePush = true;
	m_bMouseOn = false;
}

void CTownUI::MouseLbtnUp()
{

}

void CTownUI::MouseLbtnClicked()
{
	//여기다가 기능
	CDungeonMgr::GetInst()->exit_dungeon();
}

void CTownUI::render(HDC _dc)
{
	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();

	CTexture* pTex = CResMgr::GetInst()->FindTexture(L"changeTown0");

	if (m_bMouseOn)
		pTex = CResMgr::GetInst()->FindTexture(L"changeTown1");
	else if (m_bMousePush)
		pTex = CResMgr::GetInst()->FindTexture(L"changeTown2");

	TransparentBlt(_dc,
		(int)(vPos.x),
		(int)(vPos.y),
		(int)(vScale.x),
		(int)(vScale.y),
		pTex->GetDC(),
		(int)0,
		(int)0,
		(int)(pTex->Width()),
		(int)(pTex->Height()),
		RGB(255, 255, 255));


	CUI::render(_dc);
}

void CTownUI::update()
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

void CTownUI::finalupdate()
{
	CUI::finalupdate();
}
