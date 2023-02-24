#pragma once

class CCore
{
	SINGLE(CCore);

private:
	HWND			m_hWnd;//�� ������ �ڵ鰪
	POINT			m_ptResolution; // ���� ������ �ػ�;
	HDC				m_hDC;//�� ������ DC��
	HMENU			m_hMenu;


	//���� ���ۿ� �ʿ��� ��Ʈ�ʰ� �ش� ��Ʈ���� ����ų DC��
	HBITMAP			m_hBit; //��Ʈ�� �ڵ鰪 
	HDC				m_memDC; //�׸��� �ڵ鰪

	HBRUSH m_arrBrsh[(UINT)BRUSH_TYPE::END];
	HPEN   m_arrPen[(UINT)PEN_TYPE::END];

public:
	int init(HWND _hWnd, POINT _pt); //Core��ü �ʱ�ȭ
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

