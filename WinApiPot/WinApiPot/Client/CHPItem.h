#pragma once
#include "CItem.h"
class CHPItem :
    public CItem
{
public:
    CHPItem();
    virtual ~CHPItem();

private:
    CTexture* m_pItemTex;

    float m_fHealValue;


public:
    virtual void render(HDC _dc);
    virtual void update();//���
    virtual void finalupdate();

    virtual void UseItem();

public:
    virtual void MouseOn();//UI���� ���콺 �ö���� �� 
    virtual void MouseLbtnDown();//UI�ȿ��� ������ ��
    virtual void MouseLbtnUp();//UI�ȿ��� ���� ��
    virtual void MouseLbtnClicked();//UI�ȿ��� ������ ���� ��

};

