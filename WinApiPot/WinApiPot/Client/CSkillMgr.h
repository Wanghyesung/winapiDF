#pragma once


class CSkill;
class CPlayer;

class CSkillMgr
{
public:
	SINGLE(CSkillMgr)

private:
	//해당 오브젝트에서 스킬이 끝나면 bool값을 넘겨줌
	CPlayer*				 m_pPlayer;
	bool					 m_bOnSkill;
	float					 m_fMaxSkillTime;
	SKILL_STATE				 m_eCurStkllState;
	map<SKILL_STATE, float>  m_mapSkill;

public:
	void update();//매 프레임마다 해당 키의 스킬이 눌렸는지 체크와 해당 스킬을 누르고 재사용대기시간 체크
	void init();//스킬 리소스 받아두기

	void initSkill();

	//스킬 키가 눌렸는지
	bool IsOnSkill() { return m_bOnSkill; }
	void SetEndSkill(bool _b) { m_bOnSkill = _b; }
	void SetPlayer(CPlayer* _pPlayer) { m_pPlayer = _pPlayer; }

	SKILL_STATE GetCurSkill() { return m_eCurStkllState; }
	void SetCurSkill(SKILL_STATE _eSkill) { m_eCurStkllState = _eSkill; }

	void SetSkillTimeMax(SKILL_STATE _eSkill);
private:
	//키를 입력받고 입력된 키에 해당하는 스킬이 사용 가능한 스킬인지 확인
	bool IsPossibleSkill(SKILL_STATE _eSkill);
	void skillKey_update();

};

