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

    //이름에 따라 몬스터 색 변경
    wstring m_strTexName;
public:
    virtual void update();
    virtual void render(HDC _dc);
   
protected:
    void hit(CCollider* _pOther, const tAttackInfo& _tAtt);


private:
    void update_state();

    void init_skill();
    //텍스쳐, 애니메이션 초기화
    void init(const wstring& _strName);
    
    //기사 몬스터마다 이미지 크기 설정
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

