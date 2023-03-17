#pragma once
#include "CObject.h"

class CLord;

class CThunder :
    public CObject
{
public:
    CThunder();
    virtual ~CThunder();

private:
    CLord* m_pOwner;
    tAttackInfo m_tAtt;

    int m_iFrame;
    int m_iDir;
    float m_fTime;
    float m_fMaxTime;

    bool m_bAttackOn;

    Vec2 vOffset;

public:
    virtual void render(HDC _dc);
    virtual void update();//»ó¼Ó

public:
    virtual void OnColliderEnter(CCollider* _pOther);
    virtual void OnColliderExit(CCollider* _pOther);
    virtual void OnCollision(CCollider* _pOther);

public:
    const tAttackInfo& GetAttackInfo() { return m_tAtt; }

    bool IsAttackOn() { return m_bAttackOn; }

private:
    void SetAttackInfo(const tAttackInfo& _tAtt) { m_tAtt = _tAtt; }
    bool IsSameJumLoc(CCollider* _pOther, CCollider* _pThis);

    friend class CLord;
};

