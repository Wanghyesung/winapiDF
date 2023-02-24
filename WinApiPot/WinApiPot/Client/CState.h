#pragma once
class AI;
class CMonster;

class CState
{
public:
	CState(MONSTER_STATE m_eMonState);
	virtual ~CState();

private:
	AI* m_AI;
	MONSTER_STATE m_eMonState;

	int m_iDir;

public:
	AI* GetAI() { return m_AI; }
	MONSTER_STATE GetType() { return m_eMonState; }
	CMonster* GetMonster();

public:
	void SetDir(int _iDir) { m_iDir = _iDir; }
	int GetDir() { return m_iDir; }

	virtual void enter() = 0;
	virtual void exit();
	virtual void update() = 0;

	friend class AI;
};

