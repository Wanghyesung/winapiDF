#pragma once
#include "CObject.h"
class CRobotExs;

class CExsFire :
    public CObject
{
public:
    CExsFire();
    virtual ~CExsFire();

private:
    int m_iDir;

    float m_fSpeed;

    float m_fDelTime;
    float m_fCurTime;

    tAttackInfo m_tAtt;

    CTexture* m_pFireballRight;
    CTexture* m_pFireballLeft;

public:
    virtual void update();
    virtual void render(HDC _dc);

public:
    const tAttackInfo& GetAttInfo() { return m_tAtt; }
    void SetAttackInfo(const tAttackInfo& _tAtt) { m_tAtt = _tAtt; }

public:
    bool IsSameJumLoc(CCollider* _pOther);

private:
    void init_dir(int _iDir);
public:
    virtual void OnColliderEnter(CCollider* _pOther);
    virtual void OnColliderExit(CCollider* _pOther);
    virtual void OnCollision(CCollider* _pOther);

    friend class CRobotExs;
};

