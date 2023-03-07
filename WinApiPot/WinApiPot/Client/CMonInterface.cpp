#include "pch.h"
#include "CMonInterface.h"

#include "CInterfaceMgr.h"
#include "CMonHP.h"

#include "CResMgr.h"
#include "CTexture.h"



CMonInterface::CMonInterface(const wstring& _strMonName)
{
	//네임은 동적할당하고 다음에 설정
	CInterfaceMgr::GetInst()->AddMonInterface(_strMonName, this);
	CMonHP* pHP = new CMonHP;
	pHP->SetName(L"HP");
	AddChildUI(pHP);

	m_pInterfaceTex = CResMgr::GetInst()->LoadTextur(L"MonInterface", L"..\\OutPut\\bin_release\\Content\\Interface\\MonInterface.bmp");
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

	if (pHP != nullptr)
	{
		float fValue = ((100.f - _fHpValue) / 100.f * 626.f);
		pHP->SetMinusHp(fValue);
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
