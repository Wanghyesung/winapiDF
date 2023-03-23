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
	//�ڽ� ������Ʈ �߰�
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
			//�������� ��ǥ���� ������ �̹��� ũ��
			0, 0,
			m_vecNumber[m_iItemCount - 1]->Width(), m_vecNumber[m_iItemCount - 1]->Height(),
			RGB(255, 255, 255));
	}

	//������ ���� ������ �ϰ�
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
		//�������̽� ������â ��ġ�� �θ� �������̽������� �̵�
		if (vStartPos <= vPos && vPos <= vEndPos)
		{
			pInter->MoveIoInterface(this);
		}
		else
		{
			//�ƴϸ� �κ��丮���� �̵�
			m_pInven->ChangeItemPos(this);
			//}
		}

		//interface��ġ�� ������ �������̽��� �ٲٱ�
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
