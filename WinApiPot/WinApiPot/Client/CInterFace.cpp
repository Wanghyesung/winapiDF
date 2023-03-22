#include "pch.h"
#include "CInterFace.h"

#include "CKeyMgr.h"
#include "CResMgr.h"
#include "CTexture.h"

#include "CItem.h"
#include "CObject.h"
#include "CHP.h"
#include "CMP.h"

#include "CInventory.h"


CInterFace::CInterFace():
	m_pInterFaceTex(nullptr),
	m_vecItem{},
	m_vItemStartPos(Vec2(150.f, 655.f)),
	m_vItemEndPos(Vec2(520.f, 693.f)),
	m_vItemStep(Vec2(62.f, 38.f))

{
	SetName(L"InterFace");
	m_pInterFaceTex = CResMgr::GetInst()->LoadTextur(L"InterFace", L"..\\OutPut\\bin_release\\Content\\Interface\\playerInterface.bmp");
	SetScale(Vec2(1280.f, 100.f));

	m_vecItem.resize(6);
}

CInterFace::~CInterFace()
{
	int a = 10;
}

void CInterFace::update()
{
	//if (KEY_TAP(KEY::KEY1))
	//{
	//	int a = 10;
	//}
	//���⼭ ����

	CUI::update();

}

void CInterFace::MouseOn()
{

}

void CInterFace::MouseLbtnDown()
{
	
}

void CInterFace::MouseLbtnUp()
{

}

void CInterFace::MouseLbtnClicked()
{

}

void CInterFace::MoveIoInterface(CItem* _pItem)
{
	//�������� ���� �ؽø� �ε���
	UINT iItemIndex = 0;
	UINT iFinalIndx = 0;

	Vec2 vOtherDragePrePos = _pItem->m_vDragePrePos;
	Vec2 vOtherItemPos = _pItem->GetPos();

	//�ϴ� �ƹ� ���̳�
	float fMinLen = 1000.f;
	Vec2  vMinVec = vOtherDragePrePos;

	for (int x = m_vItemStartPos.x; x <= m_vItemEndPos.x; x += m_vItemStep.x)
	{
		if (Vec2(x, 655) == vOtherDragePrePos)
		{
			++iItemIndex;
			continue;
		}
		//�� �κ��丮 ������ ��ġĭ�� ������ ���� ������ ��ġ
		float fLen = abs(abs(vOtherItemPos.x) - abs(x));

		if (fLen <= 55.5f && fMinLen >= fLen)
		{
			//�� �������� ���� �ε���
			iFinalIndx = iItemIndex;
			fMinLen = fLen;
			vMinVec = Vec2(x, 655);
		}
		++iItemIndex;
	}

	//�� ���� ��ġ�� �ξ��ٸ�
	if (vMinVec == vOtherDragePrePos)
	{
		_pItem->m_tItemInfo.m_vPos = vOtherDragePrePos;
		_pItem->SetPos(vOtherDragePrePos);
		return;
	}

	
	//���� interface�� �ִ� ����������
	if (!_pItem->m_bIsInterfacePos)
	{
		_pItem->m_bIsInterfacePos = true;
		//�θ� ��ġ ���� �ȹް�
		_pItem->SetParentAfeccted(false);
		//���� �θ�UI ������ interfaceUI�� �θ��
		_pItem->DeleteChildUI();
		AddChildUI(_pItem);
	}
	//�κ��丮 â���� �ٲ۰Ŷ��
	else
	{
		//�ش� �ε����� �ִ� ������ ��������
		CItem* pItem = getItemThisIndex(iFinalIndx);
		if (pItem != nullptr)
		{
			changeItemIndex(pItem, _pItem);
		}
		else
		{
			int iIndex = GetItemIndex(_pItem);
			m_vecItem[iIndex] = nullptr;
		}

	}

	m_vecItem[iFinalIndx] = _pItem;
	_pItem->m_tItemInfo.m_vPos = vMinVec;
	_pItem->SetPos(vMinVec);


}

CItem* CInterFace::getItemThisIndex(int _iIndex)
{
	for (int i = 0; i < m_vecItem.size(); ++i)
	{
		if (m_vecItem[i] == m_vecItem[_iIndex])
			return m_vecItem[i];
	}

	return nullptr;
}

int CInterFace::GetItemIndex(CItem* _pItem)
{
	for (int i = 0; i < m_vecItem.size(); ++i)
	{
		if (m_vecItem[i] == _pItem)
			return i;
	}

	return -1;
}

void CInterFace::changeItemIndex(CItem* _pItem, CItem* _pOtehr)
{
	int iIndex = GetItemIndex(_pItem);
	int iOtherIndex = GetItemIndex(_pOtehr);

	m_vecItem[iOtherIndex] = _pItem;
	_pItem->m_tItemInfo.m_vPos = _pOtehr->m_tItemInfo.m_vPos;
	_pItem->SetPos(_pOtehr->m_tItemInfo.m_vPos);
}

void CInterFace::ChangeValue(float _HPfValue, float _MPfValue)
{
	if (dynamic_cast<CHP*>(GetChildUI(L"HP")))
	{
		CHP* pHP = dynamic_cast<CHP*>(GetChildUI(L"HP"));
		float fHpValue = ((100.f - _HPfValue) / 100.f) * 88.f;
		pHP->SetMinusHp(fHpValue);
	}
	if (dynamic_cast<CMP*>(GetChildUI(L"MP")))
	{
		CMP* pMP = dynamic_cast<CMP*>(GetChildUI(L"MP"));
		float fValue = ((100.f - _MPfValue) / 100.f) * 88.f;
		pMP->SetMinusMp(fValue);

	}
}

void CInterFace::render(HDC _dc)
{
	Vec2 vPos = GetFinalPos();

	TransparentBlt(_dc,
		(int)vPos.x, (int)vPos.y,
		m_pInterFaceTex->Width(), m_pInterFaceTex->Height(),
		m_pInterFaceTex->GetDC(),
		0, 0,
		m_pInterFaceTex->Width(), m_pInterFaceTex->Height(),
		RGB(0, 0, 0));

	CUI::render(_dc);

}
