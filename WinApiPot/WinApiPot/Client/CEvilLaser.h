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
    CObject* m_pOwner;
    wstring m_strLaserDir;

    tAttackInfo m_tAtt;
    bool m_bAttackOn;
    UINT m_iFrame;

    int m_iDir;
public:
    virtual void render(HDC _dc);
    virtual void update();//���

public:
    const tAttackInfo& GetAttackInfo() { return m_tAtt; }
    bool IsAttackOn() { return m_bAttackOn; }
public:
    virtual void OnColliderEnter(CCollider* _pOther);
    virtual void OnColliderExit(CCollider* _pOther);
    virtual void OnCollision(CCollider* _pOther);

private:
    bool IsSameJumLoc(CCollider* _pOther, CCollider* _pThis);
    void setDir(int _iDir);

    void set_DirUp();

    friend class CEvileye;
    friend class CCreateEye;
};
