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
	CSkillState* m_pCurSkill;//��ų ���·� �ؼ� ������ ��������
	CPlayer* m_pOwner;
	map<SKILL_STATE, CSkillState*> m_mapSkill;

	//�÷��̾��� ����
	int m_iDir;

public:
	void update();

public:
	void AddSkill(CSkillState* _pSkillState);
	//mgr���� ������Ʈ ������ mgr���� �Է¹��� ��ų���¸� �޾Ƽ� �ش� ��ų���� ��ü�� update�� ȣ������
	CSkillState* FindSkillState(SKILL_STATE _eSkillState);
	CSkillState* GetCurSkill() { return m_pCurSkill; }
	CPlayer* GetPlayer() { return m_pOwner; }
	
	//setcurSkill �����ϱ�
private:
	void SetCurSkill(CSkillState* _pSkillState) { m_pCurSkill = _pSkillState; }

	friend class CPlayer;
	friend class CSkillMgr;
};

