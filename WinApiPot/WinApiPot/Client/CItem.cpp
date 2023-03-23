#include "pch.h"
#include "CItem.h"

#include "CUIMgr.h"
#include "CKeyMgr.h"
#include "CInventory.h"
#include "CScene.h"

#include "CInterFace.h"
#include "CInterfaceMgr.h"

#include "CTexture.h"
#include "CResMgr.h"

CItem::CItem() :
	m_pInven(nullptr),
	m_bActive(false),
	m_bTargetOn(false),
	m_bIsInterfacePos(false),
	m_iItemCount(0),
	m_iWidth(0),
	m_iHeight(0),
	m_vecNumber{}
{
	//1~9
	m_vecNumber.resize(9);
	//자식 오브젝트 추가
	for (int i = 0; i < 9; ++i)
	{
		wstring strNum = std::to_wstring(i+1);
		m_vecNumber[i] = CResMgr::GetInst()->LoadTextur(L"Number", L"..\\OutPut\\bin_release\\Content\\Item\\" + strNum + L".bmp");
	}
	m_iNumberWidth = m_vecNumber[0]->Width();
	m_iNumberHeight = m_vecNumber[0]->Height();

}

CItem::~CItem()
{
	
}

void CItem::render(HDC _dc)
{

	if (m_iItemCount != 0)
	{
		Vec2 vPos = GetFinalPos();

		//offset
		TransparentBlt(_dc,
			(int)vPos.x, (int)vPos.y,
			m_iNumberWidth, m_iNumberHeight,
			m_vecNumber[m_iItemCount-1]->GetDC(),
			//시작지점 좌표부터 가져올 이미지 크기
			0, 0,
			m_vecNumber[m_iItemCount - 1]->Width(), m_vecNumber[m_iItemCount - 1]->Height(),
			RGB(255, 255, 255));
	}

	//아이템 먼저 렌더링 하고
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

void CItem::SetItemScale(Vec2 _vScale)
{
	SetScale(_vScale);
	m_iHeight = _vScale.y;
	m_iWidth = _vScale.x;

	if (m_bIsInterfacePos)
	{
		m_iNumberHeight *= 2;
		m_iNumberWidth *= 2;
	}
	else
	{
		m_iNumberHeight /= 2;
		m_iNumberWidth /= 2;
	}
}
