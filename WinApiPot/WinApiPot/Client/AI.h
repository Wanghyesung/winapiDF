#pragma once
//���� ������Ʈ �ֱ�

class CMonster;
class CState;

//�̰� Ŭ���� �̸� �ٲ����,,
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

