#pragma once
#include "CUI.h"

class CTexture;
class CInterfaceMgr;

class CInterFace :
    public CUI
{

public:
    CInterFace();
    virtual ~CInterFace();

private:
    CTexture* m_pInterFaceTex;
    CTexture* m_pMPTex;

    
public:
    virtual void MouseOn();//UI위에 마우스 올라왔을 떄 
    virtual void MouseLbtnDown();//UI안에서 눌렸을 떄
    virtual void MouseLbtnUp();//UI안에서 땠을 때
    virtual void MouseLbtnClicked();//UI안에서 누르고 떘을 떄

private:
    void ChangeValue(float _HPfValue, float _MPfValue);

    //void CHANGE

public:
    virtual void render(HDC _dc);
private:
    

    friend class CInterfaceMgr;
};

