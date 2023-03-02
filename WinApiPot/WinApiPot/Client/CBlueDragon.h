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

public:
    virtual void update();
    virtual void render(HDC _dc);

protected:
    void hit(CCollider* _pOther, const tAttackInfo& _tAtt);

private:
    void update_state();


public:
    virtual void OnColliderEnter(CCollider* _pOther);
    virtual void OnColliderExit(CCollider* _pOther);
    virtual void OnCollision(CCollider* _pOther);

};

