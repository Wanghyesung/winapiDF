#pragma once
#include "CObject.h"
class CSpinner :
    public CObject
{
public:
    CSpinner();
    virtual ~CSpinner();

private:
    tAttackInfo m_tAttackInfo;
    float m_fDegree;

    float m_fCurTime;
    float m_fMaxTime;

public:
    virtual void render(HDC _dc);
    virtual void update();
    virtual void finalupdate();

public:
    const tAttackInfo& GetAttInfo() { return m_tAttackInfo; }

public:
    virtual void OnColliderEnter(CCollider* _pOther);
    virtual void OnColliderExit(CCollider* _pOther);
    virtual void OnCollision(CCollider* _pOther);

};

