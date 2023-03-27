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

    //활성화
    bool m_bActive;
    bool m_bTargetOn;
    
    //현재 나를 보관하고있는 공간 
    //인터페이스면 크기 변경

    //숫자 이미지 벡터
    vector<CTexture*> m_vecNumber;

protected:
    ITEM_TYPE m_eItemType;

    UINT m_iItemCount;

    bool m_bIsInterfacePos;

    //인터페이스로 가면 커지게
    int m_iWidth;//내 이미지 가로
    int m_iHeight;//내 이미지 세로

    int m_iNumberWidth; 
    int m_iNumberHeight;

private:
    Vec2 m_vDragStartPos;
    Vec2 m_vDragePrePos;

    CInventory* m_pInven;

    //이미지 상대적으로 크게
    Vec2 m_vOffsetScale;

protected:
    CInventory* GetInventory() { return m_pInven; }
    Vec2 GetOffsetScale() { return m_vOffsetScale; }

    void deleteItem();

public:
    virtual void render(HDC _dc);
    virtual void update();//상속
    virtual void finalupdate();

    virtual void UseItem() = 0;

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

    void SetItemScale(Vec2 _vScale);


    friend class CItemMgr;
    friend class CInventory;
    friend class CInterFace;
};

