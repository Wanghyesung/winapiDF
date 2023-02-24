#pragma once
#include "CObject.h"

class CCollider;

class CWall :
    public CObject
{
public:
    CWall();
    virtual ~CWall();

private:


public:
    virtual void render(HDC _dc);
    virtual void update();

public:
    virtual void OnColliderEnter(CCollider* _pOther);
    virtual void OnColliderExit(CCollider* _pOther);
    virtual void OnCollision(CCollider* _pOther);
};

