#pragma once
#include "CObject.h"
class CPillar :
    public CObject
{
public:
    CPillar();
    virtual ~CPillar();

private:
    CTexture* CTex;

public:
    virtual void render(HDC _dc);
    virtual void update();
    virtual void finalupdate();

public:
    virtual void OnColliderEnter(CCollider* _pOther);
    virtual void OnColliderExit(CCollider* _pOther);
    virtual void OnCollision(CCollider* _pOther);

};

