#pragma once
#include "CMonster.h"
class CKnightTrace;
class CKnightAttack;


class CKnight :
    public CMonster
{

public:
    CKnight();
    virtual ~CKnight();

private:
    MONSTER_STATE m_eMonState;

    unordered_map<wstring, tNew_Attack> m_hashMonSkill;

    //�̸��� ���� ���� �� ����
    wstring m_strTexName;
public:
    virtual void update();
    virtual void render(HDC _dc);
   
protected:
    void hit(CCollider* _pOther, const tAttackInfo& _tAtt);


private:
    void update_state();

    void init_skill();
    //�ؽ���, �ִϸ��̼� �ʱ�ȭ
    void init(const wstring& _strName);
    
    //��� ���͸��� �̹��� ũ�� ����
    Vec2 m_vTexScale;
    Vec2 m_vTexOffset;
private:
    void setTexScale(Vec2 _vScale) { m_vTexScale = _vScale; }
    void setTexOffset(Vec2 _vOffset) { m_vTexOffset = _vOffset; }

public:
    virtual void OnColliderEnter(CCollider* _pOther);
    virtual void OnColliderExit(CCollider* _pOther);
    virtual void OnCollision(CCollider* _pOther);


    friend class CKnightTrace;
    friend class CKnightAttack;
    friend class CMonFactory;
};

