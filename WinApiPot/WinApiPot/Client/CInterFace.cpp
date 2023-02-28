#include "pch.h"
#include "CInterFace.h"

#include "CResMgr.h"
#include "CTexture.h"

#include "CObject.h"

CInterFace::CInterFace():
	m_pInterFaceTex(nullptr)
{
	m_pInterFaceTex = CResMgr::GetInst()->LoadTextur(L"InterFace", L"..\\OutPut\\bin_release\\Content\\Interface//interface.bmp");
	//m_pHPTex = CResMgr::GetInst()->LoadTextur(L"HP", L"..\\OutPut\\bin_release\\Content\\Interface//HP.bmp");
	//m_pMPTex = CResMgr::GetInst()->LoadTextur(L"MP", L"..\\OutPut\\bin_release\\Content\\Interface//MP.bmp");
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
