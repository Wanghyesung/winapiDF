#pragma once
#include "CUI.h"

class CInventory;
class CInterFace;


class CItem :
    public CUI
{
public:
    CItem();
    virtual ~CItem();

private:
    tItemInfo m_tItemInfo;
    UINT m_iItemCount;

    //Ȱ��ȭ
    bool m_bActive;
    bool m_bTargetOn;
    
    //���� ���� �����ϰ��ִ� ���� 
    //�������̽��� ũ�� ����
    bool m_bIsInterfacePos;

    Vec2 m_vDragStartPos;
    Vec2 m_vDragePrePos;

    CInventory* m_pInven;

    //�̹��� ��������� ũ��
    Vec2 m_vOffsetScale;

protected:
    CInventory* GetInventory() { return m_pInven; }
    Vec2 GetOffsetScale() { return m_vOffsetScale; }

public:
    virtual void render(HDC _dc);
    virtual void update();//���
    virtual void finalupdate();

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


    friend class CInventory;
    friend class CInterFace;
};

