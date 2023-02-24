#pragma once
#include "CObject.h"

class CTexture;

class CFireBall :
    public CObject
{
private:
    int m_iDir;
    Vec2 m_vPos;
    float m_fDamge;

    float m_fSpeed;

    float m_fDelTime;
    float m_fCurTime;

    tAttackInfo m_tAtt;

private:
    CTexture* m_pFireballRight;
    CTexture* m_pFireballLeft;

public:
    CFireBall(int iDir, Vec2 _vPos);
    virtual ~CFireBall();

    virtual void update();
    virtual void render(HDC _dc);


public:
    const tAttackInfo& GetAttInfo() { return m_tAtt; }

public:
    virtual void OnColliderEnter(CCollider* _pOther);
    virtual void OnColliderExit(CCollider* _pOther);
    virtual void OnCollision(CCollider* _pOther);
};

