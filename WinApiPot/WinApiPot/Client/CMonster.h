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

    Vec2 m_vHitMove;

    float m_fAttTime;   
    float m_fCurAttTime;

public:
    void SetDead() { m_bDead = true; }
    bool IsDead() { return m_bDead; }

    void SetActiv(bool _b) { m_bActiv = _b; }
    bool IsActiv() { return m_bActiv; }

public:
    virtual void update();
    virtual void render(HDC _dc);
    virtual void Hit(CCollider* _pOther, const tAttackInfo& _tAtt) {};

    AI* GetAI() { return m_AI; }
    void SetAI(AI* _AI);

    void SetHitInfo(const tHitInfo& _tInfo) { m_tHitInfo = _tInfo; }
    tHitInfo& GetHitInfo() { return m_tHitInfo; }

protected:
    float& GetAttCurTime() { return m_fCurAttTime;}
    float GetAttTime() { return m_fAttTime; }

public:
    void SetHitMove(Vec2 _vAmountMove) { m_vHitMove = _vAmountMove; }
    Vec2 GetHitMove() { return m_vHitMove; }

public:
    void SettMonInfo(const tMonInfo& _tMonInfo) { m_tMonInfo = _tMonInfo; }
    tMonInfo& GetMonInfo() { return m_tMonInfo; }

public:
    void SetAttackInfo(const tAttackInfo& _tAttackInfo) { m_tAttackInfo = _tAttackInfo; }
    tAttackInfo GetAttackInfo() { return m_tAttackInfo; }

    void InitAttackInfo(const tAttackInfo& _tAttackInfo) { m_tAttackInfo = _tAttackInfo; }

public:
    virtual void OnColliderEnter(CCollider* _pOther);
    virtual void OnColliderExit(CCollider* _pOther);   
    virtual void OnCollision(CCollider* _pOther);

    friend class CMonFactory;
};

