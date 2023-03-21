#pragma once
#include "CUI.h"

class CInventory;

class CItem :
    public CUI
{
public:
    CItem();
    virtual ~CItem();

private:
    tItemInfo m_tItemInfo;
    UINT m_iItemCount;

    //활성화
    bool m_bActive;
    bool m_bTargetOn;
    Vec2 m_vDragStartPos;
    Vec2 m_vDragePrePos;

    CInventory* m_pInven;

protected:
    CInventory* GetInventory() { return m_pInven; }

public:
    virtual void render(HDC _dc);
    virtual void update();//상속
    virtual void finalupdate();

public:
    virtual void MouseOn();//UI위에 마우스 올라왔을 떄 
    virtual void MouseLbtnDown();//UI안에서 눌렸을 떄
    virtual void MouseLbtnUp();//UI안에서 땠을 때
    virtual void MouseLbtnClicked();//UI안에서 누르고 떘을 떄

public:
    void SetItemName(const wstring& _strName) { m_tItemInfo.m_strName = _strName; }
    const wstring& GetItemName() { return m_tItemInfo.m_strName; }

private:
    tItemInfo& GetItemInfo() { return m_tItemInfo; }
    const UINT& GetItemqQantity() { return m_iItemCount; }


    friend class CInventory;
};

