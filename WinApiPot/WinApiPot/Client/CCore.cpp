#include "pch.h"
#include "CCore.h"
#include "CSceneMgr.h"

#include "CScene.h"
#include "CScene_Start.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CPathMgr.h"
#include "CColliderMgr.h"
#include "CCameraMgr.h"
#include "CEventMgr.h"
#include "CSkillMgr.h"


CCore::CCore():
	m_hDC(0),
	m_hWnd(0),
	m_ptResolution{},
	m_hBit(0),
	m_memDC(0)
{

}

CCore::~CCore()
{
	DeleteDC(m_hDC);
	
	//������ DC�� ��Ʈ�� ����
	DeleteDC(m_memDC);
	DeleteObject(m_hBit);

	//DestroyMenu(m_hMenu); ��� �޴��� ����� �ϴ°ɷ�
}



int CCore::init(HWND _hWnd, POINT _pt)
{
	m_hWnd = _hWnd;
	m_ptResolution = _pt;


	ChangeWindowSize(Vec2((float)m_ptResolution.x, (float)m_ptResolution.y), false);
	

	m_hDC = GetDC(m_hWnd);//�� ������ DC�� 

	//m_hDC ID�� �� 
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);//������ DC�� �׸� ��Ʈ��?
	m_memDC = CreateCompatibleDC(m_hDC); // �̷��� ������� ��Ʈ�� �ڵ��� ����->DleteDC�� ��������

	

	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit); //���� ��Ʈ�ʰ� �ڵ鰪 �� ����
	DeleteObject(hOldBit);//�����ϰ� �ٷ� ����

	CreateBrushPen();

	//���� ���� ������ �� ����� ���� mgr��ü���� �ʱ�ȭ����
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CPathMgr::GetInst()->init();
	CCameraMgr::GetInst()->init();
	SceneMgr::GetInst()->init();
	CSkillMgr::GetInst()->init();//��ų ���ҽ� �޾Ƶα�

	return S_OK;
}

void CCore::progress()
{
	//mgr������Ʈ�ϰ� -> ��ȭ���� ���� �׸�((m_memDC) -> ����� ������ ȭ�鿡 �׸�((m_memDC) -> (m_memDC)��⿡ ������ ��ü���� �׸� -> bitblt���� ���� ��������ϴ� ȭ�鿡 �׸�
	/////////////////MANGERCLASS UPDATE/////////////////////////////
	CTimeMgr::GetInst()->update();
	CKeyMgr::GetInst()->update();

	CCameraMgr::GetInst()->update();
	CSkillMgr::GetInst()->update();
	SceneMgr::GetInst()->update();
	CColliderMgr::GetInst()->update();

	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);//ȭ�鿡 �����ִ� �κ��� �ƴ϶� �ٸ� �������� ȭ���� ����(1px�� ������ ����ؼ�)

	SceneMgr::GetInst()->render(m_memDC);
	CCameraMgr::GetInst()->render(m_memDC);

	//�׸� ������ �� ���� Dc�� �׷��ֱ�
	BitBlt(m_hDC, 0, 0, (long)m_ptResolution.x, (long)m_ptResolution.y,
		m_memDC, 0, 0, SRCCOPY);

	CTimeMgr::GetInst()->render(m_memDC);
	CEventMgr::GetInst()->update();
}

void CCore::ChangeWindowSize(Vec2 _vResolution, bool _bMenu)
{
	RECT rt = {0,0,(long)_vResolution.x, (long)_vResolution.y};

	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, _bMenu);//�����츦 ���鶧 �α��� �����ؾ� �ϱ� ������ ���� �Ʒ������� �� ��ŭ ���ؾ��� ���� ������ ũ�⸸ŭ �������

	SetWindowPos(m_hWnd, nullptr, 120, 30, rt.right - rt.left, rt.bottom- rt.top,0);//ũ�⸦ ����ޱ� ���ؼ� -lefr���� -���� bottom��

}

void CCore::CreateBrushPen()
{
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	
	m_arrBrsh[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	m_arrBrsh[(UINT)BRUSH_TYPE::BLACK] = (HBRUSH)GetStockObject(BLACK_BRUSH);
}
