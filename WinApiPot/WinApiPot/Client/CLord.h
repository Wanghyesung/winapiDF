#pragma once
#include "CMonster.h"
class CThunder;

class CLord :
    public CMonster
{
public:
    CLord();
    virtual ~CLord();

private:
    MONSTER_STATE m_eMonState;

    //일정시간 번개
    float m_fThunderCurTime;
    float m_fThunderMaxTime;

public:
    virtual void update();
    virtual void render(HDC _dc);

public:
    CThunder* CreateThunder();

public:
    virtual void OnColliderEnter(CCollider* _pOther);
    virtual void OnColliderExit(CCollider* _pOther);
    virtual void OnCollision(CCollider* _pOther);

private:
    void hit(CCollider* _pOther, const tAttackInfo& _tAtt);
    void update_state();
};

