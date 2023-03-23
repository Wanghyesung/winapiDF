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

	m_iHeight = m_pItemTex->Height();
	m_iWidth = m_pItemTex->Width();


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
		m_iWidth, m_iHeight,
		m_pItemTex->GetDC(),
		//시작지점 좌표부터 가져올 이미지 크기
		0, 0,
		m_pItemTex->Width(), m_pItemTex->Height(),
		RGB(255, 255, 255));


	CItem::render(_dc);

}

void CHPItem::update()
{
	CItem::update();
}

void CHPItem::finalupdate()
{
	CUI::finalupdate();
}

void CHPItem::MouseOn()
{
	CItem::MouseOn();
}

void CHPItem::MouseLbtnDown()
{
	CItem::MouseLbtnDown();
}

void CHPItem::MouseLbtnUp()
{
	//땠을 떄 위치에 맞게 들어가기
	CItem::MouseLbtnUp();
}

void CHPItem::MouseLbtnClicked()
{
	
}
