#include "pch.h"
#include "CInterFace.h"

#include "CKeyMgr.h"
#include "CResMgr.h"
#include "CTexture.h"

#include "CItem.h"
#include "CObject.h"
#include "CHP.h"
#include "CMP.h"

#include "CInventoryMgr.h"
#include "CInventory.h"


CInterFace::CInterFace():
	m_pInterFaceTex(nullptr),
	m_vecItem{},
	m_vecSKillTex{},
	m_vItemStartPos(Vec2(150.f, 655.f)),
	m_vItemEndPos(Vec2(520.f, 693.f)),
	m_vItemStep(Vec2(62.f, 38.f))

{
	SetName(L"InterFace");
	m_pInterFaceTex = CResMgr::GetInst()->LoadTextur(L"InterFace", L"..\\OutPut\\bin_release\\Content\\Interface\\playerInterface.bmp");
	SetScale(Vec2(1280.f, 100.f));

	m_vecSKillTex.resize(5);
	m_vecItem.resize(6);

	m_vecSKillTex[0] = CResMgr::GetInst()->LoadTextur(L"Kick", L"..\\OutPut\\bin_release\\Content\\SKill\\Kick.bmp");
	m_vecSKillTex[1] = CResMgr::GetInst()->LoadTextur(L"MachKick", L"..\\OutPut\\bin_release\\Content\\SKill\\MachKick.bmp");
	m_vecSKillTex[2] = CResMgr::GetInst()->LoadTextur(L"Windmill", L"..\\OutPut\\bin_release\\Content\\SKill\\Windmill.bmp");
	m_vecSKillTex[3] = CResMgr::GetInst()->LoadTextur(L"RandFire", L"..\\OutPut\\bin_release\\Content\\SKill\\RandomFire.bmp");
	m_vecSKillTex[4] = CResMgr::GetInst()->LoadTextur(L"WalkFire", L"..\\OutPut\\bin_release\\Content\\SKill\\WalkFire.bmp");
}

CInterFace::~CInterFace()
{
	int a = 10;
}

void CInterFace::update()
{
	//���⼭ ����
	if (KEY_TAP(KEY::KEY1))
	{
		if (m_vecItem[0] != nullptr)
		{
			m_vecItem[0]->UseItem();
		}
	}
	else if (KEY_TAP(KEY::KEY2))
	{

	}

	else if (KEY_TAP(KEY::KEY3))
	{

	}

	else if (KEY_TAP(KEY::KEY4))
	{

	}

	else if (KEY_TAP(KEY::KEY5))
	{

	}

	else if (KEY_TAP(KEY::KEY6))
	{

	}
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

	
	//���� �κ��丮�� �ִ� ����������
	if (!_pItem->m_bIsInterfacePos)
	{
		_pItem->m_bIsInterfacePos = true;
		//������ ũ�� Ű���
		_pItem->SetItemScale(m_vItemStep);
		//�θ� ��ġ ���� �ȹް�
		_pItem->SetParentAfeccted(false);
		//���� �θ�UI ������ interfaceUI�� �θ��
		_pItem->DeleteChildUI();
		AddChildUI(_pItem);

		//���⼭ �� �ڸ��� �������� �ִ��� �˻�
		CItem* pItem = getItemThisIndex(iFinalIndx);
		if(pItem != nullptr)
			changeInvenotry(pItem, vOtherDragePrePos);
	}

	//�������̽� â���� �ٲ۰Ŷ��
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

void CInterFace::changeInvenotry(CItem* _pItem, Vec2 _vOtherDragePrePos)
{
	int iIndex = GetItemIndex(_pItem);
	//�� �ڸ��� �������� ���»��¶�� �׳� return
	if (iIndex == -1)
		return;
	
	CItem* pPreItem = getItemThisIndex(iIndex);

	//�κ��丮�� ������
    pPreItem->m_bIsInterfacePos = false;
	pPreItem->SetItemScale(Vec2(28.f,28.f));
	//�θ� ��ġ ���� �ȹް�
	pPreItem->SetParentAfeccted(true);
	//���� �θ�UI ������ interfaceUI�� �θ��
	pPreItem->DeleteChildUI();
	
	pPreItem->m_tItemInfo.m_vPos = _vOtherDragePrePos;
	pPreItem->SetPos(_vOtherDragePrePos);

	CInventoryMgr::GetInst()->GetInventory()->AddChildUI(pPreItem);


}

void CInterFace::changeItemIndex(CItem* _pItem, CItem* _pOtehr)
{
	int iIndex = GetItemIndex(_pItem);
	int iOtherIndex = GetItemIndex(_pOtehr);

	m_vecItem[iOtherIndex] = _pItem;
	_pItem->m_tItemInfo.m_vPos = _pOtehr->m_tItemInfo.m_vPos;
	_pItem->SetPos(_pOtehr->m_tItemInfo.m_vPos);
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

void CInterFace::DeleteItem(CItem* _pItem)
{
	for (int i = 0; i < m_vecItem.size(); ++i)
	{
		if (m_vecItem[i] == _pItem)
			m_vecItem[i] = nullptr;
	}
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

	
	// 760 655
	Vec2 vStartPos = Vec2(758.f, 655.f);//��ų ������ �������� ����
	for (int i = 0; i < 5; ++i)
	{
		//���⿡ ��ų ������ �׸���
		TransparentBlt(_dc,
			vStartPos.x,vStartPos.y,
			m_vItemStep.x,m_vItemStep.y,
			m_vecSKillTex[i]->GetDC(),
			0, 0,
			m_vecSKillTex[i]->Width(), m_vecSKillTex[i]->Height(),
			RGB(255, 255, 255));

		vStartPos.x += m_vItemStep.x;
	}

	CUI::render(_dc);

}
