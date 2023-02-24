#pragma once

#include "pch.h"

class CTexture;
class CAnimator;
class CRigidBody;
class CCollider;
class CSkillState;
class CGravity;
class CSkill;

struct tHitInfo
{
	float m_fHitDir; //�´� ����
	float m_fHitRcnt;//������ ���� ��
	float m_fHitUpperRcnt; //������ ����� ��
	float m_fHitRigidityTime; //���� �ð�
	UINT  m_iMaxHitFrame;
};

struct tAttackInfo
{
	float m_fAttackDamage;
	float m_fAttackTime;
	float m_fAttRcnt;//������ ���� ��
	float m_fAttUpperRcnt; //������ ����� ��
	float m_fAttUpperAcc; //�߰� ���ӵ�
	float m_fAttRigidityTime; //���� �ð�
	Vec2 m_fAttackRange;
	ATTACK_TYPE m_eAttType;
};


class CObject
{
public:
	CObject();
	virtual ~CObject();//�Ҹ��� �� ������ �� �ְ�

private:
	Vec2 m_vPos;//�� ��ġ
	Vec2 m_vSclae; // �� ũ��

	Vec2 m_vJumpPos;//ó���� �ö� �� ����� ��
	Vec2 m_vFinalJumPos; //������ �� ����� ��

	wstring m_strName;
	GROUP_TYPE m_tTag;

	bool m_bAlive; //�� ������Ʈ�� Ȱ������ ��Ȱ������

	CTexture* m_pTex;
	CAnimator* m_pAnim;
	CRigidBody* m_pRigidBody;
	CCollider* m_pCollider;
	CGravity* m_pGravity;

public:
	virtual void render(HDC _dc);
	virtual void update() = 0 ;//���
	virtual void finalupdate();

	void component_render(HDC _dc);


public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vSclae = _vScale; };

	Vec2 GetScale() { return m_vSclae; }
	Vec2 GetPos() { return m_vPos; }

	CAnimator* GetAnimator() { return m_pAnim; }
	CRigidBody* GetRigidBody() { return m_pRigidBody; }
	CCollider* GetCollider() { return m_pCollider; }
	CGravity* GetGravity() { return m_pGravity; }

	const wstring& GetName() { return m_strName; }
	void SetName(const wstring& _strName) { m_strName = _strName; }

	bool IsDead() { return !m_bAlive; }

//�������� �Լ�
public:
	void SetJumPos(Vec2 _v) { m_vJumpPos = _v; } //������ ��ġ ����
	Vec2 GetJumPos() { return m_vJumpPos; } //���� �������� ��ġ ��ȯ

	void SetFinalJumPos(Vec2 _v) { m_vFinalJumPos = _v; }
	Vec2 GetFinalJumPos() { return m_vFinalJumPos; }

public:
	GROUP_TYPE GetTag() { return m_tTag; }
	void SetTag(GROUP_TYPE _tTag) { m_tTag = _tTag; }


public:
	void CreateAnimator();
	void CreateRigidBody();
	void CreateCollider();
	void CreateGravity();
public:
	virtual void OnColliderEnter(CCollider* _pOther) {};
	virtual void OnColliderExit(CCollider* _pOther) {};
	virtual void OnCollision(CCollider* _pOther) {};


private:
	void setDead() { m_bAlive = false; }//�̺�Ʈ �Ŵ��������� ����

	friend class CEventMgr;
};

