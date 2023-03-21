#include "pch.h"
#include "CMP.h"

#include "CResMgr.h"
#include "CTexture.h"

int CMP::m_iMinusMp = 0;

CMP::CMP():
	m_pMPTex(nullptr)
{
	SetName(L"MP");
	m_pMPTex = CResMgr::GetInst()->LoadTextur(L"MP", L"..\\OutPut\\bin_release\\Content\\Interface\\playerMP.bmp");

	SetScale(Vec2(74.f, 88.f));
}

CMP::~CMP()
{

}

void CMP::render(HDC _dc)
{
	Vec2 vPos = GetFinalPos();

	//이미지 크기 정보
	//83 101
	TransparentBlt(_dc,
		(int)vPos.x, (int)vPos.y + m_iMinusMp,
		m_pMPTex->Width(), m_pMPTex->Height() - m_iMinusMp,
		m_pMPTex->GetDC(),
		//시작지점 좌표부터 가져올 이미지 크기
		0, m_iMinusMp,
		m_pMPTex->Width(), m_pMPTex->Height() - m_iMinusMp,
		RGB(0, 0, 0));

	CUI::render(_dc);
}

void CMP::update()
{

}

void CMP::MouseOn()
{
}

void CMP::MouseLbtnDown()
{
}

void CMP::MouseLbtnUp()
{
}

void CMP::MouseLbtnClicked()
{
}
