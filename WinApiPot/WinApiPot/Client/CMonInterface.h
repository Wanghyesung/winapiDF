#pragma once
#include "CUI.h"

class CTexture;

class CMonInterface :
    public CUI
{
public:
    CMonInterface(const wstring& _strMonName);
    virtual ~CMonInterface();

private:
    CTexture* m_pInterfaceTex;
    CTexture* m_pDleTex;

    bool    m_bActiv;

public:
    virtual void render(HDC _dc) {};
    virtual void update();//���
    virtual void finalupdate();

public:
    virtual void MouseOn();//UI���� ���콺 �ö���� �� 
    virtual void MouseLbtnDown();//UI�ȿ��� ������ ��
    virtual void MouseLbtnUp();//UI�ȿ��� ���� ��
    virtual void MouseLbtnClicked();//UI�ȿ��� ������ ���� ��

private:
    void changeValue(float _fHpValue);
    void renderHp(HDC _dc);

    friend class CInterfaceMgr;


};

