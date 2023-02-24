#pragma once
class CObject;

class CRigidBody
{
public:
	CRigidBody();
	~CRigidBody();


private:
	CObject* m_pOwner;

	Vec2	m_vVelocity;//내 속도
	Vec2	m_vFore;//힘
	Vec2    m_vMaxVelocity;//최대 속도
	Vec2	m_vAccel;//내 가속도
	Vec2	m_vAccelA;//추가 가속도

	Vec2    m_vGravity; //중력
	float   m_vNgravityPos; //중력을 안 더한 움직인 값 (중력상태에서만 계산을 함)

	float	m_fMass; //질량
	float   m_fFricCoeff;//마찰계수

	bool	m_bAttiveMass;//마찰력을 적용할 것인지
	//bool	m_bAttiveGravity;

	bool	m_bDown;

	bool	m_bAccel;//가속도로 움직일지 일정속도로 움직일지

	//점프해서 내려가는 타이밍 잡기용
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

	void SetDown(bool _b) { m_bDown = _b; }//점프하고 밑으로 내려가는중인지

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

