#pragma once
#include "CObject.h"

class CEvileye;

class CEvilLaser :
    public CObject
{
public:
    CEvilLaser();
    virtual ~CEvilLaser();

private:
    CEvileye* m_pOwner;
    wstring m_strLaserDir;

    tAttackInfo m_tAtt;
    bool m_bAttackOn;
    UINT m_iFrame;
public:
    virtual void render(HDC _dc);
    virtual void update();//»ó¼Ó

public:
    const tAttackInfo& GetAttackInfo() { return m_tAtt; }
    bool IsAttackOn() { return m_bAttackOn; }
public:
    virtual void OnColliderEnter(CCollider* _pOther);
    virtual void OnColliderExit(CCollider* _pOther);
    virtual void OnCollision(CCollider* _pOther);

private:
    bool IsSameJumLoc(CCollider* _pOther, CCollider* _pThis);

    friend class CEvileye;
};

