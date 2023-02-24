#pragma once

class CCore
{
	SINGLE(CCore);

private:
	HWND			m_hWnd;//내 윈도우 핸들값
	POINT			m_ptResolution; // 메인 윈도우 해상도;
	HDC				m_hDC;//내 윈도우 DC값
	HMENU			m_hMenu;


	//이중 버퍼에 필요한 비트맵과 해당 비트맵을 가르킬 DC값
	HBITMAP			m_hBit; //비트맵 핸들값 
	HDC				m_memDC; //그리기 핸들값

	HBRUSH m_arrBrsh[(UINT)BRUSH_TYPE::END];
	HPEN   m_arrPen[(UINT)PEN_TYPE::END];

public:
	int init(HWND _hWnd, POINT _pt); //Core객체 초기화
	void progress();


public:
	void ChangeWindowSize(Vec2 _vResolution, bool _bMenu);
	HWND GetMainHwnd() { return m_hWnd; }
	HDC GetMainDC() { return m_hDC; }

	HPEN GetPen(PEN_TYPE _ePenType) { return m_arrPen[(UINT)_ePenType];}
	HBRUSH GetBRUSH(BRUSH_TYPE _eBrushType) { return m_arrBrsh[(UINT)_eBrushType]; }

	Vec2 GetResolution() { return Vec2(m_ptResolution); }
public:
	void CreateBrushPen();
};

