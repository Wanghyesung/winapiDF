#pragma once
class CObject;

class CRigidBody
{
public:
	CRigidBody();
	~CRigidBody();


private:
	CObject* m_pOwner;

	Vec2	m_vVelocity;//�� �ӵ�
	Vec2	m_vFore;//��
	Vec2    m_vMaxVelocity;//�ִ� �ӵ�
	Vec2	m_vAccel;//�� ���ӵ�
	Vec2	m_vAccelA;//�߰� ���ӵ�

	Vec2    m_vGravity; //�߷�
	float   m_vNgravityPos; //�߷��� �� ���� ������ �� (�߷»��¿����� ����� ��)

	float	m_fMass; //����
	float   m_fFricCoeff;//�������

	bool	m_bAttiveMass;//�������� ������ ������
	//bool	m_bAttiveGravity;

	bool	m_bDown;

	bool	m_bAccel;//���ӵ��� �������� �����ӵ��� ��������

	//�����ؼ� �������� Ÿ�̹� ����
	Vec2    m_vCurJumPos;
	Vec2    m_vPreJumPos;
	

	

public:
	void SetVelocity(Vec2 _v) { m_vVelocity = _v; }
	void AddVelocity(Vec2 _v) { m_vVelocity += _v; }
	Vec2 GetVelocity() { return m_vVelocity; }

	float GetSpeed() { return m_vVelocity.Length(); }

	float GetNgravityPos() { return m_vNgravityPos; }
	void SetNgravityPos(float _f) { m_vNgravityPos = _f; }

	void SetForce(Vec2 _v) { m_vFore = _v; }
	Vec2 GetForce() { return m_vFore; }

	void SetMass(float _f) { m_fMass = _f; }
	void SetAttiveMass(bool _b) { m_bAttiveMass = _b; }

	void SetAccelA(Vec2 _v) { m_vAccelA = _v; }
	void SetGravity(Vec2 _v) { m_vGravity = _v; }

	void SetDown(bool _b) { m_bDown = _b; }//�����ϰ� ������ ��������������

	void SetAccel(bool _b) { m_bAccel = _b;}
	bool IsAccelNow() { return m_bAccel; }

private:
	void move();
	void IsOutRangeMap();


public:
	void finalupdate();

	void AddForce(Vec2 _v) { m_vFore += _v; }
	void AddfFric(float _f) { m_fFricCoeff += _f; }



	friend class CObject;
};

