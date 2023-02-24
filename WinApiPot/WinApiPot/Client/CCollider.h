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

	Vec2 m_vScale;//�浹ü ũ��

	UINT m_iID;
	int m_iCol;

	bool m_bActive;//Ȱ�� ����

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

	//��� �ݶ��̴� ����
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
	CCollider(const CCollider& _origin);//���� ������ ���� (Ư�� ��ü�� �����ؼ� ������ ID�� ������ ID���� ������ �� �Ҹ��ڰ� ����� �� ������ ��) 
	~CCollider();

	friend class CObject;
	friend class CSkillState;
};

