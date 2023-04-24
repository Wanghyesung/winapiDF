#pragma once
#include "CObject.h"
class CMonster;

class CRobotEx8 :
    public CObject
{
public:
    CRobotEx8();
    virtual ~CRobotEx8();

private:
    ROBOTSTATE m_eState;

    tMonInfo m_tInfo;

    float m_fDeleteTime;

    int m_iDirX;

    bool m_bBoomOn;
    bool m_bJumOn;

    //���� ����
    Vec2 m_vTargetPos;
    float m_fJumSpeed;


public:
    virtual void render(HDC _dc);
    virtual void update();//���
    virtual void finalupdate();

public:
    virtual void OnColliderEnter(CCollider* _pOther);
    virtual void OnColliderExit(CCollider* _pOther);
    virtual void OnCollision(CCollider* _pOther);

private:
    void attack();
    void wait();//�ð� ���
    void createBoom();
    void jump();


    void render_time(HDC _dc);

    void render_second(HDC _dc);
    void render_millisecond(HDC _dc);

    void update_state();


    friend class CFire;

};

