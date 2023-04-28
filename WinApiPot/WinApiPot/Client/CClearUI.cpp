#include "pch.h"
#include "CClearUI.h"

#include "CResMgr.h"
#include "CTexture.h"

#include "CChangeUI.h"
#include "CTownUI.h"
#include "CReStartUI.h"

CClearUI::CClearUI():
	m_bActive(false)
{
	SetTag(GROUP_TYPE::UI);
	m_pUITex = CResMgr::GetInst()->LoadTextur(L"continueUI", L"..\\OutPut\\bin_release\\Content\\Interface\\continue.bmp");

	SetScale(Vec2(270.f,160.f) * 1.5f);

	SetPos(Vec2(850, 10));
}

CClearUI::~CClearUI()
{

}

void CClearUI::MouseOn()
{

}

void CClearUI::MouseLbtnDown()
{

}

void CClearUI::MouseLbtnUp()
{

}

void CClearUI::MouseLbtnClicked()
{

}

void CClearUI::render(HDC _dc)
{
	if (!m_bActive)
		return;

	Vec2 vPos = GetFinalPos();

	TransparentBlt(_dc,
		vPos.x, vPos.y,
		(int)m_pUITex->Width()*1.5f,
		(int)m_pUITex->Height()*1.5f,
		m_pUITex->GetDC(),
		0, 0,
		(int)m_pUITex->Width(),
		(int)m_pUITex->Height(),
		RGB(0, 0, 0));

	CUI::render(_dc);
}

void CClearUI::update()
{
	if (!m_bActive)
		return;

	CUI::update();
}

void CClearUI::finalupdate()
{
	if (!m_bActive)
		return;

	CUI::finalupdate();
}

void CClearUI::init()
{
	CReStartUI* pResStartUI = new CReStartUI;
	pResStartUI->SetPos(Vec2(169.f, 85.f));
	AddChildUI(pResStartUI);

	CChangeUI* pChangeUI = new CChangeUI;
	pChangeUI->SetPos(Vec2(137.f, 132.f));
	AddChildUI(pChangeUI);

	CTownUI* pTownUI = new CTownUI;
	pTownUI->SetPos(Vec2(127.f, 177.f));
	AddChildUI(pTownUI);
}
