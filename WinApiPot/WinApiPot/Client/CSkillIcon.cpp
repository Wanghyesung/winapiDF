#include "pch.h"
#include "CSkillIcon.h"

#include "CSkillMgr.h"
#include "CResMgr.h"
#include "CTexture.h"


CSkillIcon::CSkillIcon() :
	m_bMouseOn(false),
	m_bMousePush(false)
{
	SetScale(Vec2(36.f, 26.f));

	pMouseNoneTex = CResMgr::GetInst()->LoadTextur(L"SKillIconNone", L"..\\OutPut\\bin_release\\Content\\Interface\\skillIcon_0.bmp");
	pMouseOnTex = CResMgr::GetInst()->LoadTextur(L"SKillIconOn", L"..\\OutPut\\bin_release\\Content\\Interface\\skillIcon_1.bmp");
	pMousePushTex = CResMgr::GetInst()->LoadTextur(L"SKillIconPush", L"..\\OutPut\\bin_release\\Content\\Interface\\skillIcon_2.bmp");
}

CSkillIcon::~CSkillIcon()
{
}

void CSkillIcon::render(HDC _dc)
{
	Vec2 vPos = GetFinalPos();

	CTexture* pTex = CResMgr::GetInst()->FindTexture(L"SKillIconNone");

	if (m_bMouseOn)
		pTex = CResMgr::GetInst()->FindTexture(L"SKillIconOn");
	else if (m_bMousePush)
		pTex = CResMgr::GetInst()->FindTexture(L"SKillIconPush");

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

void CSkillIcon::update()
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

void CSkillIcon::MouseOn()
{

}

void CSkillIcon::MouseLbtnDown()
{
	m_bMousePush = true;
	m_bMouseOn = false;
}

void CSkillIcon::MouseLbtnUp()
{
}

void CSkillIcon::MouseLbtnClicked()
{
	CSkillMgr::GetInst()->ChangeSKillType();

	m_bMousePush = false;
}
