#pragma once
#include "CUI.h"

class CTexture;

class CInterFace :
    public CUI
{

public:
    CInterFace();
    virtual ~CInterFace();

private:
    CTexture* m_pInterFaceTex;

public:
    virtual void MouseOn();//UI���� ���콺 �ö���� �� 
    virtual void MouseLbtnDown();//UI�ȿ��� ������ ��
    virtual void MouseLbtnUp();//UI�ȿ��� ���� ��
    virtual void MouseLbtnClicked();//UI�ȿ��� ������ ���� ��

public:
    virtual void render(HDC _dc);
private:
    


};

