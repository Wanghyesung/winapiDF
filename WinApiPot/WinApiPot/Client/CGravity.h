#pragma once

class CObject;

class CGravity
{

public:
	CGravity();
	~CGravity();

private:
	bool m_bAttive;
	CObject* m_pOwner;

	int stack;

public:
	void finalupdate();
	void SetGravity(bool _b) { m_bAttive = _b; }
	bool IsGetGravity() { return m_bAttive; }//�߷��� �ް��ֳ�


	//bool IsGravity() { return m_bAttive; }

	friend class CObject;
};

