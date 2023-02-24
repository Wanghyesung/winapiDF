#pragma once

class CPlayerState;
class CPlayer;
class CFSM
{
public:
	CFSM();
	~CFSM();

public:
	void update();

public:
	void AddState(CPlayerState* _pState);
	CPlayerState* FindState(PLAYER_STATE _ePlayerState);
	
	void ChangeState(PLAYER_STATE _ePlayerState);
	void SetCurState(PLAYER_STATE _ePlayerState);
	CPlayerState* GetCurState() { return m_pCurState; }

	PLAYER_STATE GetPrevState();
	void SetPrevState(PLAYER_STATE _ePrevState);

	CPlayerState* GetPlayerState(){return m_pCurState;}
	CPlayer* GetPlayer() { return m_pOwner; }

	

private:
	map<PLAYER_STATE, CPlayerState*> m_mapState;
	CPlayerState* m_pCurState;

	PLAYER_STATE m_eCurState;
	PLAYER_STATE m_ePreState;

	CPlayer* m_pOwner;

	friend class CPlayer;
};

