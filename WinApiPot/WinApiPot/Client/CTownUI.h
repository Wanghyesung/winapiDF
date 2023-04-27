#pragma once
#include "CUI.h"
class CTownUI :
    public CUI
{
public:
    CTownUI();
    virtual ~CTownUI();

private:
    CTexture* pMouseNoneTex;
    CTexture* pMouseOnTex;
    CTexture* pMousePushTex;

    bool m_bMouseOn;
    bool m_bMousePush;

public:
    virtual void MouseOn();//UI���� ���콺 �ö���� �� 
    virtual void MouseLbtnDown();//UI�ȿ��� ������ ��
    virtual void MouseLbtnUp();//UI�ȿ��� ���� ��
    virtual void MouseLbtnClicked();//UI�ȿ��� ������ ���� ��

public:
    virtual void render(HDC _dc);
    virtual void update();//���
    virtual void finalupdate();
};

