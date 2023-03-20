#include "pch.h"
#include "CInventoryMgr.h"

#include "CKeyMgr.h"
#include "CScene.h"
#include "CSceneMgr.h"

#include "CInventory.h"

CInventoryMgr::CInventoryMgr()
{

}

CInventoryMgr::~CInventoryMgr()
{

}

void CInventoryMgr::update()
{
	if (KEY_TAP(KEY::I))
	{
		if(m_pTargetInven->m_bActive)
			m_pTargetInven->m_bActive = false;
		else
			m_pTargetInven->m_bActive = true;
	}
}

void CInventoryMgr::render(HDC _dc)
{

}

void CInventoryMgr::init()
{
	vector<CObject*> vecUI = SceneMgr::GetInst()->GetCurSCene()->GetGroupUI();

	for (int i = 0; i < vecUI.size(); ++i)
	{
		if (vecUI[i]->GetName() == L"Inventory")
		{
			m_pTargetInven = (CInventory*)vecUI[i];
		}
	}
}
