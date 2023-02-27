#include "pch.h"
#include "CInterFace.h"

#include "CResMgr.h"
#include "CTexture.h"

#include "CObject.h"

CInterFace::CInterFace():
	m_pInterFaceTex(nullptr)
{
	m_pInterFaceTex = CResMgr::GetInst()->LoadTextur(L"InterFace", L"..\\OutPut\\bin_release\\Content\\Interface//interface.bmp");
}

CInterFace::~CInterFace()
{

}

void CInterFace::MouseOn()
{
	int a = 10;
}

void CInterFace::MouseLbtnDown()
{
	int a = 10;
}

void CInterFace::MouseLbtnUp()
{

}

void CInterFace::MouseLbtnClicked()
{

}

void CInterFace::render(HDC _dc)
{
	CUI::render(_dc);

	Vec2 vPos = GetPos();

	TransparentBlt(_dc,
		(int)vPos.x, (int)vPos.y,
		m_pInterFaceTex->Width(), m_pInterFaceTex->Height(),
		m_pInterFaceTex->GetDC(),
		0, 0,
		m_pInterFaceTex->Width(), m_pInterFaceTex->Height(),
		RGB(0, 0, 0));

}
