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
    //활성화
    CTexture* m_pInvenTex;
    bool m_bActive;

    //내 인벤토리의 아이템들
    map<wstring, CItem*> m_mapInventory;

public:
    virtual void render(HDC _dc);
    virtual void update();//상속
    virtual void finalupdate();

public:
    virtual void MouseOn();//UI위에 마우스 올라왔을 떄 
    virtual void MouseLbtnDown();//UI안에서 눌렸을 떄
    virtual void MouseLbtnUp();//UI안에서 땠을 때
    virtual void MouseLbtnClicked();//UI안에서 누르고 떘을 떄

    friend class CInventoryMgr;
};

