#include "pch.h"
#include "CMonHP.h"

#include "CResMgr.h"
#include "CTexture.h"

CMonHP::CMonHP():
	m_fHp(0),
	m_pHPTex(nullptr),
	m_vUIOffset(Vec2(28.f, 17.f))
{
	m_pHPTex = CResMgr::GetInst()->LoadTextur(L"MonHp", L"..\\OutPut\\bin_release\\Content\\Interface\\MonHP.bmp");

	SetScale(Vec2(597.f, 9.f));

}

CMonHP::~CMonHP()
{

}

void CMonHP::render(HDC _dc)
{
	//Vec2 vPos = GetFinalPos();

	//�̹��� ũ�� ����
	//
	//TransparentBlt(_dc,
	//	(int)vPos.x, (int)vPos.y + m_fHp,
	//	m_pHPTex->Width(), m_pHPTex->Height() - m_fHp,
	//	m_pHPTex->GetDC(),
	//	//�������� ��ǥ���� ������ �̹��� ũ��
	//	0, m_fHp,
	//	m_pHPTex->Width(), m_pHPTex->Height() - m_fHp,
	//	RGB(0, 0, 0));

	CUI::render(_dc);
}

void CMonHP::update()
{
	CUI::update();
}

void CMonHP::finalupdate()
{
	CUI::finalupdate();
}

void CMonHP::render_hp(HDC _dc)
{
	Vec2 vPos = GetFinalPos();

	//offset
	vPos += m_vUIOffset;
	TransparentBlt(_dc,
		(int)vPos.x , (int)vPos.y,
		m_pHPTex->Width() - m_fHp, m_pHPTex->Height() ,
		m_pHPTex->GetDC(),
		//�������� ��ǥ���� ������ �̹��� ũ��
		m_fHp, 0,
		m_pHPTex->Width() - m_fHp, m_pHPTex->Height(),
		RGB(0, 0, 0));
}



void CMonHP::MouseOn()
{
}

void CMonHP::MouseLbtnDown()
{
}

void CMonHP::MouseLbtnUp()
{
}

void CMonHP::MouseLbtnClicked()
{
}
