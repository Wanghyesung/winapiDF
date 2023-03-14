#pragma once
#include "CObject.h"

class CMonster;

class CAttackObject :
    public CObject
{
    //충돌체만 가지고있는 오브젝트
public:
    CAttackObject();
    CAttackObject(Vec2 _vScale);
    virtual ~CAttackObject();

private:
    CMonster* m_pOwner;
    float  m_fAttackRange;
    UINT    m_iCurAttackIndex;
    //내 크기
    //공격 범위 

public:
    void Skill_update();
    virtual void render(HDC _dc);
    virtual void update(){};
public:
    void SetColActive(bool _b);
    void SetCurAttackIndex(UINT _i) { m_iCurAttackIndex = _i; }    

public:
    const tAttackInfo& GetAttInfo();

private:
    void SetAttackRange(float _fXRange, Vec2 _vCollScale);

public:
    virtual void OnColliderEnter(CCollider* _pOther);
    virtual void OnColliderExit(CCollider* _pOther);
    virtual void OnCollision(CCollider* _pOther);

    friend class CMonster;
    friend class CNearAttack;
};

