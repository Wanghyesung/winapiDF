#pragma once
#include "CMonster.h"
class CBlueDragon :
    public CMonster
{
public:
    CBlueDragon();
    virtual ~CBlueDragon();

private:
    MONSTER_STATE m_eMonState;
    float         m_fDefensTime;
    float         m_fCurTime;

    bool          m_bDefenseOn;

public:
    virtual void update();
    virtual void render(HDC _dc);


protected:
    void hit(CCollider* _pOther, const tAttackInfo& _tAtt);
    void SetDefense(bool _b) { m_bDefenseOn = _b; }

private:
    void update_state();

public:
    virtual void OnColliderEnter(CCollider* _pOther);
    virtual void OnColliderExit(CCollider* _pOther);
    virtual void OnCollision(CCollider* _pOther);


    friend class CDefenseState;
};

