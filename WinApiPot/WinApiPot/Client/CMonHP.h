#pragma once
#include "CUI.h"
class CMonHP :
    public CUI
{
public:
    CMonHP();
    virtual ~CMonHP();

private:
    CTexture* m_pHPTex;

    float   m_fHp;
public:
    virtual void render(HDC _dc);
    virtual void update();//���
    virtual void finalupdate();

    void render_hp(HDC _dc);

public:
    virtual void MouseOn();//UI���� ���콺 �ö���� �� 
    virtual void MouseLbtnDown();//UI�ȿ��� ������ ��
    virtual void MouseLbtnUp();//UI�ȿ��� ���� ��
    virtual void MouseLbtnClicked();//UI�ȿ��� ������ ���� ��

private:
    void SetMinusHp(float _fValue) { m_fHp = _fValue; }

    friend class CMonInterface;
};

