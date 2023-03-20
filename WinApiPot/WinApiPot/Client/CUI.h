#pragma once
#include "CObject.h"

struct tItemInfo
{
    wstring m_strName;//아이템 이름 
    Vec2 m_vPos;//인벤토리 보관 위치
};

class CUI :
    public CObject
{
public:
    CUI();
    CUI(const CUI& _pUI);
    virtual ~CUI();


private:
    Vec2 m_vFinalPos;
    CUI* m_pParentUI;//내 부모 UI
    vector<CUI*> m_vecChildUI;//자식 UI

    bool m_bCamAfeccted;//카메라 
    bool m_bMouseOn;
    bool m_bLbntDown;

public:
    virtual void render(HDC _dc);
    virtual void update();//상속
    virtual void finalupdate();


private:
    void ChildUpdate();
    void ChildRender(HDC _dc);
    void ChildFinalupdate();
   
    void MouseOnCheck();

public:
    Vec2 GetFinalPos() { return m_vFinalPos; }
    void SetFinalPos(Vec2 _vPos) { m_vFinalPos = _vPos; }

    CUI* GetParentUI() { return m_pParentUI; }
    const vector<CUI*>& GetChildVecUI() { return m_vecChildUI; }

    bool IsLBntDown() { return m_bLbntDown; }
    bool IsMosueOn() { return m_bMouseOn; }

    void AddChildUI(CUI* _pUI) { m_vecChildUI.push_back(_pUI); _pUI->m_pParentUI = this; }
    CUI* GetChildUI(const wstring& _strName);

public:
    virtual void MouseOn();//UI위에 마우스 올라왔을 떄 
    virtual void MouseLbtnDown();//UI안에서 눌렸을 떄
    virtual void MouseLbtnUp();//UI안에서 땠을 때
    virtual void MouseLbtnClicked();//UI안에서 누르고 떘을 떄


    friend class CUIMgr;
};

