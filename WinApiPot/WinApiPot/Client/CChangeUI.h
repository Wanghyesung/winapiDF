#pragma once
#include "CUI.h"
class CChangeUI :
    public CUI
{
public:
    CChangeUI();
    virtual ~CChangeUI();

private:
    CTexture* pMouseNoneTex;
    CTexture* pMouseOnTex;
    CTexture* pMousePushTex;

    bool m_bMouseOn;
    bool m_bMousePush;

public:
    virtual void MouseOn();//UI위에 마우스 올라왔을 떄 
    virtual void MouseLbtnDown();//UI안에서 눌렸을 떄
    virtual void MouseLbtnUp();//UI안에서 땠을 때
    virtual void MouseLbtnClicked();//UI안에서 누르고 떘을 떄

public:
    virtual void render(HDC _dc);
    virtual void update();//상속
    virtual void finalupdate();


};

