#pragma once
#include "CMonster.h"
class CKnight :
    public CMonster
{

struct tKnight_Attack
{
    //공격 오브젝트 크기, 생성될 위치, 공격시잘될 프레임 ,
    Vec2 m_vAttackSacle;
    Vec2 m_vOffset;
    UINT m_iStartAttackFrame;
    UINT m_iEndAttackFrame;
    float m_fSkillTime;
    tAttackInfo m_tAttackInfo;
};

public:
    CKnight();
    virtual ~CKnight();

private:
    MONSTER_STATE m_eMonState;

    unordered_map<wstring, tKnight_Attack> m_hashMonSkill;

public:
    virtual void update();
    virtual void render(HDC _dc);
   
protected:
    void hit(CCollider* _pOther, const tAttackInfo& _tAtt);


private:
    void update_state();

    void init_skill();

public:
    virtual void OnColliderEnter(CCollider* _pOther);
    virtual void OnColliderExit(CCollider* _pOther);
    virtual void OnCollision(CCollider* _pOther);



};

