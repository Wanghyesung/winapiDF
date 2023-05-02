#pragma once
#include "CUI.h"

class CDungeonMgr;

class CClearUI :
    public CUI
{
public:
    CClearUI();
    virtual ~CClearUI();

private:
    bool m_bActive;
    CTexture* m_pUITex;

public:
    virtual void MouseOn();//UI위에 마우스 올라왔을 떄 
    virtual void MouseLbtnDown();//UI안에서 눌렸을 떄
    virtual void MouseLbtnUp();//UI안에서 땠을 때
    virtual void MouseLbtnClicked();//UI안에서 누르고 떘을 떄

public:
    virtual void render(HDC _dc);
    virtual void update();//상속
    virtual void finalupdate();

    void Create();//자식UI들 미리 설정

    friend class CDungeonMgr;
};

