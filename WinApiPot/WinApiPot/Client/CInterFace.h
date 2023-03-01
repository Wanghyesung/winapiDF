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
    virtual void MouseOn();//UI���� ���콺 �ö���� �� 
    virtual void MouseLbtnDown();//UI�ȿ��� ������ ��
    virtual void MouseLbtnUp();//UI�ȿ��� ���� ��
    virtual void MouseLbtnClicked();//UI�ȿ��� ������ ���� ��

private:
    void ChangeValue(float _HPfValue, float _MPfValue);

    //void CHANGE

public:
    virtual void render(HDC _dc);
private:
    

    friend class CInterfaceMgr;
};

