#pragma once

class CCollider;
class CPlayer;
class CSkillState;
class CSkillMgr;

class CSkill
{
public:
	CSkill();
	~CSkill();

private:
	CSkillState* m_pCurSkill;//스킬 상태로 해서 맵으로 구현하자
	CPlayer* m_pOwner;
	map<SKILL_STATE, CSkillState*> m_mapSkill;

	//플레이어의 방향
	int m_iDir;

public:
	void update();

public:
	void AddSkill(CSkillState* _pSkillState);
	//mgr에서 업데이트 들어오면 mgr에서 입력받은 스킬상태를 받아서 해당 스킬상태 객체에 update를 호출해줌
	CSkillState* FindSkillState(SKILL_STATE _eSkillState);
	CSkillState* GetCurSkill() { return m_pCurSkill; }
	CPlayer* GetPlayer() { return m_pOwner; }
	
	//setcurSkill 지정하기
private:
	void SetCurSkill(CSkillState* _pSkillState) { m_pCurSkill = _pSkillState; }

	friend class CPlayer;
	friend class CSkillMgr;
};

