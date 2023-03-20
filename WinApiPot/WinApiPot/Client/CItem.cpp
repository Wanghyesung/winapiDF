#include "pch.h"
#include "CItem.h"

CItem::CItem():
	m_bActive(false),
	m_iItemCount(0)
{

}

CItem::~CItem()
{

}

void CItem::render(HDC _dc)
{
	CUI::render(_dc);
}

void CItem::update()
{
	CUI::update();
}

void CItem::finalupdate()
{
	CUI::finalupdate();
}

void CItem::MouseOn()
{

}

void CItem::MouseLbtnDown()
{

}

void CItem::MouseLbtnUp()
{

}

void CItem::MouseLbtnClicked()
{

}
