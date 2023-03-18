#include "pch.h"
#include "CInventory.h"

#include "CResMgr.h"


CInventory::CInventory() :
	m_bActive(false),
	m_pInvenTex(nullptr),
	m_mapInventory{}
{
	m_pInvenTex = CResMgr::GetInst()->LoadTextur(L"Inventory", L"..\\OutPut\\bin_release\\Content\\Item\\iTeminventory.bmp");

}

CInventory::~CInventory()
{

}

void CInventory::render(HDC _dc)
{
	CUI::render(_dc);
}

void CInventory::update()
{
	CUI::update();
}

void CInventory::finalupdate()
{
	CUI::finalupdate();
}

void CInventory::MouseOn()
{

}

void CInventory::MouseLbtnDown()
{

}

void CInventory::MouseLbtnUp()
{

}

void CInventory::MouseLbtnClicked()
{
}
