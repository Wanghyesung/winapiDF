#pragma once
#include "CUI.h"
class CMonHP :
    public CUI
{
public:
    CMonHP();
    virtual ~CMonHP();

private:
    CTexture* m_pHPTex;

    float   m_fHp;
    Vec2    m_vUIOffset;

public:
    virtual void render(HDC _dc);
    virtual void update();//상속
    virtual void finalupdate();

    void render_hp(HDC _dc);


public:
    virtual void MouseOn();//UI위에 마우스 올라왔을 떄 
    virtual void MouseLbtnDown();//UI안에서 눌렸을 떄
    virtual void MouseLbtnUp();//UI안에서 땠을 때
    virtual void MouseLbtnClicked();//UI안에서 누르고 떘을 떄

private:
    void SetMinusHp(float _fValue) { m_fHp = _fValue; }
    void SetUIOffset(Vec2 _vOffset) { m_vUIOffset = _vOffset; }

    friend class CMonInterface;
};

