#pragma once
#include "CSkillState.h"

class CKick :
    public CSkillState
{
public:
    CKick();
    virtual ~CKick();

private:
    float m_fOffSet;
    Vec2 m_vCollSize;
    Vec2 m_vCollOffSet;

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

