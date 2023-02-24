#pragma once
//몬스터 스테이트 넣기

class CMonster;
class CState;

//이거 클래스 이름 바꿔야함,,
class AI
{
public:
	AI();
	~AI();
	
private:
	CState* m_pCurState;
	CState* m_pPreState;

	map<MONSTER_STATE, CState*> m_mapMonState;
	CMonster* m_pOwner;


public:
	void update();


	void AddState(CState* _pState);

	CState* GetState(MONSTER_STATE _eState);

	void SetCurState(MONSTER_STATE _eState);
	void ChangeState(MONSTER_STATE _eNextState);

	CMonster* GetCMonster() { return m_pOwner; }

	CState* GetPreState() { return m_pPreState; }
	void	SetPreState(CState* pState) { m_pPreState = pState; }

	CState* GetCurState() 
	{ 
		return m_pCurState;
	}

	friend class CMonster;
};

