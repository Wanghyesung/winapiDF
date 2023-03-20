#include "pch.h"
#include "CHPItem.h"

#include "CResMgr.h"
#include "CTexture.h"

#include "CKeyMgr.h"



CHPItem::CHPItem()
{
	m_pItemTex = CResMgr::GetInst()->LoadTextur(L"HPItem", L"..\\OutPut\\bin_release\\Content\\Item\\HPItem.bmp");

	//아이템 이미지 크기
	SetScale(Vec2(28.f, 28.f));

	SetItemName(L"HPItem");
}

CHPItem::~CHPItem()
{
}

void CHPItem::render(HDC _dc)
{
	//if (!m_bActive)
	//	return;

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

void CHPItem::update()
{
	CUI::update();
}

void CHPItem::finalupdate()
{
	CUI::finalupdate();
}

void CHPItem::MouseOn()
{
	if (IsLBntDown())
	{
		Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos();

		Vec2 vDiff = vMousePos - m_vDragStartPos;
		Vec2 vPos = GetPos() + vDiff;

		SetPos(vPos);
		m_vDragStartPos = CKeyMgr::GetInst()->GetMousePos();
	}
}

void CHPItem::MouseLbtnDown()
{
	m_vDragStartPos = CKeyMgr::GetInst()->GetMousePos();
}

void CHPItem::MouseLbtnUp()
{
	
}

void CHPItem::MouseLbtnClicked()
{
	
}
