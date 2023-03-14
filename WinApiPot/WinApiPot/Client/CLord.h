#pragma once
#include "CMonster.h"
class CLord :
    public CMonster
{
public:
    CLord();
    virtual ~CLord();

private:
    MONSTER_STATE m_eMonState;

public:
    virtual void update();
    virtual void render(HDC _dc);

public:
    virtual void OnColliderEnter(CCollider* _pOther);
    virtual void OnColliderExit(CCollider* _pOther);
    virtual void OnCollision(CCollider* _pOther);

private:
    void hit(CCollider* _pOther, const tAttackInfo& _tAtt);
    void update_state();
};

