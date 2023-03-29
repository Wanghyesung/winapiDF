#pragma once
#include "CObject.h"
class CWallPixle :
    public CObject
{
public:
    CWallPixle();
    virtual ~CWallPixle();

private:
    CTexture* m_pPixleTex;


public:
    virtual void update();//»ó¼Ó
    virtual void render(HDC _dc);
    virtual void finalupdate();

public:
    virtual void OnColliderEnter(CCollider* _pOther);
    virtual void OnColliderExit(CCollider* _pOther);
    virtual void OnCollision(CCollider* _pOther);




};

