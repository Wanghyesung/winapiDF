#pragma once


class CSkill;
class CPlayer;

class CSkillMgr
{
public:
	SINGLE(CSkillMgr)

private:
	//�ش� ������Ʈ���� ��ų�� ������ bool���� �Ѱ���
	CPlayer*				 m_pPlayer;
	bool					 m_bOnSkill;
	float					 m_fMaxSkillTime;
	SKILL_STATE				 m_eCurStkllState;
	map<SKILL_STATE, float>  m_mapSkill;

public:
	void update();//�� �����Ӹ��� �ش� Ű�� ��ų�� ���ȴ��� üũ�� �ش� ��ų�� ������ ������ð� üũ
	void init();//��ų ���ҽ� �޾Ƶα�

	void initSkill();

	//��ų Ű�� ���ȴ���
	bool IsOnSkill() { return m_bOnSkill; }
	void SetEndSkill(bool _b) { m_bOnSkill = _b; }
	void SetPlayer(CPlayer* _pPlayer) { m_pPlayer = _pPlayer; }

	SKILL_STATE GetCurSkill() { return m_eCurStkllState; }
	void SetCurSkill(SKILL_STATE _eSkill) { m_eCurStkllState = _eSkill; }

	void SetSkillTimeMax(SKILL_STATE _eSkill);
private:
	//Ű�� �Է¹ް� �Էµ� Ű�� �ش��ϴ� ��ų�� ��� ������ ��ų���� Ȯ��
	bool IsPossibleSkill(SKILL_STATE _eSkill);
	void skillKey_update();

};

