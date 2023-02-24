#pragma once

struct tColliderInfo
{
	float fLeftWidth;
	float fRightWidth;
	float fTopHeight;
	float fBottomHeight;
};


class CObject;
class CSkillState;

class CCollider
{

private:
	static UINT g_iNextId;

	CObject* m_pOwner;

	Vec2 offsetPos;
	Vec2 finalPos;

	Vec2 m_vScale;//충돌체 크기

	UINT m_iID;
	int m_iCol;

	bool m_bActive;//활성 여부

	tColliderInfo m_tCollSize;
	tColliderInfo tOtherCollInfo;

public:
	CObject* GetObj() { return m_pOwner; }

	void SetOffSet(Vec2 _v) { offsetPos = _v; }
	void SetFinalPos(Vec2 _v) { finalPos = _v; }

	Vec2 GetOffSetPos() {return offsetPos;}
	Vec2 GetFinalPos() { return finalPos;}

	UINT GetID() { return m_iID; }

	Vec2 GetScale() { return m_vScale; }
	void SetScale(Vec2 _v) { m_vScale = _v; }

	void SetColliderInfo();
	const tColliderInfo& GetColliderInfo() { return m_tCollSize; }

	void SetActive(bool _b) { m_bActive = _b; }
	bool IsActive() { return m_bActive; }

	//상대 콜라이더 정보
	const tColliderInfo& GetOtherCollInfo() { return tOtherCollInfo; }
	void SetOtherCollInfo(const tColliderInfo& _tCollInfo) { tOtherCollInfo = _tCollInfo; }

public:
	void finalupdate();
	void render(HDC _dc);

	void OnColliderEnter(CCollider* _pOther);
	void OnColliderExit(CCollider* _pOther);
	void OnCollision(CCollider* _pOther);

	CCollider& operator = (CCollider& _orgin) = delete;

public:
	CCollider();
	CCollider(const CCollider& _origin);//복사 생성자 구현 (특정 객체를 복사해서 받으면 ID가 동일한 ID값을 가지게 됨 소멸자가 실행될 때 오류가 남) 
	~CCollider();

	friend class CObject;
	friend class CSkillState;
};

