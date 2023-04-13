#pragma once
#include "CMonster.h"

class CEvileyeIdel;
class CEvileyeAttack;

enum class EVILSKILL
{
    LASER,
    SHOT,
    CREATE
};

struct tEvileyeSkill
{
    float m_fCurTime;
    float m_fMaxTime;
    UINT m_iStartFrame;
};

class CEvileye :
    public CMonster
{
public:
    CEvileye();
    virtual ~CEvileye();

private:
    unordered_map<UINT, tEvileyeSkill> m_hashSkillTime;

    MONSTER_STATE m_eMonState;

    //이블아이 왼쪽 오른쪽 고정으로
    wstring m_strMonDir;
    
public:
    virtual void update();
    virtual void render(HDC _dc);

public:
    virtual void OnColliderEnter(CCollider* _pOther);
    virtual void OnColliderExit(CCollider* _pOther);
    virtual void OnCollision(CCollider* _pOther);
    
public:
    void SetDir(int _iDir);

protected:
    void hit(CCollider* _pOther, const tAttackInfo& _tAtt);

private:
    void init_skill();
    void update_skilltime();
    void update_state();

    //눈 발사 
    void shotEye();
    //땅에 눈 소환
    void createEye();
    //레이저
    void createLaser();

    friend class CEvileyeIdel;
    friend class CEvileyeAttack;
};

