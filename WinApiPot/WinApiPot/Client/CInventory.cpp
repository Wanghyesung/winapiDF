#include "pch.h"
#include "CInventory.h"

#include "CItem.h"
#include "CResMgr.h"
#include "CTexture.h"

#include "CKeyMgr.h"

#include "CInterFace.h"
#include "CInterfaceMgr.h"
#include "CCoinMgr.h"

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

CItem* CInventory::GetItemThisPos(Vec2 _vPos)
{
	map<wstring, CItem*>::iterator iter = m_mapInventory.begin();

	for (; iter != m_mapInventory.end(); ++iter)
	{
		if (iter->second->GetItemInfo().m_vPos == _vPos)
		{
			return iter->second;
		}
	}
	return nullptr;
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
					_pItem->m_pInven = this;
					_pItem->m_tItemInfo.m_vPos = Vec2(x, y);
					_pItem->SetPos(Vec2(x, y));
					m_mapInventory.insert(make_pair(_pItem->GetItemName(), _pItem));
					AddChildUI(_pItem);
					++_pItem->m_iItemCount;
					return;
				}
			}
		}
	}
	else
	{
		//���� �ִ� �� ������
		CItem* pItem = FindItem(_pItem->GetItemInfo().m_strName);
		if (pItem->m_iItemCount >= 9)
		{
			DeleteObject(_pItem);
			return;
		}
		++pItem->m_iItemCount;
		DeleteObject(_pItem);
	}

}

//����ε� ��ġ�� �ƴ� �� �������� �ִ� ��ġ�� �����ؼ� ���콺�� ������
void CInventory::ChangeItemPos(CItem* _pItem)
{
	//��� �������� ó�� ������ �� ��ġ
	Vec2 vOtherDragePrePos = _pItem->m_vDragePrePos;
	Vec2 vOtherItemPos = _pItem->GetPos();

	//���������� ���� �ٲ� ������
	CItem* pItem = nullptr;

	//�ϴ� �ƹ� ���̳�
	float fMinLen = 1000.f;
	Vec2  vMinVec = vOtherDragePrePos;

	for (int y = m_vStartPos.y; y <= m_vEndPos.y; y += m_vStep.y)
	{
		for (int x = m_vStartPos.x; x <= m_vEndPos.x; x += m_vStep.x)
		{
			//�� �����ڸ��� ����
			if (Vec2(x, y) == vOtherDragePrePos)
				continue;

			//�� �κ��丮 ������ ��ġĭ�� ������ ���� ������ ��ġ
			float fLen = Vec2(abs(vOtherItemPos.x - x), abs(vOtherItemPos.y - y)).Length();
			if (fLen <= 23.5f && fMinLen >= fLen)
			{
				fMinLen = fLen;
				vMinVec = Vec2(x, y);
			}
		}
	}

	//���⼭ ���������� �ɸ� ��ġ�� �̹� �������� �ִ��� �˻� ������ �ٲٰ� ������ �׳�

	//�� ���� ��ġ�� �ξ��ٸ�
	if (vMinVec == vOtherDragePrePos)
	{
		_pItem->m_tItemInfo.m_vPos = vOtherDragePrePos;
		_pItem->SetPos(vOtherDragePrePos);
		return;
	}

	//�������̽����� �� �������̶��
	if (_pItem->m_bIsInterfacePos)
	{
		CItem* pItem = GetItemThisPos(vMinVec);
		if (pItem != nullptr)
		{
			changeInterface(pItem, _pItem, vOtherDragePrePos);
		}
		else
		{
			//������ ���Ϳ��� �����
			CInterfaceMgr::GetInst()->GetPlayerInterFace()->DeleteItem(_pItem);
		}
		_pItem->m_bIsInterfacePos = false;

		_pItem->SetItemScale(Vec2(28.f, 28.f));

		//�θ� ��ġ ���� �ȹް�
		_pItem->SetParentAfeccted(true);
		//���� �θ�UI ������ interfaceUI�� �θ��
		_pItem->DeleteChildUI();
		AddChildUI(_pItem);

	}

	//���� ��ġ��� �ٲٰ� ���� ��ġ�� �ƴϸ� �� ��ġ�� ������ �ֱ�
	pItem = GetItemThisPos(vMinVec);//�� ��ġ�� �ִ� ���� ������
	if (pItem != nullptr)
	{
		pItem->m_tItemInfo.m_vPos = vOtherDragePrePos;
		pItem->SetPos(vOtherDragePrePos);
	}
	_pItem->m_tItemInfo.m_vPos = vMinVec;
	_pItem->SetPos(vMinVec);

}

//���� �ִ� ������ , ���� �ѷ��� ������ , �巡�� ó�� ������ ��ġ
void CInventory::changeInterface(CItem* _pItem, CItem* _pOtherItem, Vec2 _vOtherDragePrePos)
{
	//�κ��丮���� interface��
	_pItem->m_bIsInterfacePos = true;
	_pItem->SetItemScale(Vec2(62.f, 38.f));//������ ũ�� ����
	//�θ� ��ġ ���� �ȹް�
	_pItem->SetParentAfeccted(false);
	//���� �θ�UI ������ interfaceUI�� �θ��
	_pItem->DeleteChildUI();

	_pItem->m_tItemInfo.m_vPos = _vOtherDragePrePos;
	_pItem->SetPos(_vOtherDragePrePos);

	CInterFace* pInter = CInterfaceMgr::GetInst()->GetPlayerInterFace();
	int iIndex = pInter->GetItemIndex(_pOtherItem);
	pInter->AddChildUI(_pItem);
	pInter->AddVecItem(_pItem, iIndex);
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

	//���� ���� render
	UINT iCoinCount = CCoinMgr::GetInst()->GetCoinCount();
	//50 322
	wstring strNum = std::to_wstring(iCoinCount);
	CTexture* pCoinCnt = CResMgr::GetInst()->FindTexture(L"coin" + strNum);

	TransparentBlt(_dc,
		50, 310,
		pCoinCnt->Width(), pCoinCnt->Height(),
		pCoinCnt->GetDC(),
		//�������� ��ǥ���� ������ �̹��� ũ��
		0, 0,
		pCoinCnt->Width(), pCoinCnt->Height(),
		RGB(0, 0, 0));

	//�����۵��� childUI����
	CUI::render(_dc);
}

void CInventory::update()
{
	if (!m_bActive)
		return;
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
	
}

void CInventory::MouseLbtnUp()
{

}

void CInventory::MouseLbtnClicked()
{
}

void CInventory::DeleteItem(CItem* _pItem)
{
	map<wstring,CItem*>::iterator iter = m_mapInventory.find(_pItem->GetItemName());

	if (iter != m_mapInventory.end())
	{
		m_mapInventory.erase(iter);
	}
}


