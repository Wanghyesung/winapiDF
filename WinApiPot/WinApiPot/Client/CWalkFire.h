#pragma once
#include "CSkillState.h"
class CWalkFire :
    public CSkillState
{
public:
    CWalkFire();
    virtual ~CWalkFire();

private:
    Vec2 m_vCollSize;
    Vec2 m_vCollOffSet;

    int m_iFireCount;

    int m_iDir;

    float m_iCurTime;
    float m_iMaxTime;
public:
    virtual void Skillupdate();
    virtual void init();
    virtual void enter();

public:
    void SetDir(int _i) { m_iDir = _i; }

    friend class CBullet;
};

