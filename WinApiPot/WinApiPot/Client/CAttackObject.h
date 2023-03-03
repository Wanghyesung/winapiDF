#pragma once
#include "CObject.h"

class CMonster;

class CAttackObject :
    public CObject
{
    //�浹ü�� �������ִ� ������Ʈ
public:
    CAttackObject();
    CAttackObject(Vec2 _vScale);
    virtual ~CAttackObject();

private:
    CMonster* m_pOwner;
    float  m_fAttackRange;

public:
    virtual void update();
    virtual void render(HDC _dc);

public:
    void SetColActive(bool _b);

public:
    virtual void OnColliderEnter(CCollider* _pOther);
    virtual void OnColliderExit(CCollider* _pOther);
    virtual void OnCollision(CCollider* _pOther);

    friend class CMonster;
};

