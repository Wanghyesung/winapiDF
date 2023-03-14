#pragma once
#include "CObject.h"
class CDragonObj :
    public CObject
{
public:
    CDragonObj();
    virtual ~CDragonObj();

private:
    bool m_bActive;

    //�� hp�� �� �޸� ��Ȱ��ȭ
    float m_fHp;

    //���� ����
    float m_fCurTime;
    float m_fTime;

    CTexture* CTex;
    CTexture* CTex1;

    tAttackInfo m_tAttackInfo;

public:
    virtual void render(HDC _dc);
    virtual void update();
    virtual void finalupdate();

public:
    virtual void OnColliderEnter(CCollider* _pOther);
    virtual void OnColliderExit(CCollider* _pOther);
    virtual void OnCollision(CCollider* _pOther);


};

