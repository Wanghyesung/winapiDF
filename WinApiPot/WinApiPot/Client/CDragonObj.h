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

    //내 hp가 다 달면 비활성화
    float m_fHp;

    //공겨 시작
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

