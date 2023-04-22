#pragma once
#include "CObject.h"
class CMechDrop;

class CDropRobot :
    public CObject
{
public:
	CDropRobot();
	virtual ~CDropRobot();

private:
	tAttackInfo m_tAtt;

	//상대 콜라이더가 이미지 맞은 콜라이더인지 확인하기 위한 벡터
	unordered_map<UINT,UINT> m_hashColl;

	//내려와서 로봇으로 만들어지는 지점
	Vec2 m_vCreatePos;

	Vec2 m_vDir;

	float m_fDropSpeed;

	UINT m_iAttackCount;
	bool m_bAttackOn;
public:
	virtual void render(HDC _dc);
	virtual void update();//상속
	virtual void finalupdate();

public:
	virtual void OnColliderEnter(CCollider* _pOther);
	virtual void OnColliderExit(CCollider* _pOther) ;
	virtual void OnCollision(CCollider* _pOther);

	const tAttackInfo& GetAttInfo() { return m_tAtt; }
	bool IsAttackOn() { return m_bAttackOn; }

private:
	void create_robot();
	void init_dir(int _iDir, Vec2 _vCreatePos);
	bool isSameYPos(CCollider* _pOtherCol);

	friend class CMechDrop;
};

