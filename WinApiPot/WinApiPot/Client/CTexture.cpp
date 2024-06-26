#include "pch.h"
#include "CTexture.h"

#include "CCore.h"

CTexture::CTexture():
	m_dc(0),
	m_hBit(0),
	m_bitInfo{}
{
}

CTexture::~CTexture()
{
	DeleteDC(m_dc);
	DeleteObject(m_hBit);
}

void CTexture::Load(const wstring& _strRelativePath)
{
	m_hBit = (HBITMAP)LoadImageW(nullptr
		, _strRelativePath.c_str(), IMAGE_BITMAP
		, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	assert(m_hBit);

	m_dc = CreateCompatibleDC(CCore::GetInst()->GetMainDC());

	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_dc, m_hBit);
	DeleteObject(hPrevBit);

	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);
}


COLORREF CTexture::GetPixel(int x, int y)
{
	return ::GetPixel(m_dc, x, y);
}

void CTexture::SetPixle(int x, int y, COLORREF _color)
{
	::SetPixel(m_dc, x, y, _color);
}

void CTexture::Create(UINT _iWidth, UINT _iHeight)
{
	HDC mainDc = CCore::GetInst()->GetMainDC();

	m_hBit = CreateCompatibleBitmap(mainDc, _iWidth, _iHeight);

	m_dc = CreateCompatibleDC(mainDc);

	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_dc, m_hBit);
	DeleteObject(hPrevBit);

	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);
}


