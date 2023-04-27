#include "pch.h"
#include "CMonInterface.h"

#include "CInterfaceMgr.h"
#include "CMonHP.h"

#include "CResMgr.h"
#include "CTexture.h"



CMonInterface::CMonInterface(const wstring& _strMonName, UINT _MonNum, bool _bIsBoss):
	m_strMonName(_strMonName)
{
	//������ �����Ҵ��ϰ� ������ ����
	//������ HP�ؽ��ı��� �ٲ���
	if (_bIsBoss)
	{
		CInterfaceMgr::GetInst()->AddMonInterface(_strMonName, this);
		CMonHP* pHP = new CMonHP;
		pHP->SetUIOffset(Vec2(32.f, 2.f));
		pHP->SetName(L"HP");
		pHP->SetScale(Vec2(590.f, 33.f));
		AddChildUI(pHP);
		m_pInterfaceTex = CResMgr::GetInst()->LoadTextur(L"BossInterface", L"..\\OutPut\\bin_release\\Content\\Interface\\BossInterface.bmp");
		pHP->m_pHPTex = CResMgr::GetInst()->LoadTextur(L"BossHp", L"..\\OutPut\\bin_release\\Content\\Interface\\BossHP.bmp");

		SetScale(Vec2(630.f, 33.f));
	}
	else
	{
		CInterfaceMgr::GetInst()->AddMonInterface(_strMonName, this);
		CMonHP* pHP = new CMonHP;
		pHP->SetName(L"HP");
		AddChildUI(pHP);
		m_pInterfaceTex = CResMgr::GetInst()->LoadTextur(L"MonInterface", L"..\\OutPut\\bin_release\\Content\\Interface\\MonInterface.bmp");
		SetScale(Vec2(626.f, 29.f));
	}

	//���� �̹���bmp�̸�
	m_iMonTexNum = _MonNum;
	m_pDleTex = CResMgr::GetInst()->LoadTextur(L"MonHp", L"..\\OutPut\\bin_release\\Content\\Interface\\DeleteMon.bmp");
}

CMonInterface::~CMonInterface()
{
	int a = 10;
}


void CMonInterface::update()
{
	CUI::update();
}

void CMonInterface::finalupdate()
{
	CUI::finalupdate();
}

void CMonInterface::MouseOn()
{
}

void CMonInterface::MouseLbtnDown()
{
}

void CMonInterface::MouseLbtnUp()
{
}

void CMonInterface::MouseLbtnClicked()
{
}


void CMonInterface::changeValue(float _fHpValue)
{
	CMonHP* pHP = ((CMonHP*)GetChildUI(L"HP"));

	float fFullValue = pHP->m_pHPTex->Width();
	if (pHP != nullptr)
	{
		float fValue = ((100.f - _fHpValue) / 100.f * fFullValue);
		pHP->SetMinusHp(fValue);
		/*if (0.f >= _fHpValue)
		{
			CInterfaceMgr::GetInst()->deleteInterface(m_strMonName);
		}*/
	}
}

void CMonInterface::renderHp(HDC _dc)
{
	Vec2 vPos = GetFinalPos();
	

	//�������̽�
	TransparentBlt(_dc,
		(int)vPos.x, (int)vPos.y,
		m_pInterfaceTex->Width(), m_pInterfaceTex->Height(),
		m_pInterfaceTex->GetDC(),
		0, 0,
		m_pInterfaceTex->Width(), m_pInterfaceTex->Height(),
		RGB(255, 255, 255));

	//���� �̹���
	wstring strNum = std::to_wstring(m_iMonTexNum);
	CTexture* pMonInterface =
		CResMgr::GetInst()->LoadTextur(strNum, L"..\\OutPut\\bin_release\\Content\\MonIterface\\" + strNum + L".bmp");

	TransparentBlt(_dc,
		(int)vPos.x + 3, (int)vPos.y + 3,
		pMonInterface->Width(), pMonInterface->Height(),
		pMonInterface->GetDC(),
		0, 0,
		pMonInterface->Width(), pMonInterface->Height(),
		RGB(0, 0, 0));


	//CUI::render(_dc);

	CMonHP* pHP = ((CMonHP*)GetChildUI(L"HP"));

	//�� �������̽� �׸��� hp�׸���
	if (pHP != nullptr)
	{
		pHP->render_hp(_dc);
	}
}
