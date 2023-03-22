#include "pch.h"
#include "CItem.h"

#include "CUIMgr.h"
#include "CKeyMgr.h"
#include "CInventory.h"
#include "CScene.h"

#include "CInterFace.h"
#include "CInterfaceMgr.h"

CItem::CItem():
	m_pInven(nullptr),
	m_bActive(false),
	m_bTargetOn(false),
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

	if (m_bTargetOn)
	{
		Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos();

		Vec2 vDiff = vMousePos - m_vDragStartPos;
		Vec2 vPos = GetPos() + vDiff;

		Vec2 vEndPos = m_pInven->GetEndPos();
		Vec2 vStartPos = m_pInven->GetStartPos();

		//if (vPos <= vEndPos && vStartPos <= vPos)
		//{
		//	SetPos(vPos);
		//}
		SetPos(vPos);
		m_vDragStartPos = CKeyMgr::GetInst()->GetMousePos();
	}

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
	m_bTargetOn = true;

	CUIMgr::GetInst()->MoveFrontChildUI(this);
	m_vDragStartPos = CKeyMgr::GetInst()->GetMousePos();
	m_vDragePrePos = GetPos();
}

void CItem::MouseLbtnUp()
{
	m_bTargetOn = false;

	if (m_pInven != nullptr)
	{
		CInterFace* pInter = CInterfaceMgr::GetInst()->GetPlayerInterFace();
		Vec2 vStartPos = pInter->GetItemStartPos();
		Vec2 vEndPos = pInter->GetItemEndPos();
		Vec2 vPos = GetPos();
		//인터페이스 아이템창 위치에 두면 인터페이스쪽으로 이동
		if (vStartPos <= vPos && vPos <= vEndPos)
		{
			pInter->MoveIoInterface(this);
		}
		else
		{
			//아니면 인벤토리에서 이동
			m_pInven->ChangeItemPos(this);
			//}
		}

		//interface위치에 놓으면 인터페이스로 바꾸기
	}
}

void CItem::MouseLbtnClicked()
{

}
