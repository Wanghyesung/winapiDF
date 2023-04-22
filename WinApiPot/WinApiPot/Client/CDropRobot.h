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

	//��� �ݶ��̴��� �̹��� ���� �ݶ��̴����� Ȯ���ϱ� ���� ����
	unordered_map<UINT,UINT> m_hashColl;

	//�����ͼ� �κ����� ��������� ����
	Vec2 m_vCreatePos;

	Vec2 m_vDir;

	float m_fDropSpeed;

	UINT m_iAttackCount;
	bool m_bAttackOn;
public:
	virtual void render(HDC _dc);
	virtual void update();//���
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

