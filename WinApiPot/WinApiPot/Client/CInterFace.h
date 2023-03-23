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

    //포션
    virtual void update();
    virtual void render(HDC _dc);

private:
    CTexture* m_pInterFaceTex;

    //내 인터페이스 아이템들
    vector<CItem*> m_vecItem;
    //아이템 1번~5번째 칸 위치 아이템 1칸씩 범위
    Vec2 m_vItemStartPos;
    Vec2 m_vItemEndPos;
    Vec2 m_vItemStep;
   

public:
    virtual void MouseOn();//UI위에 마우스 올라왔을 떄 
    virtual void MouseLbtnDown();//UI안에서 눌렸을 떄
    virtual void MouseLbtnUp();//UI안에서 땠을 때
    virtual void MouseLbtnClicked();//UI안에서 누르고 떘을 떄

public:
    void MoveIoInterface(CItem* _pItem);

    Vec2 GetItemStartPos() { return m_vItemStartPos; }
    Vec2 GetItemEndPos() { return m_vItemEndPos; }

    void DeleteItem(CItem* _pItem);
    void AddVecItem(CItem* _pItem, int _iIndx) {m_vecItem[_iIndx] = _pItem;}
    int GetItemIndex(CItem* _pItem);

private:
    void ChangeValue(float _HPfValue, float _MPfValue);

    void changeInvenotry(CItem* _pItem, Vec2 _vOtherDragePrePos);

    //아이템 찾기
    CItem* getItemThisIndex(int _iIndex);
    void changeItemIndex(CItem* _pItem, CItem* _pOtehr);

private:
    friend class CInterfaceMgr;
};

