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
    virtual void render(HDC _dc);

private:
    CTexture* m_pInterFaceTex;

    //�� �������̽� �����۵�
    vector<CItem*> m_vecItem;
    //������ 1��~5��° ĭ ��ġ ������ 1ĭ�� ����
    Vec2 m_vItemStartPos;
    Vec2 m_vItemEndPos;
    Vec2 m_vItemStep;
   

public:
    virtual void MouseOn();//UI���� ���콺 �ö���� �� 
    virtual void MouseLbtnDown();//UI�ȿ��� ������ ��
    virtual void MouseLbtnUp();//UI�ȿ��� ���� ��
    virtual void MouseLbtnClicked();//UI�ȿ��� ������ ���� ��

public:
    void MoveIoInterface(CItem* _pItem);

    Vec2 GetItemStartPos() { return m_vItemStartPos; }
    Vec2 GetItemEndPos() { return m_vItemEndPos; }

private:
    void ChangeValue(float _HPfValue, float _MPfValue);

    //void CHANGE

    //������ ã��
    CItem* getItemThisIndex(int _iIndex);
    int GetItemIndex(CItem* _pItem);
    void changeItemIndex(CItem* _pItem, CItem* _pOtehr);

private:
    

    friend class CInterfaceMgr;
};

