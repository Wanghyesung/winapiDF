#include "pch.h"
#include "CInventory.h"

#include "CItem.h"
#include "CResMgr.h"
#include "CTexture.h"

#include "CKeyMgr.h"

//���� 18.5 177  �� 243 273
   //step = 32.5 32.5
   //for(int i =0; i<)

CInventory::CInventory() :
	m_bActive(false),
	m_pInvenTex(nullptr),
	m_mapInventory{},
	m_vStartPos(Vec2(18.5f,177.f)),//�κ��丮 ����
	m_vEndPos(Vec2(243.f,273.f)),//�κ��丮 ��
	m_vStep(Vec2(32.5f,32.5f))//�Ѿ ��
{
	m_pInvenTex = CResMgr::GetInst()->LoadTextur(L"Inventory", L"..\\OutPut\\bin_release\\Content\\Item\\iTeminventory.bmp");

	SetName(L"Inventory");
	SetScale(Vec2(291.f, 410.f));

}

CInventory::~CInventory()
{

}

CItem* CInventory::FindItem(const wstring& _strName)
{
	map<wstring, CItem*>::iterator iter = m_mapInventory.find(_strName);

	if (iter != m_mapInventory.end())
	{
		return iter->second;
	}
	return nullptr;
}

bool CInventory::IsSamePos(Vec2 _vPos)
{
	map<wstring, CItem*>::iterator iter = m_mapInventory.begin();

	for (; iter != m_mapInventory.end(); ++iter)
	{
		if (iter->second->GetItemInfo().m_vPos == _vPos)
		{
			return true;
		}
	}
	return false;
}

void CInventory::AddItem(CItem* _pItem)
{
	//�������� ��ġ ���
	// ������ ũ�� 28 28

	if (FindItem(_pItem->GetItemInfo().m_strName) == nullptr)
	{
		for (int y = m_vStartPos.y; y <= m_vEndPos.y; y += m_vStep.y)
		{
			for (int x = m_vStartPos.x; x <= m_vEndPos.x; x += m_vStep.x)
			{
				if (IsSamePos(Vec2(x, y)))
				{
					continue;
				}
				else
				{
					_pItem->GetItemInfo().m_vPos = Vec2(x, y);
					_pItem->SetPos(Vec2(x, y));
					m_mapInventory.insert(make_pair(_pItem->GetItemName(), _pItem));
					AddChildUI(_pItem);
					return;
				}
			}
		}
	}
	else
	{
		++_pItem->m_iItemCount;
	}

	//�κ��丮�� �� ������ ��ġ�� ���ٸ�
	//if (FindItem(_pItem->GetItemInfo().m_vPos) == nullptr)
	//{
	//	for (int y = m_vStartPos.y; y <= m_vEndPos.y; y += m_vStep.y)
	//	{
	//		for (int x = m_vStartPos.x; x <= m_vEndPos.x; x += m_vStep.x)
	//		{
	//			if (FindItem(Vec2(x, y)) == nullptr)
	//			{
	//				Vec2 vPos = Vec2(x, y);
	//				_pItem->GetItemInfo().m_vPos = vPos;
	//				_pItem->SetPos(vPos);
	//				m_mapInventory.insert(make_pair(vPos, _pItem));
	//				AddChildUI(_pItem);
	//				return;
	//			}
	//		}
	//	}
	//}
	////�̹� �κ��丮 ��ġ�� �� �������� �ִٸ�
	//else
	//{
	//	++_pItem->m_iItemCount;
	//}
}

void CInventory::render(HDC _dc)
{
	if (!m_bActive)
		return;

	Vec2 vPos = GetFinalPos();

	//offset
	TransparentBlt(_dc,
		(int)vPos.x, (int)vPos.y,
		m_pInvenTex->Width(), m_pInvenTex->Height(),
		m_pInvenTex->GetDC(),
		//�������� ��ǥ���� ������ �̹��� ũ��
		0, 0,
		m_pInvenTex->Width(), m_pInvenTex->Height(),
		RGB(255, 255, 255));


	CUI::render(_dc);
}

void CInventory::update()
{
	CUI::update();
}

void CInventory::finalupdate()
{
	//��Ȱ���̸� Ŭ�� �ȵǰ�
	if (!m_bActive)
		return;

	CUI::finalupdate();
}

void CInventory::MouseOn()
{

}

void CInventory::MouseLbtnDown()
{
	//scale���ϱ�
	int a = 10;
}

void CInventory::MouseLbtnUp()
{

}

void CInventory::MouseLbtnClicked()
{
}


