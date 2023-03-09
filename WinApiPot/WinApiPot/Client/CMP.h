#pragma once
#include "CUI.h"
class CMP :
    public CUI
{
public:
    CMP();
    virtual ~CMP();

private:
    CTexture* m_pMPTex;

    static int m_iMinusMp;

public:
    virtual void render(HDC _dc);
    virtual void update();//상속

public:
    virtual void MouseOn();//UI위에 마우스 올라왔을 떄 
    virtual void MouseLbtnDown();//UI안에서 눌렸을 떄
    virtual void MouseLbtnUp();//UI안에서 땠을 때
    virtual void MouseLbtnClicked();//UI안에서 누르고 떘을 떄

private:
    void SetMinusMp(float _fMp) { m_iMinusMp = _fMp; }


    friend class CInterFace;
};

