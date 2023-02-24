#pragma once
#include "CSkillState.h"
class CRandomFire :
    public CSkillState
{
public:
    CRandomFire();
    virtual ~CRandomFire();

private:
    float m_fOffSet;
    Vec2 m_vCollSize;
    Vec2 m_vCollOffSet;

    float m_fAccTime;
    float m_fCurTime;

    int m_iAttackFrame;

public:
    virtual void Skillupdate();
    virtual void init();
    virtual void exit();

public:
    virtual void OnColliderEnter(CCollider* _pOther);
    virtual void OnColliderExit(CCollider* _pOther);
    virtual void OnCollision(CCollider* _pOther);

};

