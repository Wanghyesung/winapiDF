#pragma once
#include "CUI.h"

class CItem;

class CInventory :
    public CUI
{
public:
    CInventory();
    virtual ~CInventory();

private:
    //Ȱ��ȭ
    CTexture* m_pInvenTex;
    bool m_bActive;

    //�� �κ��丮�� �����۵�
    map<wstring, CItem*> m_mapInventory;

public:
    virtual void render(HDC _dc);
    virtual void update();//���
    virtual void finalupdate();

public:
    virtual void MouseOn();//UI���� ���콺 �ö���� �� 
    virtual void MouseLbtnDown();//UI�ȿ��� ������ ��
    virtual void MouseLbtnUp();//UI�ȿ��� ���� ��
    virtual void MouseLbtnClicked();//UI�ȿ��� ������ ���� ��

    friend class CInventoryMgr;
};
