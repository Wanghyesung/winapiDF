#pragma once
#include "CObject.h"
class CCrystalPillar :
    public CObject
{
public:
    CCrystalPillar();
    virtual ~CCrystalPillar();


public:
    virtual void render(HDC _dc);
    virtual void update();
    virtual void finalupdate();


public:
    virtual void OnColliderEnter(CCollider* _pOther);
    virtual void OnColliderExit(CCollider* _pOther);
    virtual void OnCollision(CCollider* _pOther);



};

