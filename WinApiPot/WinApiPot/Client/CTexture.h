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
    BITMAP m_bitInfo;//��Ʈ�� ����
    
public:
    void Create(UINT _iWidth, UINT _iHeight);//������� �ؽ����� 
    void Load(const wstring& _strFilePath);//��� �������� ResMgr���� ��θ� ��������

    UINT Width() { return m_bitInfo.bmWidth; }
    UINT Height() { return m_bitInfo.bmHeight; }

    HDC GetDC() { return m_dc; }

    friend class CResMgr;
};

