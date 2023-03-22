#include "pch.h"
#include "CTimeMgr.h"

#include "CCore.h"
#include "CKeyMgr.h"

//c+ s
CTimeMgr::CTimeMgr():
	m_dAcc(0),
	m_dDT(0),
	m_iCallCount(0),
	m_llCurCount{},
	m_llFrequency{},
	m_llPrevCount{}
{
}

CTimeMgr::~CTimeMgr()
{

}


void CTimeMgr::update()
{
	QueryPerformanceCounter(&m_llCurCount); //���� ī��Ʈ ��

	//���� ������ - ���������� / ��ü ī��Ʈ��
	m_dDT = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequency.QuadPart;
	m_llPrevCount = m_llCurCount;
//#ifdef _DEBUG
//	if (m_dDT >= (1. / 60.))
//		m_dDT = 1. / 60.;
//
//#endif	

}

void CTimeMgr::render(HDC _dc)
{
	++m_iCallCount;
	m_dAcc += m_dDT;

	if (m_dAcc >= 1.f)
	{
		m_iFPS = m_iCallCount;
		m_dAcc = 0;
		m_iCallCount = 0;
		Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos();

		//18 175 
		wchar_t szBuffer[256] = {};
		//swprintf_s(szBuffer, L"FPS : %d, DT : %f", m_iFPS, m_dDT);
		swprintf_s(szBuffer, L"FPS : %d, DT : %f, MousePos X : %f, Y : %f",m_iFPS, m_dDT, vMousePos.x, vMousePos.y);
		SetWindowText(CCore::GetInst()->GetMainHwnd(), szBuffer);
	}
}

void CTimeMgr::init()
{
	QueryPerformanceCounter(&m_llPrevCount);//���� ī��Ʈ

	QueryPerformanceFrequency(&m_llFrequency);//����� 1�ʴ� ī��Ʈ�� �󸶳� �������� ��ü ī��Ʈ 
}
