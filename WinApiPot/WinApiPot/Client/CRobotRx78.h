#pragma once
#include "CObject.h"

class CMonster;
class CFire;
enum class ROBOTSTATE
{
    TRACE,
    ATTACK,
    JUMP,
    BOOM
};

class CRobotRx78 :
    public CObject
{
public:
    CRobotRx78();
    virtual ~CRobotRx78();

private:
    ROBOTSTATE m_eState;
    CMonster* m_pTarget;

    tMonInfo m_tInfo;

    UINT m_iAttackCount;

    float m_fDeleteCurTime;
    float m_fDeleteTime;

    int m_iDirX;

    bool m_bBoomOn;
    bool m_bJumOn;

    //점프 관련
    Vec2 m_vTargetPos;
    float m_fJumSpeed;


public:
    virtual void render(HDC _dc);
    virtual void update();//상속
    virtual void finalupdate();

public:
    virtual void OnColliderEnter(CCollider* _pOther);
    virtual void OnColliderExit(CCollider* _pOther) ;
    virtual void OnCollision(CCollider* _pOther);

private:
    void attack();
    void createBoom();
    void trace();
    void jump();

    bool setTarget();

    void update_state();


    friend class CFire;
};

