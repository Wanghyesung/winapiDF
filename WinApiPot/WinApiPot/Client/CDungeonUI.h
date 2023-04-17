#pragma once
#include "CUI.h"
class CDungeonUI :
    public CUI
{

public:
    CDungeonUI();
    virtual ~CDungeonUI();

private:
    SCENE_TYPE m_eNextScene;

public:
    virtual void MouseOn();//UI위에 마우스 올라왔을 떄 
    virtual void MouseLbtnDown();//UI안에서 눌렸을 떄
    virtual void MouseLbtnUp();//UI안에서 땠을 때
    virtual void MouseLbtnClicked();//UI안에서 누르고 떘을 떄

    virtual void render(HDC _dc);

public:
    void SetNextScene(SCENE_TYPE _eNextScene) { m_eNextScene = _eNextScene; }

};

