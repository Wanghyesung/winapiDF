#pragma once
#include "CUI.h"

class CTexture;

class CMonInterface :
    public CUI
{
public:
    CMonInterface(const wstring& _strMonName, bool _bIsBoss = false);
    virtual ~CMonInterface();

private:
    CTexture* m_pInterfaceTex;
    CTexture* m_pDleTex;

    wstring m_strMonName;//�� ���� �̸�
    bool    m_bActiv;

public:
    virtual void render(HDC _dc) {};
    virtual void update();//���
    virtual void finalupdate();

    const wstring& GetMonName() { return m_strMonName; }

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

