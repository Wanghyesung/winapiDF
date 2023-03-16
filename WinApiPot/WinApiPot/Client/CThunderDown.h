#pragma once
#include "CObject.h"

class CLord;

class CThunderDown :
    public CObject
{
public:
	CThunderDown();
	virtual ~CThunderDown();

private:
	CTexture* pTex;//����
	CLord* m_pOwner;

	//�� ���� ��ġ�������� ȸ���� ����
	float m_fDegree;

	tAttackInfo m_tAtt;

public:
	virtual void render(HDC _dc);
	virtual void update();

public:
	virtual void OnColliderEnter(CCollider* _pOther);
	virtual void OnColliderExit(CCollider* _pOther);
	virtual void OnCollision(CCollider* _pOther);

public:
	const tAttackInfo& GetAttackInfo() { return m_tAtt; }
private:
	void SetAttackInfo(const tAttackInfo& _tAtt) { m_tAtt = _tAtt; }

	friend class CLord;
};

