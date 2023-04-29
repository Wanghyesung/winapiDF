#pragma once
#include "CObject.h"

class CEvileye;

class CShotEye :
    public CObject
{
public:
    CShotEye();
    virtual ~CShotEye();

private:
    CEvileye* m_pOwner;
    wstring m_strLaserDir;

    tAttackInfo m_tAtt;
    bool m_bAttackOn;
    bool m_bDelOn;
    UINT m_iFrame;

    int m_iDir;
    //날아갈 방향
    Vec2 m_vLookAt;

    float m_fDeleteTime;
    float m_fCurTime;

public:
    virtual void render(HDC _dc);
    virtual void update();//상속

public:
    const tAttackInfo& GetAttackInfo() { return m_tAtt; }
    bool IsAttackOn() { return m_bAttackOn; }

public:
    virtual void OnColliderEnter(CCollider* _pOther);
    virtual void OnColliderExit(CCollider* _pOther);
    virtual void OnCollision(CCollider* _pOther);

private:
    bool IsSameJumLoc(CCollider* _pOther, CCollider* _pThis);
    void setDir(int _iDir) { m_iDir = _iDir; }
    void init_pos(Vec2 _vPos);//생성될 위치 초기화

    friend class CEvileye;

};

