#pragma once
#include "CObject.h"
class CTemWall :
    public CObject
{
public:
    CTemWall();
    virtual ~CTemWall();

public:
    virtual void update();
    virtual void render(HDC _dc);
    virtual void finalupdate();

public:
    virtual void OnColliderEnter(CCollider* _pOther);
    virtual void OnColliderExit(CCollider* _pOther);
    virtual void OnCollision(CCollider* _pOther);
private:


};

