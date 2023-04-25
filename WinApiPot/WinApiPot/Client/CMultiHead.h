#pragma once
#include "CSkillState.h"
class CMultiHead :
    public CSkillState
{
public:
    CMultiHead();
    virtual ~CMultiHead();

private:
	float m_fOffSet;
	Vec2 m_vCollSize;
	Vec2 m_vCollOffSet;

	UINT m_iAttackCount;
	wstring m_strSkillName;
	wstring m_strPreStateName;
	//일정 시간동안 키를 움직이지 않으면 exit
	float m_fExitTime;
	float m_fCurExitTime;

	//일정 시간동안 움직임을 바꿀 수 없음
	float m_fChangeTime;
	float m_fCurChangeTime;

	int m_iDirX;
	int m_iDirY;
public:
	virtual void Skillupdate();
	virtual void update();
	virtual void init();//collider 초기화
	virtual void exit();
	virtual void enter();

public:
	virtual void OnColliderEnter(CCollider* _pOther);
	virtual void OnColliderExit(CCollider* _pOther) ;
	virtual void OnCollision(CCollider* _pOther);

private:
	void change_Dir(int _iDirX, int _iDirY);
	void create_particle(Vec2 _vPos);
};

