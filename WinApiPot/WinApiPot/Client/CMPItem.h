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

public:
    virtual void render(HDC _dc);
    virtual void update();//상속
    virtual void finalupdate();

    virtual void UseItem();

public:
    virtual void MouseOn();//UI위에 마우스 올라왔을 떄 
    virtual void MouseLbtnDown();//UI안에서 눌렸을 떄
    virtual void MouseLbtnUp();//UI안에서 땠을 때
    virtual void MouseLbtnClicked();//UI안에서 누르고 떘을 떄
};

