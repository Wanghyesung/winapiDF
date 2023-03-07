#include "pch.h"
#include "CInterFace.h"

#include "CResMgr.h"
#include "CTexture.h"

#include "CObject.h"
#include "CHP.h"
#include "CMP.h"


CInterFace::CInterFace():
	m_pInterFaceTex(nullptr)
{
	SetName(L"InterFace");
	m_pInterFaceTex = CResMgr::GetInst()->LoadTextur(L"InterFace", L"..\\OutPut\\bin_release\\Content\\Interface//interface.bmp");
	
	//hp 자식 ui로 가지고있기
}

CInterFace::~CInterFace()
{
	
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

void CInterFace::ChangeValue(float _HPfValue, float _MPfValue)
{
	
	if (dynamic_cast<CHP*>(GetChildUI(L"HP")))
	{
		CHP* pHP = dynamic_cast<CHP*>(GetChildUI(L"HP"));
		float fHpValue = ((100.f - _HPfValue) / 101.f) * 100.f;
		pHP->SetMinusHp(fHpValue);
	
	}
	if (dynamic_cast<CMP*>(GetChildUI(L"MP")))
	{
		CMP* pMP = dynamic_cast<CMP*>(GetChildUI(L"MP"));
		float fValue = ((100.f - _MPfValue) / 101.f) * 100.f;
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
