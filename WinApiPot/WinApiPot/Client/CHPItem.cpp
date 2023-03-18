#include "pch.h"
#include "CHPItem.h"

#include "CResMgr.h"

CHPItem::CHPItem()
{
	m_pItemTex = CResMgr::GetInst()->LoadTextur(L"Thunder1_right", L"..\\OutPut\\bin_release\\Content\\Item\\HPItem.bmp");
}

CHPItem::~CHPItem()
{
}

void CHPItem::render(HDC _dc)
{
}

void CHPItem::update()
{
}

void CHPItem::finalupdate()
{
}

void CHPItem::MouseOn()
{
}

void CHPItem::MouseLbtnDown()
{
}

void CHPItem::MouseLbtnUp()
{
}

void CHPItem::MouseLbtnClicked()
{
}
