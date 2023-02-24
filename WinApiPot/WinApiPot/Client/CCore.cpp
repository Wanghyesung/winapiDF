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
	
	//만들어둔 DC와 비트맵 삭제
	DeleteDC(m_memDC);
	DeleteObject(m_hBit);

	//DestroyMenu(m_hMenu); 요건 메뉴바 생기면 하는걸로
}



int CCore::init(HWND _hWnd, POINT _pt)
{
	m_hWnd = _hWnd;
	m_ptResolution = _pt;


	ChangeWindowSize(Vec2((float)m_ptResolution.x, (float)m_ptResolution.y), false);
	

	m_hDC = GetDC(m_hWnd);//내 윈도우 DC값 

	//m_hDC ID를 줌 
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);//목적지 DC에 그릴 비트맵?
	m_memDC = CreateCompatibleDC(m_hDC); // 이렇게 만들어진 비트맵 핸들을 가짐->DleteDC로 지워야함

	

	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit); //만든 비트맵과 핸들값 을 이음
	DeleteObject(hOldBit);//연결하고 바로 삭제

	CreateBrushPen();

	//이중 버퍼 구조를 다 만들고 이제 mgr객체들을 초기화해줌
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CPathMgr::GetInst()->init();
	CCameraMgr::GetInst()->init();
	SceneMgr::GetInst()->init();
	CSkillMgr::GetInst()->init();//스킬 리소스 받아두기

	return S_OK;
}

void CCore::progress()
{
	//mgr업데이트하고 -> 흰화면을 먼저 그림((m_memDC) -> 변경된 값들을 화면에 그림((m_memDC) -> (m_memDC)요기에 움직인 객체들을 그림 -> bitblt으로 원래 보여줘야하는 화면에 그림
	/////////////////MANGERCLASS UPDATE/////////////////////////////
	CTimeMgr::GetInst()->update();
	CKeyMgr::GetInst()->update();

	CCameraMgr::GetInst()->update();
	CSkillMgr::GetInst()->update();
	SceneMgr::GetInst()->update();
	CColliderMgr::GetInst()->update();

	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);//화면에 보여주는 부분이 아니라 다른 프레임의 화면을 지움(1px선 값까지 계산해서)

	SceneMgr::GetInst()->render(m_memDC);
	CCameraMgr::GetInst()->render(m_memDC);

	//그린 값들을 내 메인 Dc에 그려주기
	BitBlt(m_hDC, 0, 0, (long)m_ptResolution.x, (long)m_ptResolution.y,
		m_memDC, 0, 0, SRCCOPY);

	CTimeMgr::GetInst()->render(m_memDC);
	CEventMgr::GetInst()->update();
}

void CCore::ChangeWindowSize(Vec2 _vResolution, bool _bMenu)
{
	RECT rt = {0,0,(long)_vResolution.x, (long)_vResolution.y};

	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, _bMenu);//윈도우를 만들때 두깨도 생각해야 하기 떄문에 왼쪽 아래쪽으로 그 만큼 더해야지 내가 설정한 크기만큼 보장받음

	SetWindowPos(m_hWnd, nullptr, 120, 30, rt.right - rt.left, rt.bottom- rt.top,0);//크기를 보장받기 위해서 -lefr값을 -해줌 bottom도

}

void CCore::CreateBrushPen()
{
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	
	m_arrBrsh[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	m_arrBrsh[(UINT)BRUSH_TYPE::BLACK] = (HBRUSH)GetStockObject(BLACK_BRUSH);
}
