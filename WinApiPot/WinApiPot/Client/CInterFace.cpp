#include "pch.h"
#include "CInterFace.h"

#include "CKeyMgr.h"
#include "CResMgr.h"
#include "CTexture.h"

#include "CItem.h"
#include "CObject.h"
#include "CHP.h"
#include "CMP.h"

#include "CSkillMgr.h"
#include "CInventoryMgr.h"
#include "CInventory.h"
#include "CInvenIcon.h"

#include "CSkillMgr.h"

CInterFace::CInterFace():
	m_pInterFaceTex(nullptr),
	m_vecItem{},
	m_vecSKillTex{},
	m_vecCoolDownTex{},
	m_vecKeyValue{},
	m_vItemStartPos(Vec2(150.f, 655.f)),
	m_vItemEndPos(Vec2(520.f, 693.f)),
	m_vItemStep(Vec2(62.f, 38.f))

{
	SetName(L"InterFace");
	m_pInterFaceTex = CResMgr::GetInst()->LoadTextur(L"InterFace", L"..\\OutPut\\bin_release\\Content\\Interface\\playerInterface.bmp");
	SetScale(Vec2(1280.f, 100.f));

	m_vecSKillTex.resize(12);
	m_vecCoolDownTex.resize(12);
	m_vecItem.resize(6);

	//�� �������̽� Ű �Է°�
	m_vecKeyValue = { L"1",L"2" ,L"3" ,L"4" ,L"5" ,L"6" ,L"z" ,L"s" ,L"d" ,L"f" ,L"t", L"w"};

	//��ų �̹���
	m_vecSKillTex[0] = CResMgr::GetInst()->LoadTextur(L"Kick", L"..\\OutPut\\bin_release\\Content\\SKill\\Kick.bmp");
	m_vecSKillTex[1] = CResMgr::GetInst()->LoadTextur(L"MachKick", L"..\\OutPut\\bin_release\\Content\\SKill\\MachKick.bmp");
	m_vecSKillTex[2] = CResMgr::GetInst()->LoadTextur(L"Windmill", L"..\\OutPut\\bin_release\\Content\\SKill\\Windmill.bmp");
	m_vecSKillTex[3] = CResMgr::GetInst()->LoadTextur(L"RandFire", L"..\\OutPut\\bin_release\\Content\\SKill\\RandomFire.bmp");
	m_vecSKillTex[4] = CResMgr::GetInst()->LoadTextur(L"WalkFire", L"..\\OutPut\\bin_release\\Content\\SKill\\WalkFire.bmp");
	m_vecSKillTex[5] = CResMgr::GetInst()->LoadTextur(L"MultiHead", L"..\\OutPut\\bin_release\\Content\\SKill\\multihead.bmp");

	//�ι�° ��ų
	m_vecSKillTex[6] = CResMgr::GetInst()->LoadTextur(L"rx-78", L"..\\OutPut\\bin_release\\Content\\SKill\\rx-78.bmp");
	m_vecSKillTex[7] = CResMgr::GetInst()->LoadTextur(L"Dropland", L"..\\OutPut\\bin_release\\Content\\SKill\\Dropland.bmp");
	m_vecSKillTex[8] = CResMgr::GetInst()->LoadTextur(L"7ex", L"..\\OutPut\\bin_release\\Content\\SKill\\7ex.bmp");
	m_vecSKillTex[9] = CResMgr::GetInst()->LoadTextur(L"Fire", L"..\\OutPut\\bin_release\\Content\\SKill\\Fire.bmp");
	m_vecSKillTex[10] = CResMgr::GetInst()->LoadTextur(L"exs", L"..\\OutPut\\bin_release\\Content\\SKill\\exs.bmp");
	m_vecSKillTex[11] = CResMgr::GetInst()->LoadTextur(L"Laser", L"..\\OutPut\\bin_release\\Content\\SKill\\laser.bmp");


	m_vecCoolDownTex[0] = CResMgr::GetInst()->LoadTextur(L"Kick_", L"..\\OutPut\\bin_release\\Content\\SKill\\Kick_.bmp");
	m_vecCoolDownTex[1] = CResMgr::GetInst()->LoadTextur(L"MachKick_", L"..\\OutPut\\bin_release\\Content\\SKill\\MachKick_.bmp");
	m_vecCoolDownTex[2] = CResMgr::GetInst()->LoadTextur(L"Windmill_", L"..\\OutPut\\bin_release\\Content\\SKill\\Windmill_.bmp");
	m_vecCoolDownTex[3] = CResMgr::GetInst()->LoadTextur(L"RandFire_", L"..\\OutPut\\bin_release\\Content\\SKill\\RandomFire_.bmp");
	m_vecCoolDownTex[4] = CResMgr::GetInst()->LoadTextur(L"WalkFire_", L"..\\OutPut\\bin_release\\Content\\SKill\\WalkFire_.bmp");
	m_vecCoolDownTex[5] = CResMgr::GetInst()->LoadTextur(L"MultiHead_", L"..\\OutPut\\bin_release\\Content\\SKill\\multihead_.bmp");


	//�ι�° ��ų
	m_vecCoolDownTex[6] = CResMgr::GetInst()->LoadTextur(L"rx-78_", L"..\\OutPut\\bin_release\\Content\\SKill\\rx-78_.bmp");
	m_vecCoolDownTex[7] = CResMgr::GetInst()->LoadTextur(L"Dropland_", L"..\\OutPut\\bin_release\\Content\\SKill\\Dropland_.bmp");
	m_vecCoolDownTex[8] = CResMgr::GetInst()->LoadTextur(L"7ex_", L"..\\OutPut\\bin_release\\Content\\SKill\\7ex_.bmp");
	m_vecCoolDownTex[9] = CResMgr::GetInst()->LoadTextur(L"Fire_", L"..\\OutPut\\bin_release\\Content\\SKill\\Fire_.bmp");
	m_vecCoolDownTex[10] = CResMgr::GetInst()->LoadTextur(L"exs_", L"..\\OutPut\\bin_release\\Content\\SKill\\exs_.bmp");
	m_vecCoolDownTex[11] = CResMgr::GetInst()->LoadTextur(L"Laser_", L"..\\OutPut\\bin_release\\Content\\SKill\\laser_.bmp");


	m_vecNumber.resize(9);
	//�ڽ� ������Ʈ �߰�
	for (int i = 0; i < 9; ++i)
	{
		wstring strNum = std::to_wstring(i + 1);
		m_vecNumber[i] = CResMgr::GetInst()->LoadTextur(L"Number" + strNum, L"..\\OutPut\\bin_release\\Content\\Item\\" + strNum + L".bmp");
	}

	//�������̽� ��ų , ������â
	

}

CInterFace::~CInterFace()
{
	
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
		if (m_vecItem[1] != nullptr)
		{
			m_vecItem[1]->UseItem();
		}
	}

	else if (KEY_TAP(KEY::KEY3))
	{
		if (m_vecItem[2] != nullptr)
		{
			m_vecItem[2]->UseItem();
		}
	}

	else if (KEY_TAP(KEY::KEY4))
	{
		if (m_vecItem[3] != nullptr)
		{
			m_vecItem[3]->UseItem();
		}
	}

	else if (KEY_TAP(KEY::KEY5))
	{
		if (m_vecItem[4] != nullptr)
		{
			m_vecItem[4]->UseItem();
		}
	}

	else if (KEY_TAP(KEY::KEY6))
	{
		if (m_vecItem[5] != nullptr)
		{
			m_vecItem[5]->UseItem();
		}
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

	//�������̽� ���� �׸���
	TransparentBlt(_dc,
		(int)vPos.x, (int)vPos.y,
		m_pInterFaceTex->Width(), m_pInterFaceTex->Height(),
		m_pInterFaceTex->GetDC(),
		0, 0,
		m_pInterFaceTex->Width(), m_pInterFaceTex->Height(),
		RGB(0, 0, 0));

	skillRender(_dc);

	CUI::render(_dc);

	//�������� �׷����� �� ��ü Ű���� �׷�����
	keyRender(_dc);

}

void CInterFace::keyRender(HDC _dc)
{
	Vec2 vStartPos = m_vItemStartPos;
	for (int i = 0; i < 6; ++i)
	{
		CTexture* pNumTex = CKeyMgr::GetInst()->GetKeyTex(m_vecKeyValue[i]);

		TransparentBlt(_dc,
			vStartPos.x + 5, vStartPos.y,
			pNumTex->Width()*1.5, pNumTex->Height()*1.5,
			pNumTex->GetDC(),
			0, 0,
			pNumTex->Width(), pNumTex->Height(),
			RGB(255, 255, 255));

		vStartPos.x += m_vItemStep.x;
	}
	//��ų �׸� ���� ��ġ
	vStartPos = Vec2(758.f, 655.f);
	
	for (int i = 6; i < 12; ++i)
	{
		CTexture* pNumTex = CKeyMgr::GetInst()->GetKeyTex(m_vecKeyValue[i]);

		TransparentBlt(_dc,
			vStartPos.x - 10, vStartPos.y+ 1,
			pNumTex->Width() * 1.7, pNumTex->Height() * 1.6,
			pNumTex->GetDC(),
			0, 0,
			pNumTex->Width(), pNumTex->Height(),
			RGB(255, 255, 255));

		vStartPos.x += m_vItemStep.x;
	}

}

void CInterFace::skillRender(HDC _dc)
{
	// 760 655
	Vec2 vStartPos = Vec2(758.f, 655.f);//��ų ������ �������� ����
	int iStart;
	int iEnd;
	if (CSkillMgr::GetInst()->GetSKillType() == 1)
	{
		iStart = 0; iEnd = 6;
	}
	else
	{
		iStart = 6; iEnd = 12;
	}

	for (iStart; iStart < iEnd; ++iStart)
	{
		//���⿡ ��ų ������ �׸���
		//���⼭ ��ų ��Ÿ�� ��������
		float iSkillTime = CSkillMgr::GetInst()->GetCurSKillTime((SKILL_STATE)iStart);
		//��ų ��Ÿ���� 0�̸�
		if (iSkillTime <= 0.f)
		{
			TransparentBlt(_dc,
				vStartPos.x, vStartPos.y,
				m_vItemStep.x, m_vItemStep.y,
				m_vecSKillTex[iStart]->GetDC(),
				0, 0,
				m_vecSKillTex[iStart]->Width(), m_vecSKillTex[iStart]->Height(),
				RGB(255, 255, 255));
		}
		else
		{
			TransparentBlt(_dc,
				vStartPos.x, vStartPos.y,
				m_vItemStep.x, m_vItemStep.y,
				m_vecCoolDownTex[iStart]->GetDC(),
				0, 0,
				m_vecCoolDownTex[iStart]->Width(), m_vecCoolDownTex[iStart]->Height(),
				RGB(255, 255, 255));


			TransparentBlt(_dc,
				vStartPos.x + 26, vStartPos.y + 10,
				10, 20,
				m_vecNumber[(int)iSkillTime]->GetDC(),
				//�������� ��ǥ���� ������ �̹��� ũ��
				0, 0,
				m_vecNumber[(int)iSkillTime]->Width(), m_vecNumber[(int)iSkillTime]->Height(),
				RGB(255, 255, 255));
		}
		//���� �̹��� ��ġ ���
		vStartPos.x += m_vItemStep.x;
	}
}

