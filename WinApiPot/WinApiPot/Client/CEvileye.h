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
    //�̺���� ��ȯ ��
    //��ȯ ��ü���� �ð� �ٸ��� �ϱ� ����
    static UINT m_iEvilCount;

    unordered_map<UINT, tEvileyeSkill> m_hashSkillTime;

    MONSTER_STATE m_eMonState;

    //�̺���� ���� ������ ��������
    wstring m_strMonDir;

    //�� ���� �ð�, ���� �ð�
    float m_fCreateEyeTime;
    float m_fCurTime;
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
    void update_passive();

    //�� �߻� 
    void shotEye();
    //���� �� ��ȯ
    void createEye();
    //������
    void createLaser();

    friend class CEvileyeIdel;
    friend class CEvileyeAttack;
};

