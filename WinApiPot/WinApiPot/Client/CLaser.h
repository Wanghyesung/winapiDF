#pragma once
#include "CSkillState.h"

class CLaser :
    public CSkillState
{
public:
    CLaser();
    virtual ~CLaser();

private:
    float m_fOffSet;
    Vec2 m_vCollSize;
    Vec2 m_vCollOffSet;

    int m_iAttackFrame;
    wstring m_strSkillName;
    wstring m_strLaserName;

    //�߻� ����
    bool m_bStart;
public:
    virtual void Skillupdate();
    virtual void init();
    virtual void exit();
    virtual void enter();

    //������ ���̰�
    virtual void render(HDC _dc);
    virtual void finalupdate();

public:
    virtual void OnColliderEnter(CCollider* _pOther);
    virtual void OnColliderExit(CCollider* _pOther);
    virtual void OnCollision(CCollider* _pOther);


};

