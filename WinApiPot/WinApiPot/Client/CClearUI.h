#pragma once
#include "CUI.h"

class CDungeonMgr;

class CClearUI :
    public CUI
{
public:
    CClearUI();
    virtual ~CClearUI();

private:
    bool m_bActive;
    CTexture* m_pUITex;

public:
    virtual void MouseOn();//UI���� ���콺 �ö���� �� 
    virtual void MouseLbtnDown();//UI�ȿ��� ������ ��
    virtual void MouseLbtnUp();//UI�ȿ��� ���� ��
    virtual void MouseLbtnClicked();//UI�ȿ��� ������ ���� ��

public:
    virtual void render(HDC _dc);
    virtual void update();//���
    virtual void finalupdate();

    void Create();//�ڽ�UI�� �̸� ����

    friend class CDungeonMgr;
};

