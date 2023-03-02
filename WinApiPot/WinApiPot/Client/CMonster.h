#pragma once
#include "CObject.h"

struct tMonInfo
{
    int m_iHp;
    float m_fspeed;
    float m_fnavigationScope;
};




class AI;

class CMonster :
    public CObject
{
public:
    CMonster();
    virtual ~CMonster();

private:
    AI* m_AI;
    bool m_bHit;

    bool m_bDead;
    bool m_bActiv;//È°¼ºÈ­

    tMonInfo m_tMonInfo;
    tHitInfo m_tHitInfo;
    tAttackInfo m_tAttackInfo;

    float m_fAttTime;   
    float m_fCurAttTime;

protected:
    void SetDead() { m_bDead = true; }
    void SetActiv(bool _b) { m_bActiv = _b; }

public:
    bool IsDead() { return m_bDead; }
    bool IsActiv() { return m_bActiv; }

public:
    virtual void update();
    virtual void render(HDC _dc);
   

    AI* GetAI() { return m_AI; }
    void SetAI(AI* _AI);

    void SetHitInfo(const tHitInfo& _tInfo) { m_tHitInfo = _tInfo; }
    tHitInfo& GetHitInfo() { return m_tHitInfo; }

protected:
    float& GetAttCurTime() { return m_fCurAttTime;}
    float GetAttTime() { return m_fAttTime; }

    virtual void hit(CCollider* _pOther, const tAttackInfo& _tAtt);



public:
    void SettMonInfo(const tMonInfo& _tMonInfo) { m_tMonInfo = _tMonInfo; }
    tMonInfo& GetMonInfo() { return m_tMonInfo; }

public:
    void SetAttackInfo(const tAttackInfo& _tAttackInfo) { m_tAttackInfo = _tAttackInfo; }
    const tAttackInfo& GetAttackInfo() { return m_tAttackInfo; }

    void InitAttackInfo(const tAttackInfo& _tAttackInfo) { m_tAttackInfo = _tAttackInfo; }

public:
    virtual void OnColliderEnter(CCollider* _pOther);
    virtual void OnColliderExit(CCollider* _pOther);   
    virtual void OnCollision(CCollider* _pOther);
    
    friend class CMonFactory;
    friend class CDeadState;
};

