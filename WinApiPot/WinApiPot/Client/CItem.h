#pragma once
#include "CUI.h"

class CInventory;
class CInterFace;
class CItemMgr;

class CItem :
    public CUI
{
public:
    CItem();
    virtual ~CItem();

private:
    tItemInfo m_tItemInfo;

    //Ȱ��ȭ
    bool m_bActive;
    bool m_bTargetOn;
    
    //���� ���� �����ϰ��ִ� ���� 
    //�������̽��� ũ�� ����

    //���� �̹��� ����
    vector<CTexture*> m_vecNumber;

protected:
    ITEM_TYPE m_eItemType;

    UINT m_iItemCount;

    bool m_bIsInterfacePos;

    //�������̽��� ���� Ŀ����
    int m_iWidth;//�� �̹��� ����
    int m_iHeight;//�� �̹��� ����

    int m_iNumberWidth; 
    int m_iNumberHeight;

private:
    Vec2 m_vDragStartPos;
    Vec2 m_vDragePrePos;

    CInventory* m_pInven;

    //�̹��� ��������� ũ��
    Vec2 m_vOffsetScale;

protected:
    CInventory* GetInventory() { return m_pInven; }
    Vec2 GetOffsetScale() { return m_vOffsetScale; }

    void deleteItem();

public:
    virtual void render(HDC _dc);
    virtual void update();//���
    virtual void finalupdate();

    virtual void UseItem() = 0;

public:
    virtual void MouseOn();//UI���� ���콺 �ö���� �� 
    virtual void MouseLbtnDown();//UI�ȿ��� ������ ��
    virtual void MouseLbtnUp();//UI�ȿ��� ���� ��
    virtual void MouseLbtnClicked();//UI�ȿ��� ������ ���� ��

public:
    void SetItemName(const wstring& _strName) { m_tItemInfo.m_strName = _strName; }
    const wstring& GetItemName() { return m_tItemInfo.m_strName; }

private:
    tItemInfo& GetItemInfo() { return m_tItemInfo; }
    const UINT& GetItemqQantity() { return m_iItemCount; }

    void SetItemScale(Vec2 _vScale);


    friend class CItemMgr;
    friend class CInventory;
    friend class CInterFace;
};

