#pragma once
#include "CUI.h"
class CMP :
    public CUI
{
public:
    CMP();
    virtual ~CMP();

private:
    CTexture* m_pMPTex;

    int m_iMinusMp;

public:
    virtual void render(HDC _dc);
    virtual void update();//���

public:
    virtual void MouseOn();//UI���� ���콺 �ö���� �� 
    virtual void MouseLbtnDown();//UI�ȿ��� ������ ��
    virtual void MouseLbtnUp();//UI�ȿ��� ���� ��
    virtual void MouseLbtnClicked();//UI�ȿ��� ������ ���� ��


};

