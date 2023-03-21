#pragma once
#include "CUI.h"

class CTexture;
class CInterfaceMgr;
class CItem;

class CInterFace :
    public CUI
{

public:
    CInterFace();
    virtual ~CInterFace();

    //����
    virtual void update();

private:
    CTexture* m_pInterFaceTex;

    //���� ������ ����
    vector<CItem*> m_vecItem;

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

