#pragma once

class CCollider;

class CSkillState;

union COLLIDER_ID
{
	struct
	{
		UINT LEFT_ID;
		UINT RIGT_ID;
	};
	ULONGLONG ID;
};

class CColliderMgr
{
	SINGLE(CColliderMgr)

private:
	map<ULONGLONG, bool> m_mapColInfo;
	UINT m_arrCheck[(UINT)GROUP_TYPE::END];

	

public:
	void update();
	void ChekGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	//void ChekSkillGroup(GROUP_TYPE _eGrouptype);
	void Reset() 
	{
		memset(m_arrCheck, 0, sizeof(UINT) *(UINT)GROUP_TYPE::END);
	}

private:
	void CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	
	bool IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol);
};

