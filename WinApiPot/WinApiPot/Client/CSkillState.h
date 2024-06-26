#pragma once
#include "CObject.h"

class CSkill;
class CCollider;
class CSkillMgr;
class CSound;


class CSkillState : public CObject
{
public:
	CSkillState(SKILL_STATE _eSkill);
	virtual ~CSkillState();

private:
	SKILL_STATE m_eSkillState;
	CSkill* m_pOwner;
	wstring m_strSkillName;

	int m_iFrm;

	float m_fMPValue;

	bool m_bOnAttack;

	tAttackInfo m_tAtt;

	vector<UINT> m_vecAttackFrame;//내가 공격할 프레임을 모아둔 벡터
	vector<UINT> m_vecOtherColl;//공격할 몬스터 colliderID를 보관하는 벡터

	int m_iSkillTime;//내 스킬 쿨타임

	CSound* m_pSound;
public:
	virtual void Skillupdate() = 0;
	virtual void update() {}
	virtual void init() = 0;//collider 초기화
	virtual void exit();
	virtual void enter();

public:
	CSkill* GetSkill() { return m_pOwner; }

	void SetSkillState(SKILL_STATE _eSkillState) { m_eSkillState = _eSkillState; }
	SKILL_STATE GetSkillState() { return m_eSkillState; }

	void SetSKillName(const wstring& str) { m_strSkillName = str; }
	wstring& GetSkillName() { return m_strSkillName; }

	void SetCurFram(int _ifrmCount) { m_iFrm = _ifrmCount; }
	int GetCurFram() { return m_iFrm; }

	const tAttackInfo& GetAttInfo() { return m_tAtt; }

	void AddAttackFrame(UINT _i) { m_vecAttackFrame.push_back(_i); }
	const vector<UINT>& GetAttackFrame() { return m_vecAttackFrame; }

protected:
	vector<UINT>& GetOtherCollVec() { return m_vecOtherColl; }

protected:
	void SetMP(float _f) { m_fMPValue = _f; }
	float GetMP() { return m_fMPValue; }

protected:
	void SetAttInfo(const tAttackInfo& _tAtt) { m_tAtt = _tAtt; }

	//해당 프레임상태에서만 공격할 수 있게
	void SetAttackOn(bool _b) { m_bOnAttack = _b; }

	//내 쿨타임 시간
	void SetSkillTime(int _iSkillTime) { m_iSkillTime = _iSkillTime; }

public:
	bool IsAttackOn() { return m_bOnAttack; }

protected:
	void SetAnimSound(const wstring& _strPath);
	CSound* GetAnimSound() { return m_pSound; }

public:
	virtual void OnColliderEnter(CCollider* _pOther) {};
	virtual void OnColliderExit(CCollider* _pOther) {};
	virtual void OnCollision(CCollider* _pOther) {};


	friend class CSkillMgr;
	friend class CSkill;
};

