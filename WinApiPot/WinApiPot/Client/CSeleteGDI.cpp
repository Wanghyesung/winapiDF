#include "pch.h"
#include "CSeleteGDI.h"

#include "CCore.h"

CSeleteGDI::CSeleteGDI(HDC _dc, BRUSH_TYPE _eBrushType):
	m_dc(_dc),
	m_hDefalutBrush(nullptr),
	m_hDefalutPen(nullptr)
{
	HBRUSH m_hBrushType = CCore::GetInst()->GetBRUSH(_eBrushType);
	m_hDefalutBrush = (HBRUSH)SelectObject(m_dc, m_hBrushType);
}

CSeleteGDI::CSeleteGDI(HDC _dc, PEN_TYPE _ePenType):
	m_dc(_dc),
	m_hDefalutBrush(nullptr),
	m_hDefalutPen(nullptr)
{
	HPEN m_hPenType = CCore::GetInst()->GetPen(_ePenType);
	m_hDefalutPen = (HPEN)SelectObject(m_dc, m_hPenType);
}

CSeleteGDI::~CSeleteGDI()
{
	SelectObject(m_dc, m_hDefalutPen);
	SelectObject(m_dc, m_hDefalutBrush);
}
