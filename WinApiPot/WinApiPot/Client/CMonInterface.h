#pragma once
#include "CUI.h"

class CTexture;

class CMonInterface :
    public CUI
{
public:
    CMonInterface(const wstring& _strMonName, bool _bIsBoss = false);
    virtual ~CMonInterface();

private:
    CTexture* m_pInterfaceTex;
    CTexture* m_pDleTex;

    wstring m_strMonName;//내 몬스터 이름
    bool    m_bActiv;

public:
    virtual void render(HDC _dc) {};
    virtual void update();//상속
    virtual void finalupdate();

    const wstring& GetMonName() { return m_strMonName; }

public:
    virtual void MouseOn();//UI위에 마우스 올라왔을 떄 
    virtual void MouseLbtnDown();//UI안에서 눌렸을 떄
    virtual void MouseLbtnUp();//UI안에서 땠을 때
    virtual void MouseLbtnClicked();//UI안에서 누르고 떘을 떄


private:
    void changeValue(float _fHpValue);
    void renderHp(HDC _dc);

    friend class CInterfaceMgr;


};

