#include "pch.h"
#include "CHP.h"

#include "CResMgr.h"
#include "CTexture.h"

int CHP::m_iMinusHp = 0;

CHP::CHP():
	m_pHPTex(nullptr)
{
	SetName(L"HP");
	m_pHPTex = CResMgr::GetInst()->LoadTextur(L"HP", L"..\\OutPut\\bin_release\\Content\\Interface\\playerHP.bmp");
}

CHP::~CHP()
{
}

void CHP::render(HDC _dc)
{
	Vec2 vPos = GetFinalPos();

	//이미지 크기 정보
	//83 101
	TransparentBlt(_dc,
		(int)vPos.x, (int)vPos.y + m_iMinusHp,
		m_pHPTex->Width(), m_pHPTex->Height() - m_iMinusHp,
		m_pHPTex->GetDC(),
		//시작지점 좌표부터 가져올 이미지 크기
		0, m_iMinusHp,
		m_pHPTex->Width(), m_pHPTex->Height() - m_iMinusHp,
		RGB(0, 0, 0));

	CUI::render(_dc);
}

void CHP::update()
{
	CUI::update();
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
