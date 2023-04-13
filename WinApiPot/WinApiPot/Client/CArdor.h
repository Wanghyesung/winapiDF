#pragma once
#include "CMonster.h"

class CArdorTrace;
class CArdorAttack;

class CArdor :
    public CMonster
{
public:
    CArdor();
    virtual ~CArdor();

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

    friend class CArdorTrace;
    friend class CArdorAttack;


};

