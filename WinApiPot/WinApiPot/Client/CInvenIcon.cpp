#include "pch.h"
#include "CInvenIcon.h"

#include "CInventoryMgr.h"
#include "CInventory.h"
#include "CResMgr.h"
#include "CTexture.h"

#include "CSound.h"


CInvenIcon::CInvenIcon() :
	m_bMouseOn(false),
	m_bMousePush(false)
{
	SetScale(Vec2(36.f, 26.f));
	
	pMouseNoneTex = CResMgr::GetInst()->LoadTextur(L"InvenIconNone", L"..\\OutPut\\bin_release\\Content\\Interface\\invenIcon_0.bmp");
	pMouseOnTex = CResMgr::GetInst()->LoadTextur(L"InvenIconOn", L"..\\OutPut\\bin_release\\Content\\Interface\\invenIcon_1.bmp");
	pMousePushTex = CResMgr::GetInst()->LoadTextur(L"InvenIconPush", L"..\\OutPut\\bin_release\\Content\\Interface\\invenIcon_2.bmp");

}

CInvenIcon::~CInvenIcon()
{
}

void CInvenIcon::render(HDC _dc)
{
	Vec2 vPos = GetFinalPos();

	CTexture* pTex = CResMgr::GetInst()->FindTexture(L"InvenIconNone");

	if (m_bMouseOn)
		pTex = CResMgr::GetInst()->FindTexture(L"InvenIconOn");
	else if(m_bMousePush)
		pTex = CResMgr::GetInst()->FindTexture(L"InvenIconPush");
	
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
		RGB(0, 0, 0));
	

	CUI::render(_dc);
}

void CInvenIcon::update()
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

void CInvenIcon::MouseOn()
{
	
}

void CInvenIcon::MouseLbtnDown()
{
	m_bMousePush = true;
	m_bMouseOn = false;
}

void CInvenIcon::MouseLbtnUp()
{
}

void CInvenIcon::MouseLbtnClicked()
{
	CResMgr::GetInst()->LoadSound(L"click1", L"..\\OutPut\\bin_release\\Content\\Sound\\click1.wav")->Play(false);

	CInventory* pInven = CInventoryMgr::GetInst()->GetInventory();
	if (pInven->m_bActive)
		pInven->m_bActive = false;
	else
		pInven->m_bActive = true;

	m_bMousePush = false;
}
