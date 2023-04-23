#pragma once
#include "CSkillState.h"

class CTarget;

class CFire :
    public CSkillState
{
public:
    CFire();
    virtual ~CFire();

private:
    wstring m_strSkillName;

    CTarget* m_pTarget;

    bool m_bFire;

    Vec2 m_vStartPos;
public:
    virtual void Skillupdate();
    virtual void init();
    virtual void exit();
    virtual void enter();

public:
    virtual void OnColliderEnter(CCollider* _pOther);
    virtual void OnColliderExit(CCollider* _pOther);
    virtual void OnCollision(CCollider* _pOther);

private:
    void jump_robot();
    void fire_robot();
    void create_target();
};

