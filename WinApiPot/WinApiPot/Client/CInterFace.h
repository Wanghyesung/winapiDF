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

    vector<CTexture*> m_vecSKillTex;
    vector<CTexture*> m_vecCoolDownTex;
    vector<CTexture*> m_vecKeyTex;
    //�� �������̽� �����۵�
    vector<CItem*> m_vecItem;
    //������ 1��~5��° ĭ ��ġ ������ 1ĭ�� ����
    Vec2 m_vItemStartPos;
    Vec2 m_vItemEndPos;
    Vec2 m_vItemStep;
   
    //���� �̹��� ����
    vector<CTexture*> m_vecNumber;

public:
    virtual void MouseOn();//UI���� ���콺 �ö���� �� 
    virtual void MouseLbtnDown();//UI�ȿ��� ������ ��
    virtual void MouseLbtnUp();//UI�ȿ��� ���� ��
    virtual void MouseLbtnClicked();//UI�ȿ��� ������ ���� ��

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

    //������ ã��
    CItem* getItemThisIndex(int _iIndex);
    void changeItemIndex(CItem* _pItem, CItem* _pOtehr);

    //������
    void keyRender(HDC _dc);
    void skillRender(HDC _dc);

private:
    friend class CInterfaceMgr;
};

