#pragma once
#include "CMonster.h"

class CNaiasAttack;
class CNaiasTrace;


class CNaias :
    public CMonster
{
public:
    CNaias();
    virtual ~CNaias();

    virtual void update();
    virtual void render(HDC _dc);

private:
    MONSTER_STATE m_eMonState;

    unordered_map<wstring, tNew_Attack> m_hashMonSkill;


private:
    void update_state();

    void init_skill();

    void hit(CCollider* _pOther, const tAttackInfo& _tAtt);
public:
    virtual void OnColliderEnter(CCollider* _pOther);
    virtual void OnColliderExit(CCollider* _pOther);
    virtual void OnCollision(CCollider* _pOther);

    friend class CNaiasTrace;
    friend class CNaiasAttack;
};

