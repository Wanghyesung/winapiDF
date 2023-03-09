#pragma once
#include "CUI.h"
class CTexture;

class CHP :
    public CUI
{

public:
    CHP();
    virtual ~CHP();

private:
    CTexture* m_pHPTex;

    static int m_iMinusHp;

public:
    virtual void render(HDC _dc);
    virtual void update();//���


public:
    virtual void MouseOn();//UI���� ���콺 �ö���� �� 
    virtual void MouseLbtnDown();//UI�ȿ��� ������ ��
    virtual void MouseLbtnUp();//UI�ȿ��� ���� ��
    virtual void MouseLbtnClicked();//UI�ȿ��� ������ ���� ��

private:
    void SetMinusHp(float _fHp) { m_iMinusHp = _fHp; }

    friend class CInterFace;
};

