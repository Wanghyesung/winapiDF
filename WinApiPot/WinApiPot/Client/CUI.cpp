#include "pch.h"
#include "CUI.h"
#include "CSeleteGDI.h"

#include "CKeyMgr.h"
#include "CCameraMgr.h"

CUI::CUI():m_pParentUI(nullptr),
			m_bCamAfeccted(false),
			m_bMouseOn(false),
			m_bLbntDown(false)
{
}

CUI::CUI(const CUI& _pUI):
	CObject(_pUI),
	m_pParentUI(nullptr),
	m_bCamAfeccted(_pUI.m_bCamAfeccted),
	m_bMouseOn(false),
	m_bLbntDown(false)
{
	for (int i = 0; _pUI.m_vecChildUI.size(); ++i)
	{
		AddChildUI(_pUI.m_vecChildUI[i]);
	}
}

CUI::~CUI()
{
}

void CUI::render(HDC _dc)
{
	Vec2 vPos = m_vFinalPos;
	Vec2 vScale = GetScale();

	if (m_bCamAfeccted)
	{
		vPos = CCameraMgr::GetInst()->GetRenderPos(vPos);

		CSeleteGDI gdi(_dc, PEN_TYPE::GREEN);

		Rectangle(_dc,
			(int)(vPos.x),
			(int)(vPos.y),
			(int)(vPos.x + vScale.x),
			(int)(vPos.y + vScale.y)
		);
	}

	else
	{
		Rectangle(_dc,
			(int)(vPos.x - vScale.x),
			(int)(vPos.y - vScale.y),
			(int)(vPos.x + vScale.x),
			(int)(vPos.y + vScale.y)
		);
	}
}

void CUI::update()
{
	ChildUpdate();
}

void CUI::finalupdate()
{
	CUI::finalupdate();

	//부모가 이동하면 자식들도 위치를 이동해야함
	m_vFinalPos = GetPos();
	Vec2 vScale = GetScale();

	if (GetParentUI() != nullptr)
	{
		m_vFinalPos += GetParentUI()->GetPos();
	}

	MouseOnCheck();

	ChildFinalupdate();

}

void CUI::ChildUpdate()
{
	for (int i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->update();
	}
}

void CUI::ChildRender(HDC _dc)
{
	for (int i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->render(_dc);
	}
}

void CUI::ChildFinalupdate()
{
	for (int i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->finalupdate();
	}
}


//virtual 
void CUI::MouseOn()
{

}

void CUI::MouseLbtnDown()
{

}

void CUI::MouseLbtnUp()
{

}

void CUI::MouseLbtnClicked()
{

}


void CUI::MouseOnCheck()
{
	Vec2 vKeyPos = CKeyMgr::GetInst()->GetMousePos();
	Vec2 vScale = GetScale();

	if (m_bCamAfeccted)
	{
		vKeyPos = CCameraMgr::GetInst()->GetRealPos(vKeyPos);
	}

	if (m_vFinalPos.x <= vKeyPos.x && m_vFinalPos.x <= (m_vFinalPos.x + vScale.x) &&
		m_vFinalPos.y <= vKeyPos.y && m_vFinalPos.y <= (m_vFinalPos.y + vScale.y))
	{
		m_bMouseOn = true;
	}
	else
	{
		m_bMouseOn = false;
	}
}
