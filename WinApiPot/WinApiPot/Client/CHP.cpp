#include "pch.h"
#include "CHP.h"

#include "CResMgr.h"
#include "CTexture.h"

CHP::CHP():
	m_pHPTex(nullptr),
	m_iMinusHp(0)
{
	m_pHPTex = CResMgr::GetInst()->LoadTextur(L"HP", L"..\\OutPut\\bin_release\\Content\\Interface\\HP.bmp");
}

CHP::~CHP()
{
}

void CHP::render(HDC _dc)
{
	Vec2 vPos = GetFinalPos();

	TransparentBlt(_dc,
		(int)vPos.x, (int)vPos.y,
		m_pHPTex->Width(), m_pHPTex->Height(),
		m_pHPTex->GetDC(),
		//시작지점 좌표부터 가져올 이미지 크기
		0, m_iMinusHp,
		m_pHPTex->Width(), m_pHPTex->Height()- m_iMinusHp,
		RGB(0, 0, 0));

	CUI::render(_dc);
}

void CHP::update()
{

}

void CHP::MouseOn()
{
}

void CHP::MouseLbtnDown()
{
}

void CHP::MouseLbtnUp()
{
}

void CHP::MouseLbtnClicked()
{
}
