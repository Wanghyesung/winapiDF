#pragma once
#include "CObject.h"

struct tMonInfo
{
    float m_iHp;
    float m_AccHP;
    float m_fspeed;
    float m_fnavigationScope;
};


enum class eMonsterAttackType
{
    NORMAL,
    SKILL
};

struct tMonSkill
{
    eMonsterAttackType m_eSkillType;
    tAttackInfo m_MonAttackInfo; //기본 스킬 정보
    wstring m_strAttackName; //스킬 이름
    UINT m_iStartFrame; //스킬 시작 프레임
    UINT m_iEndFrame = 10;//스킬 마지막 프레임
    float m_fSkillTime; //스킬 현재 쿨타임
    float m_fMaxSkillTime;//재사용 대기시간
};

class AI;
class CAttackObject;

class CMonster :
    public CObject
{
public:
    CMonster();
    virtual ~CMonster();

private:
    vector<tMonSkill> m_vecSKill;
    CAttackObject* m_pAttackObj;

    AI* m_AI;
    bool m_bHit;

    bool m_bDead;
    bool m_bActiv;//활성화

    tMonInfo m_tMonInfo;
    tHitInfo m_tHitInfo;
    tAttackInfo m_tAttackInfo;

    float m_fAttTime;   
    float m_fCurAttTime;

protected:
    void SetDead() { m_bDead = true; }
    void SetActiv(bool _b) { m_bActiv = _b; }
    
public:
    bool IsDead() { return m_bDead; }
    bool IsActiv() { return m_bActiv; }

public:
    virtual void update();
    virtual void render(HDC _dc);

    virtual void update_MonInterFace();

    void hit(CCollider* _pOther, const tAttackInfo& _tAtt);

    AI* GetAI() { return m_AI; }
    void SetAI(AI* _AI);

    void SetHitInfo(const tHitInfo& _tInfo) { m_tHitInfo = _tInfo; }
    tHitInfo& GetHitInfo() { return m_tHitInfo; }


private:
    void add_skill(tMonSkill _tSkill) { m_vecSKill.push_back(_tSkill); }
    void update_skillTime();

public:
    vector<tMonSkill>& GetVecSkill() { return m_vecSKill; }
    CAttackObject* GetSKillObj() { return m_pAttackObj; }

private:
    void set_attackobj(SCENE_TYPE _eSceneType);

public:
    void SettMonInfo(const tMonInfo& _tMonInfo) { m_tMonInfo = _tMonInfo; }
    tMonInfo& GetMonInfo() { return m_tMonInfo; }

public:
    void SetAttackInfo(const tAttackInfo& _tAttackInfo) { m_tAttackInfo = _tAttackInfo; }
    const tAttackInfo& GetAttackInfo() { return m_tAttackInfo; }

public:
    virtual void OnColliderEnter(CCollider* _pOther);
    virtual void OnColliderExit(CCollider* _pOther);   
    virtual void OnCollision(CCollider* _pOther);
    
    friend class CMonFactory;
    friend class CDeadState;
};

