#include "pch.h"
#include "CMonInterface.h"

#include "CInterfaceMgr.h"
#include "CMonHP.h"

#include "CResMgr.h"
#include "CTexture.h"



CMonInterface::CMonInterface(const wstring& _strMonName, bool _bIsBoss):
	m_strMonName(_strMonName)
{
	//네임은 동적할당하고 다음에 설정
	//보스면 HP텍스쳐까지 바꿔줌
	if (_bIsBoss)
	{
		CInterfaceMgr::GetInst()->AddMonInterface(_strMonName, this);
		CMonHP* pHP = new CMonHP;
		pHP->SetUIOffset(Vec2(32.f, 1.f));
		pHP->SetName(L"HP");
		AddChildUI(pHP);
		m_pInterfaceTex = CResMgr::GetInst()->LoadTextur(L"BossInterface", L"..\\OutPut\\bin_release\\Content\\Interface\\BossInterface.bmp");
		pHP->m_pHPTex = CResMgr::GetInst()->LoadTextur(L"BossHp", L"..\\OutPut\\bin_release\\Content\\Interface\\BossHP.bmp");
	}
	else
	{
		CInterfaceMgr::GetInst()->AddMonInterface(_strMonName, this);
		CMonHP* pHP = new CMonHP;
		pHP->SetName(L"HP");
		AddChildUI(pHP);
		m_pInterfaceTex = CResMgr::GetInst()->LoadTextur(L"MonInterface", L"..\\OutPut\\bin_release\\Content\\Interface\\MonInterface.bmp");
	}

	m_pDleTex = CResMgr::GetInst()->LoadTextur(L"MonHp", L"..\\OutPut\\bin_release\\Content\\Interface\\DeleteMon.bmp");
}

CMonInterface::~CMonInterface()
{

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
		if (fValue >= fFullValue)
		{
			CInterfaceMgr::GetInst()->deleteInterface(m_strMonName);
		}
	}
}

void CMonInterface::renderHp(HDC _dc)
{
	Vec2 vPos = GetFinalPos();
	
	TransparentBlt(_dc,
		(int)vPos.x, (int)vPos.y,
		m_pInterfaceTex->Width(), m_pInterfaceTex->Height(),
		m_pInterfaceTex->GetDC(),
		0, 0,
		m_pInterfaceTex->Width(), m_pInterfaceTex->Height(),
		RGB(255, 255, 255));

	//CUI::render(_dc);

	CMonHP* pHP = ((CMonHP*)GetChildUI(L"HP"));

	//내 인터페이스 그리고 hp그리기
	if (pHP != nullptr)
	{
		pHP->render_hp(_dc);
	}
}
