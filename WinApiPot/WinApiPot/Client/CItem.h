#pragma once
#include "CUI.h"
class CItem :
    public CUI
{
public:
    CItem();
    virtual ~CItem();

private:
    wstring m_strItemName;
    UINT m_iItemCount;

    //활성화
    bool m_bActive;

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
    void SetItemName(const wstring& _strName) { m_strItemName = _strName; }
    const UINT& GetItemqQantity() { return m_iItemCount; }

};

