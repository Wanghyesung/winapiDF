#include "pch.h"
#include "CMPItem.h"


#include "CResMgr.h"
#include "CTexture.h"

#include "CKeyMgr.h"

CMPItem::CMPItem()
{
	m_pItemTex = CResMgr::GetInst()->LoadTextur(L"MPItem", L"..\\OutPut\\bin_release\\Content\\Item\\MPItem.bmp");

	//아이템 이미지 크기
	SetScale(Vec2(28.f, 28.f));

	SetItemName(L"MPItem");
}

CMPItem::~CMPItem()
{
}

void CMPItem::render(HDC _dc)
{
	Vec2 vPos = GetFinalPos();

	//offset
	TransparentBlt(_dc,
		(int)vPos.x, (int)vPos.y,
		m_pItemTex->Width(), m_pItemTex->Height(),
		m_pItemTex->GetDC(),
		//시작지점 좌표부터 가져올 이미지 크기
		0, 0,
		m_pItemTex->Width(), m_pItemTex->Height(),
		RGB(255, 255, 255));


	CUI::render(_dc);
}

void CMPItem::update()
{
	CItem::update();
}

void CMPItem::finalupdate()
{
	CUI::finalupdate();
}

void CMPItem::MouseOn()
{
	CItem::MouseOn();
}

void CMPItem::MouseLbtnDown()
{
	CItem::MouseLbtnDown();
}

void CMPItem::MouseLbtnUp()
{
	CItem::MouseLbtnUp();
}

void CMPItem::MouseLbtnClicked()
{
}
