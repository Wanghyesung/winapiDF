#pragma once
#include "CRes.h"
class CTexture :
    public CRes
{
private:
    CTexture();
    virtual ~CTexture();


private:
    HDC  m_dc;
    HBITMAP m_hBit;
    BITMAP m_bitInfo;//비트맵 정보
    
public:
    void Create(UINT _iWidth, UINT _iHeight);//만들어진 텍스쳐의 
    void Load(const wstring& _strFilePath);//경로 가져오기 ResMgr에서 경로를 가져오기

    UINT Width() { return m_bitInfo.bmWidth; }
    UINT Height() { return m_bitInfo.bmHeight; }

    HDC GetDC() { return m_dc; }

    friend class CResMgr;
};

