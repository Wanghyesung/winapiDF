#pragma once
#include "CUI.h"

class CItem;
class CInvenIcon;

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

    Vec2 m_vStartPos;
    Vec2 m_vEndPos;
    Vec2 m_vStep;

public:
    CItem* FindItem(const wstring& _strName);
    void AddItem(CItem* _pItem);

    void ChangeItemPos(CItem* _pItem);

    Vec2 GetStartPos() { return m_vStartPos; }
    Vec2 GetEndPos() { return m_vEndPos; }



public:
    virtual void render(HDC _dc);
    virtual void update();//���
    virtual void finalupdate();

public:
    virtual void MouseOn();//UI���� ���콺 �ö���� �� 
    virtual void MouseLbtnDown();//UI�ȿ��� ������ ��
    virtual void MouseLbtnUp();//UI�ȿ��� ���� ��
    virtual void MouseLbtnClicked();//UI�ȿ��� ������ ���� ��

    void DeleteItem(CItem* _pItem);

private:
    bool IsSamePos(Vec2 _vPos);
    CItem* GetItemThisPos(Vec2 _vPos);

    void changeInterface(CItem* _pItem, CItem* _pOtherItem, Vec2 _vOtherDragePrePos);

    friend class CInventoryMgr;
    friend class CInvenIcon;
};

