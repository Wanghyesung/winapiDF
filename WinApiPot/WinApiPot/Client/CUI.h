#pragma once
#include "CObject.h"

struct tItemInfo
{
    wstring m_strName;//������ �̸� 
    Vec2 m_vPos;//�κ��丮 ���� ��ġ
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
    CUI* m_pParentUI;//�� �θ� UI
    vector<CUI*> m_vecChildUI;//�ڽ� UI

    bool m_bCamAfeccted;//ī�޶� 
    bool m_bMouseOn;
    bool m_bLbntDown;

public:
    virtual void render(HDC _dc);
    virtual void update();//���
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
    virtual void MouseOn();//UI���� ���콺 �ö���� �� 
    virtual void MouseLbtnDown();//UI�ȿ��� ������ ��
    virtual void MouseLbtnUp();//UI�ȿ��� ���� ��
    virtual void MouseLbtnClicked();//UI�ȿ��� ������ ���� ��


    friend class CUIMgr;
};

