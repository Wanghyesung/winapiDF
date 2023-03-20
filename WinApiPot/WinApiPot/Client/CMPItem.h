#pragma once
#include "CItem.h"
class CMPItem :
    public CItem
{
public:
    CMPItem();
    virtual ~CMPItem();

private:
    CTexture* m_pItemTex;

    Vec2 m_vDragStartPos;

public:
    virtual void render(HDC _dc);
    virtual void update();//���
    virtual void finalupdate();

public:
    virtual void MouseOn();//UI���� ���콺 �ö���� �� 
    virtual void MouseLbtnDown();//UI�ȿ��� ������ ��
    virtual void MouseLbtnUp();//UI�ȿ��� ���� ��
    virtual void MouseLbtnClicked();//UI�ȿ��� ������ ���� ��
};
