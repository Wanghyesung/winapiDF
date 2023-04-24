#pragma once
#include "CObject.h"

class CExsFire;

class CRobotExs :
    public CObject
{
public:
    CRobotExs();
    virtual ~CRobotExs();

private:
    tMonInfo m_tInfo;

    float m_fDeleteCurTime;
    float m_fDeleteTime;

    int m_iDirX;

    UINT m_iCreateCount;
public:
    virtual void render(HDC _dc);
    virtual void update();//»ó¼Ó
    virtual void finalupdate();

public:
    virtual void OnColliderEnter(CCollider* _pOther);
    virtual void OnColliderExit(CCollider* _pOther);
    virtual void OnCollision(CCollider* _pOther);

private:
    void init_dir(int _iDir);

    void create_fire();

    friend class CExs;
};

