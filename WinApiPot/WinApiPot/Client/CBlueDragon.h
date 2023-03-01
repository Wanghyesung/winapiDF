#pragma once
#include "CMonster.h"
class CBlueDragon :
    public CMonster
{
public:
    CBlueDragon();
    virtual ~CBlueDragon();


public:
    virtual void OnColliderEnter(CCollider* _pOther);
    virtual void OnColliderExit(CCollider* _pOther);
    virtual void OnCollision(CCollider* _pOther);

};

