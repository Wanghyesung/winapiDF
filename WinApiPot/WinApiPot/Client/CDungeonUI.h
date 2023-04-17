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
    virtual void MouseOn();//UI���� ���콺 �ö���� �� 
    virtual void MouseLbtnDown();//UI�ȿ��� ������ ��
    virtual void MouseLbtnUp();//UI�ȿ��� ���� ��
    virtual void MouseLbtnClicked();//UI�ȿ��� ������ ���� ��

    virtual void render(HDC _dc);

public:
    void SetNextScene(SCENE_TYPE _eNextScene) { m_eNextScene = _eNextScene; }

};

