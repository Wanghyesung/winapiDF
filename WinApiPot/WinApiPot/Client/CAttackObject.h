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
    UINT    m_iCurAttackIndex;
    //�� ũ��
    //���� ���� 
    tAttackInfo m_tAttackInfo;

public:
    void Skill_update();
    virtual void render(HDC _dc);
    virtual void update(){};
public:
    void SetColActive(bool _b);
    void SetCurAttackIndex(UINT _i) { m_iCurAttackIndex = _i; }    

public:
    const tAttackInfo& GetAttInfo();
    void SetAttInfo(const tAttackInfo& _tAtt) { m_tAttackInfo = _tAtt; }

public:
    void SetAttackRange(float _fXRange, Vec2 _vCollScale);

public:
    virtual void OnColliderEnter(CCollider* _pOther);
    virtual void OnColliderExit(CCollider* _pOther);
    virtual void OnCollision(CCollider* _pOther);

    friend class CMonster;
    friend class CNearAttack;
};

