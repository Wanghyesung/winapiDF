#include "pch.h"
#include "CInventory.h"

#include "CItem.h"
#include "CResMgr.h"
#include "CTexture.h"

#include "CKeyMgr.h"

//시작 18.5 177  끝 243 273
   //step = 32.5 32.5
   //for(int i =0; i<)

CInventory::CInventory() :
	m_bActive(false),
	m_pInvenTex(nullptr),
	m_mapInventory{},
	m_vStartPos(Vec2(18.5f,177.f)),//인벤토리 시작
	m_vEndPos(Vec2(243.f,273.f)),//인벤토리 끝
	m_vStep(Vec2(32.5f,32.5f))//넘어갈 양
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
	//공통으로 위치 잡기
	// 아이템 크기 28 28

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
					return;
				}
			}
		}
	}
	else
	{
		++_pItem->m_iItemCount;
	}

}

//제대로된 위치가 아닌 내 아이템이 있는 위치에 근접해서 마우스를 땠으면
void CInventory::ChangeItemPos(CItem* _pItem)
{
	//상대 아이템을 처음 눌렀을 때 위치
	Vec2 vOtherDragePrePos = _pItem->m_vDragePrePos;
	Vec2 vOtherItemPos = _pItem->GetPos();

	//최종적으로 나랑 바꿀 아이템
	CItem* pItem = nullptr;

	//일단 아무 값이나
	float fMinLen = 1000.f;
	Vec2  vMinVec = vOtherDragePrePos;

	for (int y = m_vStartPos.y; y <= m_vEndPos.y; y += m_vStep.y)
	{
		for (int x = m_vStartPos.x; x <= m_vEndPos.x; x += m_vStep.x)
		{
			//내 원래자리는 무시
			if (Vec2(x, y) == vOtherDragePrePos)
				continue;

			//내 인벤토리 아이템 위치칸과 아이템 들어올 아이템 위치
			float fLen = Vec2(abs(vOtherItemPos.x - x), abs(vOtherItemPos.y - y)).Length();
			if (fLen <= 23.5f && fMinLen >= fLen)
			{
				fMinLen = fLen;
				vMinVec = Vec2(x, y);
			}
		}
	}

	//여기서 최종적으로 걸린 위치에 이미 아이템이 있는지 검사 있으면 바꾸고 없으면 그냥

	//내 원래 위치에 두었다면
	if (vMinVec == vOtherDragePrePos)
	{
		_pItem->m_tItemInfo.m_vPos = vOtherDragePrePos;
		_pItem->SetPos(vOtherDragePrePos);
		return;
	}

	//같은 위치라면 바꾸고 같은 위치가 아니면 그 위치에 아이템 넣기
	pItem = GetItemThisPos(vMinVec);//이 위치에 있던 원래 아이템
	if (pItem != nullptr)
	{
		pItem->m_tItemInfo.m_vPos = vOtherDragePrePos;
		pItem->SetPos(vOtherDragePrePos);
	}
	_pItem->m_tItemInfo.m_vPos = vMinVec;
	_pItem->SetPos(vMinVec);

}

void CInventory::MoveToInterFace(CItem* _pItem)
{

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
		//시작지점 좌표부터 가져올 이미지 크기
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
	//비활성이면 클릭 안되게
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


