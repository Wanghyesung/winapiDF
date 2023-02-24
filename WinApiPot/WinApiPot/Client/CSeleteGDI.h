#pragma once
class CSeleteGDI
{
public:
	CSeleteGDI(HDC _dc, BRUSH_TYPE _eBrushType);
	CSeleteGDI(HDC _dc, PEN_TYPE _ePenType);
	~CSeleteGDI();

private:
	HDC m_dc;
	HPEN m_hDefalutPen;
	HBRUSH m_hDefalutBrush;
};

