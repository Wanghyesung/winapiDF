#pragma once
#include "CObject.h"

class CSkill;
class CCollider;




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

	bool m_bOnAttack;

	tAttackInfo m_tAtt;

	vector<UINT> m_vecAttackFrame;

public:
	virtual void Skillupdate() = 0;
	virtual void update() {}
	virtual void init() = 0;//collider √ ±‚»≠
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
	void SetAttInfo(const tAttackInfo& _tAtt) { m_tAtt = _tAtt; }
	void SetAttackOn(bool _b) { m_bOnAttack = _b; }

public:
	bool IsAttackOn() { return m_bOnAttack; }

public:
	virtual void OnColliderEnter(CCollider* _pOther) {};
	virtual void OnColliderExit(CCollider* _pOther) {};
	virtual void OnCollision(CCollider* _pOther) {};


	friend class CSkill;
};

