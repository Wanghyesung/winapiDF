#pragma once
#include "CObject.h"

class CEvileye;
class CPlayer;

class CCreateEye :
    public CObject
{
 public:
     CCreateEye();
     virtual ~CCreateEye();

 private:
     CPlayer* m_pTarget;

     tAttackInfo m_tAtt;
     bool m_bAttackOn;
     UINT m_iFrame;

     UINT m_iAttackCount;
 public:
     virtual void render(HDC _dc);
     virtual void update();//»ó¼Ó

 public:
     const tAttackInfo& GetAttackInfo() { return m_tAtt; }
     bool IsAttackOn() { return m_bAttackOn; }

 public:
     virtual void OnColliderEnter(CCollider* _pOther);
     virtual void OnColliderExit(CCollider* _pOther);
     virtual void OnCollision(CCollider* _pOther);

 private:
     bool IsSameJumLoc(CCollider* _pOther, CCollider* _pThis);
     void init_pos();
     void create_laser();

     friend class CEvileye;
};

