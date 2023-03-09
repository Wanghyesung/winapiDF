#pragma once
#include "CUI.h"
class CTexture;

class CHP :
    public CUI
{

public:
    CHP();
    virtual ~CHP();

private:
    CTexture* m_pHPTex;

    static int m_iMinusHp;

public:
    virtual void render(HDC _dc);
    virtual void update();//상속


public:
    virtual void MouseOn();//UI위에 마우스 올라왔을 떄 
    virtual void MouseLbtnDown();//UI안에서 눌렸을 떄
    virtual void MouseLbtnUp();//UI안에서 땠을 때
    virtual void MouseLbtnClicked();//UI안에서 누르고 떘을 떄

private:
    void SetMinusHp(float _fHp) { m_iMinusHp = _fHp; }

    friend class CInterFace;
};

